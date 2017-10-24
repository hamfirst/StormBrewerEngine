
#include <QPainter>
#include <QMouseEvent>
#include <QTimer>

#include <StormRefl/StormReflJson.h>
#include <StormData/StormDataJson.h>
#include <sb/vector.h>

#include "Foundation/Allocator/Allocator2D.h"
#include "Foundation/Frame/Frame.h"

#include "Runtime/Map/MapDef.refl.meta.h"

#include "MapEditor.h"
#include "MapEditorTileSelector.h"
#include "DrawUtilQt.h"

MapEditorTileSelector::MapEditorTileSelector(NotNullPtr<MapEditor> editor, MapDef & map, QWidget * parent) :
  QWidget(parent),
  m_Editor(editor),
  m_Map(map),
  m_LayerIndex(-1),
  m_NumFrames(0),
  m_ScrollX(std::make_unique<QScrollBar>(Qt::Horizontal, this)),
  m_ScrollY(std::make_unique<QScrollBar>(Qt::Vertical, this)),
  m_ShowScrollX(false),
  m_ShowScrollY(false),
  m_TileSheetFileWatcher(editor),
  m_SelectedAnimation(false),
  m_SelectedFrame(kInvalidFrameId),
  m_HighlightedAnimation(false),
  m_HighlightedFrame(kInvalidFrameId)
{
  setMouseTracking(true);

  m_ScrollX->hide();
  m_ScrollY->hide();
  connect(m_ScrollX.get(), &QScrollBar::valueChanged, this, &MapEditorTileSelector::handleScrollChanged);
  connect(m_ScrollY.get(), &QScrollBar::valueChanged, this, &MapEditorTileSelector::handleScrollChanged);

  QTimer * timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &MapEditorTileSelector::tick);
  timer->start(15);
}

MapEditorTileSelector::~MapEditorTileSelector()
{

}

void MapEditorTileSelector::LoadManualTileLayer(std::size_t index)
{
  std::string path = "m_ManualTileLayers[" + std::to_string(index) + "].m_TileSheet";
  m_TileSheetFileWatcher.SetPath(path.data(), true, false, [this, index] { return m_Map.m_ManualTileLayers.HasAt(index); });
  m_TileSheetFileWatcher.SetAllUpdateCallbacks([this, index] { LoadTileSheet(m_Map.m_ManualTileLayers[index].m_TileSheet.data()); });
  LoadTileSheet(m_Map.m_ManualTileLayers[index].m_TileSheet.data());
}

void MapEditorTileSelector::Clear()
{
  m_TileSheet.Clear();  
  UpdateScroll();
  repaint();
}

void MapEditorTileSelector::SetLayer(int layer_index)
{
  m_LayerIndex = layer_index;
}

void MapEditorTileSelector::SetSelectedTile(uint64_t frame_id)
{
  m_SelectedAnimation = false;
  m_SelectedFrame = frame_id;
  repaint();
}

void MapEditorTileSelector::SetSelectedAnimation(uint64_t frame_id)
{
  m_SelectedAnimation = true;
  m_SelectedFrame = frame_id;
  repaint();
}

void MapEditorTileSelector::LoadTileSheet(czstr file_name)
{
  m_SelectedAnimation = false;
  m_SelectedFrame = kInvalidFrameId;
  m_HighlightedAnimation = false;
  m_HighlightedFrame = kInvalidFrameId;

  TileSheetResource::LoadWithCallback(file_name, [this](NotNullPtr<TileSheetResource> r) { HandleTileSheetReload(r); }, m_TileSheet);

  UpdateScroll();
  repaint();
}

void MapEditorTileSelector::HandleTileSheetReload(NotNullPtr<TileSheetResource> resource)
{
  std::vector<TextureAsset::LoadCallbackLink> old_links = std::move(m_Textures);
  for (auto elem : resource->GetData()->m_Textures)
  {
    m_Textures.emplace_back();
  }

  int texture_index = 0;
  for (auto elem : resource->GetData()->m_Textures)
  {
    TextureAsset::LoadWithCallback(elem.second.m_Filename.data(), [this](NullOptPtr<TextureAsset>) { UpdateScroll(); repaint(); }, m_Textures[texture_index]);
    texture_index++;
  }

  UpdateScroll();
  repaint();
}

void MapEditorTileSelector::UpdateScroll()
{
  int prev_scroll_val = m_ScrollY->value();

  auto content_size = VisitElements({});

  if (content_size.x <= width())
  {
    m_ScrollX->setValue(0);
    m_ScrollX->hide();

    m_ShowScrollX = false;
  }
  else
  {
    m_ScrollX->setMaximum(content_size.x - width());
    m_ScrollX->setPageStep(width());
    m_ScrollX->show();

    m_ShowScrollX = true;
  }

  if (content_size.y <= height())
  {
    m_ScrollY->setValue(0);
    m_ScrollY->hide();

    m_ShowScrollY = false;
  }
  else
  {
    m_ScrollY->setMaximum(content_size.y - height());
    m_ScrollY->setPageStep(height());
    m_ScrollY->show();

    m_ShowScrollY = true;
  }
}

Vector2 MapEditorTileSelector::VisitElements(Delegate<void, QImage *, int, int, int, int, int, int, int, int, uint64_t, bool> && callback)
{
  if (m_TileSheet.GetResource() == nullptr)
  {
    return {};
  }

  int height_offset = 0;
  int highest_x = 0;
  int highest_y = 0;

  int magnification = 2;
  int spacing_size = 5;

  int available_width = width() - m_ScrollY->sizeHint().width() - 1;
  Optional<Allocator2DShelf> allocator;
  allocator.Emplace(available_width);

  int texture_index = 0;
  for (auto elem : m_TileSheet.GetData()->m_Textures)
  {
    if (texture_index >= m_Textures.size())
    {
      continue;
    }

    auto texture = m_Textures[texture_index].Get();
    texture_index++;
    if (texture == nullptr || texture->IsLoaded() == false || texture->GetWidth() <= 0 || texture->GetHeight() <= 0)
    {
      continue;
    }

    auto & texture_data = elem.second;
    if (texture_data.m_FrameWidth <= 0 || texture_data.m_FrameHeight <= 0)
    {
      continue;
    }

    uint64_t tex_frame_id = crc32(texture_data.m_Filename.data());
    tex_frame_id <<= 32;

    auto img = DrawUtilQt::CreateImageFromTexture(*texture);
    if (!img)
    {
      continue;
    }

    int dst_w = texture_data.m_FrameWidth * magnification;
    int dst_h = texture_data.m_FrameHeight * magnification;

    auto display_size = GetFrameDisplaySize(texture_data.m_FrameWidth, texture_data.m_FrameHeight, texture->GetWidth(), texture->GetHeight(), magnification, spacing_size);
    auto frame_size = GetSizeInFrames(texture_data.m_FrameWidth, texture_data.m_FrameHeight, texture->GetWidth(), texture->GetHeight());

    Vector2 location;

    if (display_size.x >= available_width)
    {
      height_offset = highest_y;
      location = Vector2(0, 0);
      allocator.Emplace(available_width);
    }
    else
    {
      auto result = allocator->Allocate(display_size.x, display_size.y);
      if (result == false || result->m_Rotated)
      {
        height_offset = highest_y;
        location = Vector2(0, 0);
        allocator.Emplace(available_width);
      }
      else
      {
        location = Vector2(result->m_X, result->m_Y);
      }
    }

    VisitFrames(texture_data.m_FrameWidth, texture_data.m_FrameHeight, 
      texture->GetWidth(), texture->GetHeight(), [&](int src_x, int src_y, int fx, int fy, int frame_index) 
    {
      uint64_t frame_id = tex_frame_id | frame_index;

      int dst_x = src_x * magnification + fx * spacing_size - m_ScrollX->value() + location.x + spacing_size;
      int dst_y = src_y * magnification + fy * spacing_size - m_ScrollY->value() + location.y + spacing_size + height_offset;

      callback(&img.Value(), src_x, src_y, texture_data.m_FrameWidth, texture_data.m_FrameHeight, dst_x, dst_y, dst_w, dst_h, frame_id, false);
    });

    highest_x = std::max(location.x + display_size.x, highest_x);
    highest_y = std::max(location.y + display_size.y, highest_y);
  }

  for (auto elem : m_TileSheet.GetData()->m_Animations)
  {
    auto animation_hash = crc32(elem.second.m_Name.data());
    uint64_t animation_frame_id = (uint64_t)animation_hash;
    animation_frame_id <<= 32;

    AnimationState anim_state;
    m_TileSheet.GetResource()->InitAnimation(animation_hash, m_NumFrames, anim_state);

    auto frame_id = (uint64_t)elem.second.m_Frames[anim_state.m_AnimFrame].m_FrameId;
    auto texture_id = (uint32_t)(frame_id >> 32);
    auto frame_index = (uint32_t)frame_id;

    NullOptPtr<TextureAsset> tex = nullptr;
    NullOptPtr<SpriteBaseDefTexture> tex_info = nullptr;

    texture_index = 0;
    for (auto elem : m_TileSheet.GetData()->m_Textures)
    {
      auto & texture_data = elem.second;
      uint32_t tex_name_hash = crc32(texture_data.m_Filename.data());
      uint64_t tex_frame_id = tex_name_hash;
      tex_frame_id <<= 32;

      if (texture_index >= m_Textures.size())
      {
        break;
      }

      auto texture = m_Textures[texture_index].Get();
      texture_index++;

      if (tex_name_hash != texture_id)
      {
        continue;
      }

      if (texture == nullptr || texture->IsLoaded() == false || texture->GetWidth() <= 0 || texture->GetHeight() <= 0)
      {
        break;
      }

      if (texture_data.m_FrameWidth <= 0 || texture_data.m_FrameHeight <= 0)
      {
        break;
      }

      tex = texture;
      tex_info = &elem.second;
    }

    if (tex == nullptr)
    {
      continue;
    }

    auto display_size = m_TileSheet.GetResource()->GetAnimationMaxSize(animation_hash);
    display_size.x += spacing_size * 2;
    display_size.y += spacing_size * 2;

    Vector2 location;

    if (display_size.x >= available_width)
    {
      height_offset = highest_y;
      location = Vector2(0, 0);
      allocator.Emplace(available_width);
    }
    else
    {
      auto result = allocator->Allocate(display_size.x, display_size.y);
      if (result == false || result->m_Rotated)
      {
        height_offset = highest_y;
        location = Vector2(0, 0);
        allocator.Emplace(available_width);
      }
      else
      {
        location = Vector2(result->m_X, result->m_Y);
      }
    }

    auto img = DrawUtilQt::CreateImageFromTexture(*tex);
    if (!img)
    {
      continue;
    }

    VisitFrame(tex_info->m_FrameWidth, tex_info->m_FrameHeight, tex->GetWidth(), tex->GetHeight(), frame_index, [&](int src_x, int src_y)
    {
      int dst_x = location.x + spacing_size - m_ScrollX->value();
      int dst_y = location.y + spacing_size - m_ScrollY->value() + height_offset;

      int dst_w = tex_info->m_FrameWidth * magnification;
      int dst_h = tex_info->m_FrameHeight * magnification;

      callback(&img.Value(), src_x, src_y, tex_info->m_FrameWidth, tex_info->m_FrameHeight, dst_x, dst_y, dst_w, dst_h, animation_frame_id, true);
    });

    highest_x = std::max(location.x + display_size.x, highest_x);
    highest_y = std::max(location.y + display_size.y, highest_y);
  }

  return Vector2(highest_x, highest_y);
}

void MapEditorTileSelector::paintEvent(QPaintEvent * ev)
{
  QPainter p(this);

  static const int border_size = 1;
  VisitElements([&](QImage * img, int src_x, int src_y, int src_w, int src_h, int dst_x, int dst_y, int dst_w, int dst_h, uint64_t frame_id, bool animation)
  {
    p.drawImage(QRect(dst_x, dst_y, dst_w, dst_h), *img, QRect(src_x, src_y, src_w, src_h));

    DrawUtilQt::DrawFrameBorder(src_w, src_h, dst_x, dst_y, 2, border_size,
      frame_id == m_SelectedFrame && animation == m_SelectedAnimation, frame_id == m_HighlightedFrame && animation == m_HighlightedAnimation, p);
  });
}

void MapEditorTileSelector::resizeEvent(QResizeEvent * ev)
{
  m_ScrollX->setGeometry(0, height() - m_ScrollX->sizeHint().height() - 1, width() - 1, m_ScrollX->sizeHint().height());
  m_ScrollY->setGeometry(width() - m_ScrollY->sizeHint().width() - 1, 0, m_ScrollY->sizeHint().width(), height() - 1);
  UpdateScroll();
}

void MapEditorTileSelector::mouseMoveEvent(QMouseEvent * ev)
{
  auto prev_highlighted_frame = m_HighlightedFrame;
  auto prev_highlighted_anim = m_HighlightedAnimation;
  m_HighlightedFrame = kInvalidFrameId;

  VisitElements([&](QImage * img, int src_x, int src_y, int src_w, int src_h, int dst_x, int dst_y, int dst_w, int dst_h, uint64_t frame_id, bool animation)
  {
    if (ev->x() >= dst_x && ev->x() < dst_x + dst_w && ev->y() >= dst_y && ev->y() < dst_y + dst_w)
    {
      m_HighlightedFrame = frame_id;
      m_HighlightedAnimation = animation;
    }
  });

  if (m_HighlightedFrame != prev_highlighted_frame || m_HighlightedAnimation != prev_highlighted_anim)
  {
    repaint();
  }
}

void MapEditorTileSelector::mousePressEvent(QMouseEvent * ev)
{
  if (m_HighlightedFrame != kInvalidFrameId)
  {
    if (m_HighlightedAnimation)
    {
      m_Editor->SelectManualAnimation(m_LayerIndex, m_HighlightedFrame);
    }
    else
    {
      m_Editor->SelectManualTile(m_LayerIndex, m_HighlightedFrame);
    }
  }
}

void MapEditorTileSelector::wheelEvent(QWheelEvent * ev)
{
  if (m_ShowScrollY == false)
  {
    return;
  }

  auto delta = ev->delta();
  if (delta > 0)
  {
    m_ScrollY->setValue(m_ScrollY->value() - 20);
  }
  else
  {
    m_ScrollY->setValue(m_ScrollY->value() + 20);
  }
}

void MapEditorTileSelector::leaveEvent(QEvent * ev)
{
  if (m_HighlightedFrame != kInvalidFrameId)
  {
    m_HighlightedFrame = kInvalidFrameId;
    repaint();
  }
}

void MapEditorTileSelector::handleScrollChanged()
{
  repaint();
}

void MapEditorTileSelector::tick()
{
  m_NumFrames++;
  repaint();
}
