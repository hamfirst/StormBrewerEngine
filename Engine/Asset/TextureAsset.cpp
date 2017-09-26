

#include "Engine/EngineCommon.h"

#include "Foundation/Buffer/BufferUtil.h"

#include "Engine/Asset/TextureAsset.h"
#include "Engine/Asset/AssetManager.h"

#include <lodepng/lodepng.h>


int TextureAsset::PreProcessLoadedData(Buffer & buffer, bool load_deps)
{
  unsigned char * out_memory;
  unsigned int width;
  unsigned int height;

  auto error = lodepng_decode_memory(&out_memory, &width, &height, buffer.Get(), buffer.GetSize(), LodePNGColorType::LCT_RGBA, 8);
  if (error != 0)
  {
    return error;
  }

  buffer = MoveToBuffer(PixelBuffer(out_memory, width, height, 4));
  return 0;
}

void TextureAsset::OnDataLoadComplete(Buffer & buffer, bool load_deps)
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
    m_LoadError = 0xBADDBADD;
    CallAssetLoadCallbacksWithFailure();
    //printf("Invalid pixel size: %d\n", m_PixelBuffer->GetPixelSize());
    return;
  }

  //printf("Finalizing texture: %d %d\n", m_PixelBuffer->GetWidth(), m_PixelBuffer->GetHeight());

  m_Texture.SetTextureData(*m_PixelBuffer, type);
  if (m_Texture.GetLoadError() != 0)
  {
    m_LoadError = m_Texture.GetLoadError();
    CallAssetLoadCallbacksWithFailure();
    return;
  }

  if (m_LinearFilter)
  {
    m_Texture.SetLinearFilter();
  }

  FinalizeAssetLoad();
}

const Texture & TextureAsset::GetTexture() const
{
  return m_Texture;
}

int TextureAsset::GetWidth() const
{
  return m_PixelBuffer->GetWidth();
}

int TextureAsset::GetHeight() const
{
  return m_PixelBuffer->GetHeight();
}

Vector2 TextureAsset::GetSize() const
{
  return Vector2(GetWidth(), GetHeight());
}

NullOptPtr<const PixelBuffer> TextureAsset::GetPixelBuffer() const
{
  return m_PixelBuffer.GetPtr();
}

void TextureAsset::SetLinearFilter()
{
  m_LinearFilter = true;
  if (IsLoaded())
  {
    m_Texture.SetLinearFilter();
  }
}

bool TextureAsset::IsValid() const
{
  return IsLoaded() && GetWidth() > 0 && GetHeight() > 0;
}

ASSET_SOURCE_FUNCS(TextureAsset)
