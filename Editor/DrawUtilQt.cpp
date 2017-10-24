
#include "DrawUtilQt.h"

#include "Foundation/Frame/Frame.h"

Optional<QImage> DrawUtilQt::CreateImageFromTexture(const TextureAsset & tex)
{
  if (tex.IsLoaded() == false || tex.GetWidth() <= 0 || tex.GetHeight() <= 0)
  {
    return {};
  }

  auto pixel_buffer = tex.GetPixelBuffer();

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
    return {};
  }

  return QImage(pixel_buffer->GetPixelBuffer(), pixel_buffer->GetWidth(), pixel_buffer->GetHeight(), img_format);
}

void DrawUtilQt::DrawFrameBorder(int frame_width, int frame_height, int dx, int dy, int magnification, int border_size, bool selected, bool highlighted, QPainter & painter)
{
  int dst_w = frame_width * magnification;
  int dst_h = frame_height * magnification;
  if (selected && highlighted)
  {
    painter.setPen(QPen(Qt::darkBlue, 6));
  }
  else if (highlighted)
  {
    painter.setPen(QPen(Qt::darkBlue, 4));
  }
  else if (selected)
  {
    painter.setPen(QPen(Qt::blue, 4));
  }
  else
  {
    painter.setPen(Qt::black);
  }

  painter.drawRect(dx - border_size, dy - border_size, dst_w + border_size, dst_h + border_size);
  painter.setPen(Qt::black);
}

bool DrawUtilQt::DrawFrame(const TextureAsset & tex, int frame_width, int frame_height, uint32_t frame_index, int dx, int dy, int magnification, QPainter & painter)
{
  auto img = CreateImageFromTexture(tex);
  if (!img)
  {
    return false;
  }

  return DrawFrame(img.Value(), frame_width, frame_height, frame_index, dx, dy, magnification, painter);
}

bool DrawUtilQt::DrawFrame(QImage & img, int frame_width, int frame_height, uint32_t frame_index, int dx, int dy, int magnification, QPainter & painter)
{
  if (frame_width <= 0 || frame_height <= 0)
  {
    return false;
  }

  VisitFrame(frame_width, frame_height, img.width(), img.height(), frame_index, [&] (int src_x, int src_y)
  {
    painter.drawImage(QRect(dx, dy, frame_width * magnification, frame_height * magnification), img, QRect(src_x, src_y, frame_width, frame_height));
  });

  return true;
}
