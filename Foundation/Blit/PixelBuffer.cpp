
#include "Foundation/Common.h"

#include "PixelBuffer.h"


PixelBuffer::PixelBuffer(uint8_t * buffer, int width, int height, int pixel_size) :
  m_Memory(buffer),
  m_Width(width),
  m_Height(height),
  m_PixelSize(pixel_size),
  m_Stride(width * pixel_size)
{

}

PixelBuffer::PixelBuffer(std::unique_ptr<uint8_t[]> buffer, int width, int height, int pixel_size) :
  m_Buffer(std::move(buffer)),
  m_Memory(m_Buffer.get()),
  m_Width(width),
  m_Height(height),
  m_PixelSize(pixel_size),
  m_Stride(width * pixel_size)
{

}

PixelBuffer::PixelBuffer(int width, int height, int pixel_size) :
  m_Buffer(std::make_unique<uint8_t[]>(width * height * pixel_size)),
  m_Memory(m_Buffer.get()),
  m_Width(width),
  m_Height(height),
  m_PixelSize(pixel_size),
  m_Stride(width * pixel_size)
{

}

PixelBuffer::PixelBuffer(int width, int height, const void * buffer_data, int pixel_size) :
  PixelBuffer(width, height, pixel_size)
{
  memcpy(m_Buffer.get(), buffer_data, width * height * pixel_size);
}

PixelBuffer::~PixelBuffer()
{

}

PixelBuffer PixelBuffer::Rotate()
{
  PixelBuffer buffer(m_Height, m_Width, m_PixelSize);
  for (int y = 0; y < m_Height; y++)
  {
    for (int x = 0; x < m_Width; x++)
    {
      memcpy(buffer.GetPixelBuffer(y, m_Width - x - 1), GetPixelBuffer(x, y), m_PixelSize);
    }
  }

  return buffer;
}

uint8_t * PixelBuffer::GetPixelBuffer()
{
  return m_Memory;
}

uint8_t * PixelBuffer::GetPixelBuffer(int x, int y)
{
  return m_Memory + ((y * m_Stride) + x * m_PixelSize);
}

const uint8_t * PixelBuffer::GetPixelBuffer() const
{
  return m_Memory;
}

const uint8_t * PixelBuffer::GetPixelBuffer(int x, int y) const
{
  return m_Memory + ((y * m_Stride) + x * m_PixelSize);
}
