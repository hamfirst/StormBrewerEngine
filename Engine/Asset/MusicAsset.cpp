

#include "Engine/EngineCommon.h"
#include "Engine/Asset/MusicAsset.h"
#include "Engine/Asset/AssetManager.h"

int MusicAsset::PreProcessLoadedData(Buffer & buffer, bool load_deps)
{
  return 0;
}

void MusicAsset::OnDataLoadComplete(Buffer & buffer, bool load_deps)
{
  m_AudioBuffer = std::move(buffer);
  FinalizeAssetLoad();
}

ASSET_SOURCE_FUNCS(MusicAsset)
