
#include "Runtime/RuntimeCommon.h"
#include "Runtime/Asset/Asset.h"

#include "Foundation/Assert/Assert.h"

GlobalAssetList g_GlobalAssetList;
PreMainCallList g_GlobalAssetListRegister;
PreMainCallList g_GlobalDependentAssetRegister;

void GlobalAssetList::BeginAssetLoad(NotNullPtr<ClientAssetLoader> client_asset_loader)
{
  m_ClientAssetLoader = client_asset_loader;

  if (m_RefCount == 0)
  {
    for (std::size_t index = 0, end = m_GlobalAssets.size(); index < end; ++index)
    {
      m_GlobalAssets[index].BeginLoad(index);
    }

    for (std::size_t index = 0, end = m_DependentAssetContainers.size(); index < end; ++index)
    {
      auto & dep = m_DependentAssetContainers[index];
      dep.BeginLoad(dep.m_BaseAssetList, dep.m_BaseAssetListCount,
              dep.m_DependentAssetContainerList, dep.m_DependentAssetContainerListCount,
              dep.m_LoadLinks, dep.m_LoadFunc);
    }

    for (std::size_t index = 0, end = m_ClientAssets.size(); index < end; ++index)
    {
      m_ClientAssetLoader->BeginLoad(m_ClientAssets[index].m_Asset, m_ClientAssets[index].m_Path.data(), m_ClientAssets[index].m_Type);
    }
  }

  m_RefCount++;
}

void GlobalAssetList::UnloadAllAssets()
{
  m_RefCount--;
  ASSERT(m_RefCount >= 0, "Calling UnloadAllAssets too many times");

  if (m_RefCount == 0)
  {
    m_GlobalDependentAssets.clear();

    for (auto & asset_info : m_DependentAssetContainers)
    {
      asset_info.Unload(asset_info.m_DependentAssetContainerList, asset_info.m_DependentAssetContainerListCount, asset_info.m_LoadLinks);
    }

    for (auto & asset_info : m_GlobalAssets)
    {
      asset_info.Unload(asset_info.m_Asset);
    }

    for (auto & asset_info : m_ClientAssets)
    {
      m_ClientAssetLoader->Unload(asset_info.m_Asset, asset_info.m_Type);
    }
  }
}

bool GlobalAssetList::AllAssetsLoaded()
{
  for (auto & asset_info : m_GlobalAssets)
  {
    if (asset_info.IsLoaded(asset_info.m_Asset) == false)
    {
      return false;
    }
  }

  for (auto & asset_info : m_GlobalDependentAssets)
  {
    if (asset_info.IsLoaded(asset_info.m_Asset.GetRaw()) == false)
    {
      return false;
    }
  }

  for (auto & asset_info : m_ClientAssets)
  {
    if (m_ClientAssetLoader->IsLoaded(asset_info.m_Asset, asset_info.m_Type) == false)
    {
      return false;
    }
  }

  return true;
}

void GlobalAssetList::CreateClientAsset(ClientAssetType type, czstr path)
{
  m_ClientAssets.emplace_back(ClientAssetInfo{ path, type });
}
