#pragma once

#include "Engine/Asset/Asset.h"
#include "Engine/Asset/AssetTypeMacros.h"
#include "Engine/Rendering/Texture.h"

class TextureAsset : public Asset
{
public:

  const Texture & GetTexture() const;

  int GetWidth();
  int GetHeight();

protected:

  virtual void PreProcessLoadedData(Buffer & buffer) override;
  virtual bool OnDataLoadComplete(Buffer & buffer) override;


protected:
  Optional<PixelBuffer> m_PixelBuffer;
  Texture m_Texture;

public:
  ASSET_HEADER_FUNCS(TextureAsset);
};
