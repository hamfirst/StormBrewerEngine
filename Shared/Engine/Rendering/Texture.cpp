
#include "Engine/EngineCommon.h"
#include "Engine/Rendering/Texture.h"
#include "Engine/Rendering/RenderErrorMacros.h"
#include "Texture.h"

#include <gl3w/gl3w.h>

#define GL_LUMINANCE 0x1909


Texture::Texture()
{
  m_TextureName = 0;
  m_LoadError = 0;
  m_Width = 0;
  m_Height = 0;
  m_Type = TextureType::kInvalid;
  m_LinearFilter = false;
}

Texture::Texture(Texture && rhs) noexcept
{
  Move(std::move(rhs));
}

Texture::~Texture()
{
  Destroy();
}

Texture & Texture::operator = (Texture && rhs) noexcept
{
  Destroy();
  Move(std::move(rhs));
  return *this;
}

void Texture::Move(Texture && rhs) noexcept
{
  m_TextureName = rhs.m_TextureName;
  m_LoadError = rhs.m_LoadError;
  m_Width = rhs.m_Width;
  m_Height = rhs.m_Height;
  m_Type = rhs.m_Type;

  rhs.m_TextureName = 0;
  rhs.m_LoadError = 0;
  rhs.m_Width = 0;
  rhs.m_Height = 0;
  rhs.m_Type = TextureType::kInvalid;
}

void Texture::Destroy()
{
  if (m_TextureName != 0)
  {
    glDeleteTextures(1, &m_TextureName);
    m_TextureName = 0;
  }

  m_LoadError = 0;
  m_Width = 0;
  m_Height = 0;
  m_Type = TextureType::kInvalid;
}

void Texture::CreateEmptyTexture(int width, int height, TextureType type)
{
  Destroy();

  GLenum format;
  int bpp = 1;
  switch (type)
  {
  case TextureType::kGrayscale:
#if 0
    format = GL_LUMINANCE;
#else
    format = GL_RED;
#endif
    bpp = 1;
    break;
  case TextureType::kRGB:
    format = GL_RGB;
    bpp = 3;
    break;
  case TextureType::kRGBA:
    format = GL_RGBA;
    bpp = 4;
    break;
  case TextureType::kFRGBA:
    format = GL_RGBA;
    bpp = 4;
    break;
  case TextureType::kInvalid:
    return;
  }

  GLenum gl_type;
  switch(type)
  {
  default:
    gl_type = GL_UNSIGNED_BYTE;
    break;
  case TextureType::kFRGBA:
    gl_type = GL_FLOAT;
    bpp *= 4;
    break;
  }

  glGenTextures(1, &m_TextureName); CHECK_GL_RENDER_ERROR;
  auto texture_destroy_on_error = gsl::finally([&] { if (m_LoadError != 0) { glDeleteTextures(1, &m_TextureName); m_TextureName = 0; } });

  auto mem_size = bpp * width * height;
  auto mem = std::make_unique<uint8_t[]>(bpp * width * height);
  memset(mem.get(), 0, mem_size);

  glBindTexture(GL_TEXTURE_2D, m_TextureName); CHECK_GL_RENDER_ERROR;
  glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, mem.get()); CHECK_GL_RENDER_ERROR;
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); CHECK_GL_RENDER_ERROR;
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); CHECK_GL_RENDER_ERROR;
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); CHECK_GL_RENDER_ERROR;
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); CHECK_GL_RENDER_ERROR;
  glBindTexture(GL_TEXTURE_2D, 0); CHECK_GL_RENDER_ERROR;


  m_Width = width;
  m_Height = height;
  m_Type = type;
}

void Texture::SetTextureData(const PixelBuffer & pixel_buffer, TextureType type)
{
  Destroy();

  GLenum format;
  GLenum gl_type = GL_UNSIGNED_BYTE;

  switch (type)
  {
  case TextureType::kGrayscale:
#if 1
    format = GL_LUMINANCE;
#else
    format = GL_RED;
#endif
    ASSERT(pixel_buffer.GetPixelSize() == 1, "Invalid Pixel Surface");
    break;
  case TextureType::kRGB:
    format = GL_RGB;
    ASSERT(pixel_buffer.GetPixelSize() == 3, "Invalid Pixel Surface");
    break;
  case TextureType::kRGBA:
    ASSERT(pixel_buffer.GetPixelSize() == 4, "Invalid Pixel Surface");
    format = GL_RGBA;
    break;
  case TextureType::kFRGBA:
    ASSERT(pixel_buffer.GetPixelSize() == 16, "Invalid Pixel Surface");
    format = GL_RGBA;
    gl_type = GL_FLOAT;
    break;
  default:
    ASSERT(false, "Invalid pixel surface type");
    return;
  }

  //printf("Creating texture (%d, %d)\n", pixel_buffer.GetWidth(), pixel_buffer.GetHeight());

  glGenTextures(1, &m_TextureName); CHECK_GL_RENDER_ERROR;
  auto texture_destroy_on_error = gsl::finally([&] { if (m_LoadError != 0) { glDeleteTextures(1, &m_TextureName); m_TextureName = 0; } });

  glBindTexture(GL_TEXTURE_2D, m_TextureName); CHECK_GL_RENDER_ERROR;
  glTexImage2D(GL_TEXTURE_2D, 0, format, pixel_buffer.GetWidth(), pixel_buffer.GetHeight(), 0, format, gl_type, pixel_buffer.GetPixelBuffer()); CHECK_GL_RENDER_ERROR;
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); CHECK_GL_RENDER_ERROR;
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); CHECK_GL_RENDER_ERROR;
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); CHECK_GL_RENDER_ERROR;
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); CHECK_GL_RENDER_ERROR;
  glBindTexture(GL_TEXTURE_2D, 0); CHECK_GL_RENDER_ERROR;

  m_Width = pixel_buffer.GetWidth();
  m_Height = pixel_buffer.GetHeight();
  m_LinearFilter = false;
  m_Type = type;
}

void Texture::SetTextureSubData(const PixelBuffer & pixel_buffer, int dst_x, int dst_y)
{
  GLenum format;
  GLenum gl_type = GL_UNSIGNED_BYTE;

  switch (m_Type)
  {
  case TextureType::kGrayscale:
#if 1
    format = GL_LUMINANCE;
#else
    format = GL_RED;
#endif
    ASSERT(pixel_buffer.GetPixelSize() == 1, "Invalid Pixel Surface");
    break;
  case TextureType::kRGB:
    format = GL_RGB;
    ASSERT(pixel_buffer.GetPixelSize() == 3, "Invalid Pixel Surface");
    break;
  case TextureType::kRGBA:
    ASSERT(pixel_buffer.GetPixelSize() == 4, "Invalid Pixel Surface");
    format = GL_RGBA;
    break;
  case TextureType::kFRGBA:
    ASSERT(pixel_buffer.GetPixelSize() == 16, "Invalid Pixel Surface");
    format = GL_RGBA;
    gl_type = GL_FLOAT;
    break;
  default:
    ASSERT(false, "Texture has not been initialized yet");
    return;
  }

  glBindTexture(GL_TEXTURE_2D, m_TextureName); CHECK_GL_RENDER_ERROR;
  glTexSubImage2D(GL_TEXTURE_2D, 0, dst_x, dst_y, pixel_buffer.GetWidth(), pixel_buffer.GetHeight(), format, gl_type, pixel_buffer.GetPixelBuffer()); CHECK_GL_RENDER_ERROR;
  glBindTexture(GL_TEXTURE_2D, 0); CHECK_GL_RENDER_ERROR;
}

void Texture::BindTexture(int texture_stage) const
{
  glActiveTexture(GL_TEXTURE0 + texture_stage); CHECK_GL_RENDER_ERROR;
  glBindTexture(GL_TEXTURE_2D, m_TextureName); CHECK_GL_RENDER_ERROR;
}


void Texture::SetLinearFilter()
{
  if (m_LinearFilter == false)
  {
    glBindTexture(GL_TEXTURE_2D, m_TextureName); CHECK_GL_RENDER_ERROR;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); CHECK_GL_RENDER_ERROR;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); CHECK_GL_RENDER_ERROR;
    m_LinearFilter = true;
  }
}

void Texture::SetPixelPerfectFilter()
{
  if (m_LinearFilter == true)
  {
    glBindTexture(GL_TEXTURE_2D, m_TextureName); CHECK_GL_RENDER_ERROR;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); CHECK_GL_RENDER_ERROR;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); CHECK_GL_RENDER_ERROR;
    m_LinearFilter = false;
  }
}
