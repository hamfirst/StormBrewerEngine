

#include "Engine/EngineCommon.h"
#include "Engine/Asset/BinaryAsset.h"
#include "Engine/Asset/AssetManager.h"

const void * BinaryAsset::GetAssetData() const
{
  return m_Buffer.Get();
}

std::size_t BinaryAsset::GetAssetLength() const
{
  return m_Buffer.GetSize();
}

int BinaryAsset::PreProcessLoadedData(Buffer & buffer, bool load_deps)
{
  return 0;
}

void BinaryAsset::OnDataLoadComplete(Buffer & buffer, bool load_deps)
{
  m_Buffer = std::move(buffer);
  FinalizeAssetLoad();
}

ASSET_SOURCE_FUNCS(BinaryAsset)
