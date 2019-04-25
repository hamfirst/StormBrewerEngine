
#include <QPainter>
#include <QImage>
#include <QMouseEvent>

#include "SpriteBaseEditor.h"
#include "SpriteBaseTextureFrameElement.h"

#include "StormData/StormDataPath.h"

SpriteBaseTextureFrameElement::SpriteBaseTextureFrameElement(NotNullPtr<SpriteBaseEditor> editor, Delegate<SpriteBaseDefTexture *> && elem_ptr, QWidget * parent) :
  m_Editor(editor),
  m_Watcher(m_Editor),
  m_ElementPtr(std::move(elem_ptr)),
  m_HighlightedFrame(-1)
{
  setMouseTracking(true);

  auto texture_def = m_ElementPtr();

  Delegate<bool> exist_callback(&SpriteBaseTextureFrameElement::DataExists, this);
  m_Watcher.SetPath(StormDataGetPath(*texture_def).data(), true, true, std::move(exist_callback));
  m_Watcher.SetAllUpdateCallbacks([this] { LoadTexture(); });

  m_Texture.LoadFile(texture_def->m_Filename.data());
  m_Texture.SetUpdateCallback([this] { VisitElements({}); });

  m_TextureNameHash = crc32(texture_def->m_Filename.data());

  VisitElements({});
}

SpriteBaseTextureFrameElement::~SpriteBaseTextureFrameElement()
{

}

void SpriteBaseTextureFrameElement::SetSizeChangeCallback(Delegate<void> && callback)
{
  m_SizeChanged = std::move(callback);
}

void SpriteBaseTextureFrameElement::SetFrameSelectCallback(Delegate<void, uint64_t> && callback)
{
  m_FrameSelectCallback = std::move(callback);
}

void SpriteBaseTextureFrameElement::LoadTexture()
{
  auto texture_def = m_ElementPtr();
  if (texture_def == nullptr)
  {
    return;
  }

  m_Texture.LoadFile(texture_def->m_Filename.data());
}

bool SpriteBaseTextureFrameElement::DataExists()
{
  return m_ElementPtr() != nullptr;
}


void SpriteBaseTextureFrameElement::VisitElements(Delegate<void, QImage *, int, int, int, int, int, int, int, int, int> && callback, bool change_min_height)
{
  auto texture_def = m_ElementPtr();
  if (texture_def == nullptr)
  {
    return;
  }

  int font_height = fontMetrics().lineSpacing();

  int prev_min_height = minimumHeight();
  int new_min_height = font_height;

  auto texture = m_Texture.GetAsset();


  if (texture && texture->IsLoaded() && texture_def->m_FrameWidth > 0 && texture_def->m_FrameHeight > 0 && texture->GetWidth() > 0 && texture->GetHeight() > 0)
  {
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
      return;
    }

    QImage img(pixel_buffer->GetPixelBuffer(), pixel_buffer->GetWidth(), pixel_buffer->GetHeight(), img_format);

    auto start_x = width() / 3 - 5;
    auto space_available = width() - start_x - 1;
    auto frames_per_line = space_available / (texture_def->m_FrameWidth * magnification + spacing);
    frames_per_line = std::max(frames_per_line, 1);

    auto src_frames_x = (texture->GetWidth() + (texture_def->m_FrameWidth - 1)) / texture_def->m_FrameWidth;
    auto src_frames_y = (texture->GetHeight() + (texture_def->m_FrameHeight - 1)) / texture_def->m_FrameHeight;

    auto src_frames_total = src_frames_x * src_frames_y;

    int src_x = 0;
    int src_y = 0;

    int dst_x = 0;
    int dst_y = 4;

    int frames_this_line = frames_per_line;
    int content_height = texture_def->m_FrameHeight * magnification + spacing;
    int frame_index = 0;

    while (src_frames_total > 0)
    {
      callback(&img, 
        start_x + dst_x, dst_y, texture_def->m_FrameWidth * magnification, texture_def->m_FrameHeight * magnification,
        src_x, src_y, texture_def->m_FrameWidth, texture_def->m_FrameHeight, frame_index);

      frame_index++;

      src_x += texture_def->m_FrameWidth;
      if (src_x >= texture->GetWidth())
      {
        src_x = 0;
        src_y += texture_def->m_FrameHeight;
      }

      frames_this_line--;
      if (frames_this_line == 0)
      {
        dst_x = 0;
        dst_y += texture_def->m_FrameHeight * magnification + spacing;
        frames_this_line = frames_per_line;
      }
      else
      {
        dst_x += texture_def->m_FrameWidth * magnification + spacing;
      }

      src_frames_total--;
      if (src_frames_total)
      {
        content_height = std::max(content_height, dst_y + texture_def->m_FrameHeight * magnification + spacing);
      }
    }

    new_min_height = std::max(new_min_height, content_height);
  }

  if (prev_min_height != new_min_height && change_min_height)
  {
    setMinimumHeight(new_min_height);
    m_SizeChanged();
  }
}

void SpriteBaseTextureFrameElement::paintEvent(QPaintEvent * ev)
{
  auto texture_def = m_ElementPtr();
  if (texture_def == nullptr)
  {
    return;
  }

  QPainter p(this);

  int font_height = fontMetrics().lineSpacing();
  p.drawText(5, font_height, texture_def->m_Filename.data());

  p.setPen(QColor(0, 0, 0, 60));

  VisitElements([&](QImage * img, int dst_x, int dst_y, int dst_w, int dst_h, int src_x, int src_y, int src_w, int src_h, int frame_index)
  {
    if (frame_index == m_HighlightedFrame)
    {
      p.drawImage(QRect(dst_x, dst_y, dst_w, dst_h), *img, QRect(src_x, src_y, src_w, src_h));

      auto prev_pen = p.pen();

      p.setPen(QPen(QColor(70, 70, 250, 160), 4));
      p.drawRect(dst_x - border_size, dst_y - border_size, dst_w + border_size, dst_h + border_size);
      p.setPen(prev_pen);
    }
    else
    {
      p.drawRect(dst_x - border_size, dst_y - border_size, dst_w + border_size, dst_h + border_size);
      p.drawImage(QRect(dst_x, dst_y, dst_w, dst_h), *img, QRect(src_x, src_y, src_w, src_h));
    }

  }, false);
}

void SpriteBaseTextureFrameElement::resizeEvent(QResizeEvent * ev)
{
  VisitElements({});
}

void SpriteBaseTextureFrameElement::mouseMoveEvent(QMouseEvent * ev)
{
  auto prev_highlight = m_HighlightedFrame;
  m_HighlightedFrame = -1;

  VisitElements([&](QImage * img, int dst_x, int dst_y, int dst_w, int dst_h, int src_x, int src_y, int src_w, int src_h, int frame_index)
  {
    if (ev->x() >= dst_x && ev->y() >= dst_y && ev->x() < dst_x + dst_w && ev->y() < dst_y + dst_h)
    {
      m_HighlightedFrame = frame_index;
    }
  }, false);

  if (m_HighlightedFrame != prev_highlight)
  {
    update();
  }
}

void SpriteBaseTextureFrameElement::mousePressEvent(QMouseEvent * ev)
{
  if (m_HighlightedFrame != -1)
  {
    uint64_t frame_id = m_TextureNameHash;
    frame_id <<= 32;
    frame_id |= m_HighlightedFrame;
    m_FrameSelectCallback(frame_id);
  }
}

void SpriteBaseTextureFrameElement::leaveEvent(QEvent * ev)
{
  if (m_HighlightedFrame != -1)
  {
    m_HighlightedFrame = -1;
    update();
  }
}
