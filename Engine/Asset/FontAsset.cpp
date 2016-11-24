

#include "Engine/EngineCommon.h"
#include "Engine/Asset/FontAsset.h"
#include "Engine/Asset/AssetManager.h"

void FontAsset::PreProcessLoadedData(Buffer & buffer)
{

}

bool FontAsset::OnDataLoadComplete(Buffer & buffer)
{
  m_FontBuffer = std::move(buffer);
  FinalizeAssetLoad();
  return true;
}

ASSET_SOURCE_FUNCS(FontAsset)
