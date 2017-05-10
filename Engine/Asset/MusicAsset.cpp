

#include "Engine/EngineCommon.h"
#include "Engine/Asset/MusicAsset.h"
#include "Engine/Asset/AssetManager.h"

int MusicAsset::PreProcessLoadedData(Buffer & buffer)
{
  return 0;
}

void MusicAsset::OnDataLoadComplete(Buffer & buffer)
{
  m_AudioBuffer = std::move(buffer);
  FinalizeAssetLoad();
}

ASSET_SOURCE_FUNCS(MusicAsset)
