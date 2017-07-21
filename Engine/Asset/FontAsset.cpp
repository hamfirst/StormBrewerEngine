

#include "Engine/EngineCommon.h"
#include "Engine/Asset/FontAsset.h"
#include "Engine/Asset/AssetManager.h"

int FontAsset::PreProcessLoadedData(Buffer & buffer, bool load_deps)
{
  return 0;
}

void FontAsset::OnDataLoadComplete(Buffer & buffer, bool load_deps)
{
  m_FontBuffer = std::move(buffer);
  FinalizeAssetLoad();
}

ASSET_SOURCE_FUNCS(FontAsset)
