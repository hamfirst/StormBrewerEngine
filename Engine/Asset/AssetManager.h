#pragma once  

#include <colony/colony.h>
#include <hash/Hash.h>

#include <unordered_map>

#include "Foundation/Singleton/Singleton.h"

#include "Asset.h"
#include "AssetLoader.h"

template <typename AssetType>
class AssetManager : public AssetReloadCallback
{
public:
  AssetManager()
  {
    static AssetReloadInfo reload_info = { this };
    g_AssetLoader.RegisterAssetLoadCallback(&reload_info);
  }

  AssetType * LoadAsset(czstr file_path)
  {
    static_assert(sizeof(Asset::AssetHandle) >= sizeof(typename plf::colony<AssetType>::iterator), "Invalid iterator size");

    uint64_t file_name_hash = crc64lowercase(file_path);
    auto existing_asset_itr = m_AssetLookup.find(file_name_hash);
    if (existing_asset_itr != m_AssetLookup.end())
    {
      auto & asset = *existing_asset_itr->second;
      return &asset;
    }
    
    auto itr = m_Assets.emplace();
    auto & asset = *itr;

    g_AssetLoader.RequestFileLoad(&asset, file_path);

    Asset::AssetHandle handle;
    new (handle.m_Buffer) typename plf::colony<AssetType>::iterator(itr);

    asset.m_Handle = handle;
    asset.m_AssetManager = this;
    asset.m_FileName = file_path;
    asset.m_FileNameHash = file_name_hash;

    asset.m_Deleter = [](void * asset_manager, const Asset::AssetHandle & asset_handle)
    {
      AssetManager<AssetType> * ptr = static_cast<AssetManager<AssetType> *>(asset_manager);
      ptr->DestroyAsset(asset_handle);
    };

    m_AssetLookup.emplace(file_name_hash, itr);
    return &asset;
  }

  void DestroyAsset(const Asset::AssetHandle & handle)
  {
    auto itr = reinterpret_cast<const typename plf::colony<AssetType>::iterator *>(handle.m_Buffer);
    m_Assets.erase(*itr);
  }

  void ReloadFile(const char * path)
  {
    uint64_t file_name_hash = crc64lowercase(path);
    auto existing_asset_itr = m_AssetLookup.find(file_name_hash);
    if (existing_asset_itr == m_AssetLookup.end())
    {
      return;
    }

    auto & asset = *existing_asset_itr->second;
    g_AssetLoader.RequestFileLoad(&asset, path);
  }

private:
  plf::colony<AssetType> m_Assets;
  std::unordered_map<uint64_t, typename plf::colony<AssetType>::iterator> m_AssetLookup;
};
