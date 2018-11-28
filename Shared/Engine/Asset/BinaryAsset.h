#pragma once

#include "Engine/Asset/Asset.h"
#include "Engine/Asset/AssetTypeMacros.h"
#include "Engine/Audio/AudioFormat.h"


class ENGINE_EXPORT BinaryAsset : public Asset
{
public:

  const void * GetAssetData() const;
  std::size_t GetAssetLength() const;

protected:

  virtual int PreProcessLoadedData(Buffer & buffer, bool load_deps) override;
  virtual void OnDataLoadComplete(Buffer & buffer, bool load_deps) override;

protected:

  Buffer m_Buffer;

public:
  ASSET_HEADER_FUNCS(BinaryAsset);
};
