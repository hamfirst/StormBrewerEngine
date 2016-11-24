

#include "Engine/EngineCommon.h"

#include "Foundation/Buffer/BufferUtil.h"

#include "Engine/Asset/TextureAsset.h"
#include "Engine/Asset/AssetManager.h"

#include <upng/upng.h>


void TextureAsset::PreProcessLoadedData(Buffer & buffer)
{
  upng_t * png_data = upng_new_from_bytes(buffer.Get(), (unsigned long)buffer.GetSize());
  if (png_data == nullptr)
  {
    m_LoadError = UPNG_ENOMEM;
    return;
  }

  auto png_destroy = gsl::finally([&] { upng_free(png_data); });

  upng_error load_error = upng_decode(png_data);
  if (load_error != UPNG_EOK)
  {
    m_LoadError = load_error;
    return;
  }

  if (upng_get_bitdepth(png_data) != 8)
  {
    m_LoadError = UPNG_EUNFORMAT;
    return;
  }

  unsigned int width = upng_get_width(png_data);
  unsigned int height = upng_get_height(png_data);
  unsigned int bpp = 0;
  switch (upng_get_format(png_data))
  {
  case UPNG_RGB8:
    bpp = 3;
    break;
  case UPNG_RGBA8:
    bpp = 4;
    break;
  default:
    m_LoadError = UPNG_EUNFORMAT;
    return;
  }

  if (m_LoadError == 0)
  {
    // This is a little not cool, but I'm stealing data right out of the upng struct
    buffer = MoveToBuffer(PixelBuffer(std::unique_ptr<uint8_t[]>(upng_steal_buffer(png_data)), width, height, bpp));
  }
}

bool TextureAsset::OnDataLoadComplete(Buffer & buffer)
{
  m_PixelBuffer = MoveFromBuffer<PixelBuffer>(buffer);

  TextureType type;
  switch (m_PixelBuffer->GetPixelSize())
  {
  case 3:
    type = TextureType::kRGB;
    break;
  case 4:
    type = TextureType::kRGBA;
    break;
  default:
    m_LoadError = UPNG_EUNFORMAT;
    return false;
  }

  m_Texture.SetTextureData(*m_PixelBuffer, type);
  if (m_Texture.GetLoadError() != 0)
  {
    m_LoadError = m_Texture.GetLoadError();
    return false;
  }

  FinalizeAssetLoad();
  return true;
}

const Texture & TextureAsset::GetTexture() const
{
  return m_Texture;
}

int TextureAsset::GetWidth()
{
  return m_PixelBuffer->GetWidth();
}

int TextureAsset::GetHeight()
{
  return m_PixelBuffer->GetHeight();
}

ASSET_SOURCE_FUNCS(TextureAsset)
