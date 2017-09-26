#pragma once

#include <memory>

#include "Foundation/Common.h"

class PixelBuffer
{
public:
  PixelBuffer(NotNullPtr<uint8_t> buffer, int width, int height, int pixel_size = 4);
  PixelBuffer(std::unique_ptr<uint8_t[]> buffer, int width, int height, int pixel_size = 4);
  PixelBuffer(int width, int height, int pixel_size = 4);
  PixelBuffer(int width, int height, const void * buffer_data, int pixel_size = 4);
  PixelBuffer(const PixelBuffer & rhs) = delete;
  PixelBuffer(PixelBuffer && rhs) = default;

  ~PixelBuffer();

  PixelBuffer & operator = (const PixelBuffer & rhs) = delete;
  PixelBuffer & operator = (PixelBuffer && rhs) = default;

  template <typename PixelType>
  PixelType * GetPixelPtr()
  {
    ASSERT(sizeof(PixelType) == m_PixelSize, "Getting pixel buffer pointer of incorrect type");
    return static_cast<PixelType *>(GetPixelBuffer());
  }

  template <typename PixelType>
  PixelType * GetPixelPtr(int x, int y)
  {
    ASSERT(sizeof(PixelType) == m_PixelSize, "Getting pixel buffer pointer of incorrect type");
    return static_cast<PixelType *>(GetPixelBuffer(x, y));
  }

  PixelBuffer Rotate();

  static PixelBuffer CreateFromInvertedData(NotNullPtr<uint8_t> buffer, int width, int height, int pixel_size = 4);

  int GetWidth() const { return m_Width; }
  int GetHeight() const { return m_Height; }
  int GetPixelSize() const { return m_PixelSize; }
  int GetStride() const { return m_Stride; }

  NotNullPtr<uint8_t> GetPixelBuffer();
  NotNullPtr<uint8_t> GetPixelBuffer(int x, int y);

  const NotNullPtr<uint8_t> GetPixelBuffer() const;
  const NotNullPtr<uint8_t> GetPixelBuffer(int x, int y) const;

private:


  std::unique_ptr<uint8_t[]> m_Buffer;
  uint8_t * m_Memory;
  int m_Width;
  int m_Height;
  int m_PixelSize;
  int m_Stride;
};

