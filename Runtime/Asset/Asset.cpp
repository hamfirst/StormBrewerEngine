
#include "Runtime/RuntimeCommon.h"
#include "Runtime/Asset/Asset.h"

#include "Foundation/Assert/Assert.h"

GlobalAssetList g_GlobalAssetList;
PreMainCallList g_GlobalAssetListRegister;

void GlobalAssetList::BeginAssetLoad()
{
  if (m_RefCount == 0)
  {
    for (std::size_t index = 0, end = m_Assets.size(); index < end; ++index)
    {
      m_Assets[index].BeginLoad(index);
    }
  }

  m_RefCount++;
}

void GlobalAssetList::UnloadAllAssets()
{
  m_RefCount--;
  if (m_RefCount == 0)
  {
    for (auto & asset_info : m_Assets)
    {
      asset_info.Unload(asset_info.m_Asset);
    }
  }

  ASSERT(m_RefCount >= 0, "Calling unmatched UnloadAllAssets");
}

bool GlobalAssetList::AllAssetsLoaded()
{
  for (auto & asset_info : m_Assets)
  {
    if (asset_info.IsLoaded(asset_info.m_Asset) == false)
    {
      return false;
    }
  }

  return true;
}
