
#include "Foundation/Common.h"
#include "Blit.h"

void Blit(PixelBuffer & src, PixelBuffer & dst, int src_x, int src_y, int dst_x, int dst_y, int width, int height)
{
  ASSERT(src.GetPixelSize() == dst.GetPixelSize(), "Incompatible blit surfaces");

  ASSERT(src_x >= 0, "Blit out of bounds");
  ASSERT(src_y >= 0, "Blit out of bounds");
  ASSERT(dst_x >= 0, "Blit out of bounds");
  ASSERT(dst_y >= 0, "Blit out of bounds");
  ASSERT(src.GetWidth() >= src_x + width, "Blit out of bounds");
  ASSERT(src.GetHeight() >= src_y + height, "Blit out of bounds");
  ASSERT(dst.GetWidth() >= dst_x + width, "Blit out of bounds");
  ASSERT(dst.GetHeight() >= dst_y + height, "Blit out of bounds");

  uint8_t * src_ptr = src.GetPixelBuffer(src_x, src_y);
  uint8_t * dst_ptr = dst.GetPixelBuffer(dst_x, dst_y);

  int line_size = src.GetPixelSize() * width;
  while (height)
  {
    memcpy(dst_ptr, src_ptr, line_size);
    src_ptr += src.GetStride();
    dst_ptr += dst.GetStride();

    height--;
  }
}

void BlitRotated(PixelBuffer & src, PixelBuffer & dst, int src_x, int src_y, int dst_x, int dst_y, int width, int height)
{
  ASSERT(src.GetPixelSize() == dst.GetPixelSize(), "Incompatible blit surfaces");

  ASSERT(src_x >= 0, "Blit out of bounds");
  ASSERT(src_y >= 0, "Blit out of bounds");
  ASSERT(dst_x >= 0, "Blit out of bounds");
  ASSERT(dst_y >= 0, "Blit out of bounds");
  ASSERT(src.GetWidth() >= src_x + width, "Blit out of bounds");
  ASSERT(src.GetHeight() >= src_y + height, "Blit out of bounds");
  ASSERT(dst.GetWidth() >= dst_x + height, "Blit out of bounds");
  ASSERT(dst.GetHeight() >= dst_y + width, "Blit out of bounds");

  int pixel_size = dst.GetPixelSize();
  int dst_stride = dst.GetStride();
  uint8_t * src_ptr = src.GetPixelBuffer(src_x, src_y);
  uint8_t * src_next = src_ptr + src.GetStride();
  uint8_t * dst_ptr = dst.GetPixelBuffer(dst_x, dst_y);
  uint8_t * dst_next = dst_ptr + pixel_size;

  while (height)
  {
    for(int x = width; x; x--)
    {
      memcpy(dst_ptr, src_ptr, pixel_size);
      src_ptr += pixel_size;
      dst_ptr += dst_stride;
    }

    src_ptr = src_next;
    dst_ptr = dst_next;
    dst_next = dst_ptr + pixel_size;
    src_next = src_ptr + src.GetStride();

    height--;
  }
}
