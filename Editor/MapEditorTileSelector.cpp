
#include <QPainter>
#include <QMouseEvent>

#include <StormRefl/StormReflJson.h>
#include <StormData/StormDataJson.h>
#include <sb/vector.h>

#include "Runtime/Map/MapDef.refl.meta.h"

#include "MapEditor.h"
#include "MapEditorTileSelector.h"


MapEditorTileSelector::MapEditorTileSelector(NotNullPtr<MapEditor> editor, MapDef & map, QWidget * parent) :
  QWidget(parent),
  m_Editor(editor),
  m_Map(map),
  m_LayerIndex(-1),
  m_Scroll(std::make_unique<QScrollBar>(this)),
  m_ShowScroll(false),
  m_TileSheetFileWatcher(editor),
  m_SelectedFrame(kInvalidFrameId),
  m_HighlightedFrame(kInvalidFrameId)
{
  setMouseTracking(true);

  m_Scroll->hide();
  connect(m_Scroll.get(), &QScrollBar::valueChanged, this, &MapEditorTileSelector::handleScrollChanged);
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
  m_TileSheet = {};
  UpdateScroll();
  repaint();
}

void MapEditorTileSelector::SetLayer(int layer_index)
{
  m_LayerIndex = layer_index;
}

void MapEditorTileSelector::SetSelectedTile(uint64_t frame_id)
{
  if (frame_id != m_SelectedFrame)
  {
    m_SelectedFrame = frame_id;
    repaint();
  }
}

void MapEditorTileSelector::LoadTileSheet(czstr file_name)
{
  m_TileSheet = TileSheetResource::LoadWithCallback(file_name, [this](NotNullPtr<TileSheetResource> r) { HandleTileSheetReload(r); });
  m_SelectedFrame = kInvalidFrameId;
  m_HighlightedFrame = kInvalidFrameId;

  UpdateScroll();
  repaint();
}

void MapEditorTileSelector::HandleTileSheetReload(NotNullPtr<TileSheetResource> resource)
{
  std::vector<TextureAsset::LoadCallbackLink> old_links = std::move(m_Textures);
  for (auto elem : resource->GetData()->m_Textures)
  {
    m_Textures.emplace_back(TextureAsset::LoadWithCallback(elem.second.m_Filename.data(), [this](NullOptPtr<TextureAsset>) { UpdateScroll(); repaint(); }));
  }

  UpdateScroll();
  repaint();
}

void MapEditorTileSelector::UpdateScroll()
{
  int prev_scroll_val = m_Scroll->value();

  int content_height = VisitElements({});
  if (content_height <= height())
  {
    m_Scroll->setValue(0);
    m_Scroll->hide();

    m_ShowScroll = false;
  }
  else
  {
    m_Scroll->setMaximum(content_height - height());
    m_Scroll->setPageStep(height());
    m_Scroll->show();

    m_ShowScroll = true;
  }
}

int MapEditorTileSelector::VisitElements(Delegate<void, QImage *, int, int, int, int, int, int, int, int, uint64_t> && callback)
{
  if (m_TileSheet.GetResource() == nullptr)
  {
    return 0;
  }

  int x = 5;
  int y = 5;
  int line_height = 0;

  int available_width = width() - m_Scroll->sizeHint().width() - 1;

  int texture_index = 0;
  for (auto & elem : m_TileSheet.GetData()->m_Textures)
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

    auto pixel_buffer = texture->GetPixelBuffer();

    QImage::Format img_format;
    switch (pixel_buffer->GetPixelSize())
    {
    case 3:
      img_format = QImage::Format_RGB888;
      break;
    case 4:
      img_format = QImage::Format_RGBA8888;
      break;
    default:
      continue;
    }

    uint64_t tex_frame_id = crc32(texture_data.m_Filename.data());
    tex_frame_id <<= 32;

    QImage img(pixel_buffer->GetPixelBuffer(), pixel_buffer->GetWidth(), pixel_buffer->GetHeight(), img_format);

    int width_in_frames = (texture->GetWidth() + texture_data.m_FrameWidth - 1) / texture_data.m_FrameWidth;
    int height_in_frames = (texture->GetHeight() + texture_data.m_FrameHeight - 1) / texture_data.m_FrameHeight;

    int total_frames = width_in_frames * height_in_frames;

    int src_w = texture_data.m_FrameWidth;
    int src_h = texture_data.m_FrameHeight;
    int dst_w = texture_data.m_FrameWidth * 2;
    int dst_h = texture_data.m_FrameHeight * 2;
    int frame_index = 0;

    for (int fy = 0; fy < height_in_frames; ++fy)
    {
      for (int fx = 0; fx < width_in_frames; ++fx)
      {
        int src_x = fx * texture_data.m_FrameWidth;
        int src_y = fy * texture_data.m_FrameHeight;

        if (line_height > 0 && (x + dst_w + 10 > available_width || src_x == 0))
        {
          y += line_height + 5;
          x = 5;
          line_height = 0;
        }

        int dst_y = y - m_Scroll->value();
        if (dst_y + dst_h >= 0 && dst_y < height())
        {
          uint64_t frame_id = tex_frame_id | frame_index;
          callback(&img, src_x, src_y, src_w, src_h, x, dst_y, dst_w, dst_h, frame_id);
        }

        x += dst_w + 5;
        line_height = std::max(line_height, dst_h);
        frame_index++;
      }
    }
  }

  return y + line_height + 5;
}

void MapEditorTileSelector::paintEvent(QPaintEvent * ev)
{
  QPainter p(this);

  static const int border_size = 1;
  VisitElements([&](QImage * img, int src_x, int src_y, int src_w, int src_h, int dst_x, int dst_y, int dst_w, int dst_h, uint64_t frame_id)
  {
    if (frame_id == m_SelectedFrame && frame_id == m_HighlightedFrame)
    {
      p.drawImage(QRect(dst_x, dst_y, dst_w, dst_h), *img, QRect(src_x, src_y, src_w, src_h));
      p.setPen(QPen(Qt::darkBlue, 6));
      p.drawRect(dst_x - border_size, dst_y - border_size, dst_w + border_size, dst_h + border_size);
      p.setPen(Qt::black);
    }
    else if (frame_id == m_HighlightedFrame)
    {
      p.drawImage(QRect(dst_x, dst_y, dst_w, dst_h), *img, QRect(src_x, src_y, src_w, src_h));
      p.setPen(QPen(Qt::darkBlue, 4));
      p.drawRect(dst_x - border_size, dst_y - border_size, dst_w + border_size, dst_h + border_size);
      p.setPen(Qt::black);
    }
    else if (frame_id == m_SelectedFrame)
    {
      p.drawImage(QRect(dst_x, dst_y, dst_w, dst_h), *img, QRect(src_x, src_y, src_w, src_h));
      p.setPen(QPen(Qt::blue, 4));
      p.drawRect(dst_x - border_size, dst_y - border_size, dst_w + border_size, dst_h + border_size);
      p.setPen(Qt::black);
    }
    else
    {
      p.drawRect(dst_x - border_size, dst_y - border_size, dst_w + border_size, dst_h + border_size);
      p.drawImage(QRect(dst_x, dst_y, dst_w, dst_h), *img, QRect(src_x, src_y, src_w, src_h));
    }
  });
}

void MapEditorTileSelector::resizeEvent(QResizeEvent * ev)
{
  m_Scroll->setGeometry(width() - m_Scroll->sizeHint().width() - 1, 0, m_Scroll->sizeHint().width(), height() - 1);
  UpdateScroll();
}

void MapEditorTileSelector::mouseMoveEvent(QMouseEvent * ev)
{
  auto prev_highlighted_frame = m_HighlightedFrame;
  m_HighlightedFrame = kInvalidFrameId;

  VisitElements([&](QImage * img, int src_x, int src_y, int src_w, int src_h, int dst_x, int dst_y, int dst_w, int dst_h, uint64_t frame_id)
  {
    if (ev->x() >= dst_x && ev->x() < dst_x + dst_w && ev->y() >= dst_y && ev->y() < dst_y + dst_w)
    {
      m_HighlightedFrame = frame_id;
    }
  });

  if (m_HighlightedFrame != prev_highlighted_frame)
  {
    repaint();
  }
}

void MapEditorTileSelector::mousePressEvent(QMouseEvent * ev)
{
  if (m_HighlightedFrame != kInvalidFrameId)
  {
    m_Editor->SelectManualTile(m_LayerIndex, m_HighlightedFrame);
  }
}

void MapEditorTileSelector::wheelEvent(QWheelEvent * ev)
{
  if (m_ShowScroll == false)
  {
    return;
  }

  auto delta = ev->delta();
  if (delta > 0)
  {
    m_Scroll->setValue(m_Scroll->value() - 20);
  }
  else
  {
    m_Scroll->setValue(m_Scroll->value() + 20);
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
