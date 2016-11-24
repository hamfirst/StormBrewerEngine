

#include "Engine/EngineCommon.h"
#include "Engine/Asset/MusicAsset.h"
#include "Engine/Asset/AssetManager.h"

void MusicAsset::PreProcessLoadedData(Buffer & buffer)
{
}

bool MusicAsset::OnDataLoadComplete(Buffer & buffer)
{
  m_AudioBuffer = std::move(buffer);
  FinalizeAssetLoad();
  return true;
}

ASSET_SOURCE_FUNCS(MusicAsset)
