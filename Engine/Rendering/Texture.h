#pragma once

#include "Foundation/Blit/PixelBuffer.h"

enum class TextureType
{
  kGrayscale,
  kRGB,
  kRGBA,
  kInvalid,
};

class Texture
{
public:
  Texture();
  Texture(const Texture & rhs) = delete;
  Texture(Texture && rhs) noexcept;
  ~Texture();

  Texture & operator = (Texture & rhs) = delete;
  Texture & operator = (Texture && rhs) noexcept;

  void Move(Texture && rhs) noexcept;
  void Destroy();

  void CreateEmptyTexture(int width, int height, TextureType type);
  void SetTextureData(const PixelBuffer & pixel_buffer, TextureType type);
  void SetTextureSubData(const PixelBuffer & pixel_buffer, int dst_x, int dst_y);

  void BindTexture(int texture_stage) const;

  int GetLoadError() const { return m_LoadError; }

  int GetWidth() const { return m_Width; }
  int GetHeight() const { return m_Height; }

  Vector2 GetSize() const { return Vector2(m_Width, m_Height); }
private:

  unsigned int m_TextureName;
  unsigned int m_LoadError;
  TextureType m_Type;

  unsigned int m_Width;
  unsigned int m_Height;
};
