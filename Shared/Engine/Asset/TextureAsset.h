#pragma once

#include "Engine/Asset/Asset.h"
#include "Engine/Asset/AssetTypeMacros.h"
#include "Engine/Rendering/Texture.h"

class ENGINE_EXPORT TextureAsset : public Asset
{
public:
  ~TextureAsset();

  const Texture & GetTexture() const;

  int GetWidth() const;
  int GetHeight() const;

  Vector2 GetSize() const;

  NullOptPtr<const PixelBuffer> GetPixelBuffer() const;
  void SetLinearFilter();

  bool IsValid() const;

protected:

  virtual int PreProcessLoadedData(Buffer & buffer, bool load_deps) override;
  virtual void OnDataLoadComplete(Buffer & buffer, bool load_deps) override;


protected:
  Optional<PixelBuffer> m_PixelBuffer;
  Texture m_Texture;
  bool m_LinearFilter = false;

public:
  ASSET_HEADER_FUNCS(TextureAsset);
};
