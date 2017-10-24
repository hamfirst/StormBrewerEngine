#pragma once

#include "Runtime/RuntimeCommon.h"

#include "Foundation/CallList/CallList.h"

class GlobalAssetList
{
public:
  void BeginAssetLoad();
  void UnloadAllAssets();

  bool AllAssetsLoaded();

  template <typename AssetResourcePtr>
  void CreateGlobalAsset(AssetResourcePtr & asset, czstr file_path)
  {
    using AssetType = typename AssetResourcePtr::AssetType;

    std::size_t index = m_Assets.size();

    GlobalAssetInfo asset_info;
    asset_info.BeginLoad = [](std::size_t asset_index) 
    {  
      auto & asset_info = g_GlobalAssetList.m_Assets[asset_index];
      AssetResourcePtr * asset = static_cast<AssetResourcePtr *>(asset_info.m_Asset);

      *asset = AssetType::Load(asset_info.m_Path.data());
    };

    asset_info.Unload = [](void * asset_ptr) 
    {
      AssetResourcePtr * asset = static_cast<AssetResourcePtr *>(asset_ptr);
      asset->Clear();
    };

    asset_info.IsLoaded = [](void * asset_ptr)
    {
      AssetResourcePtr * asset = static_cast<AssetResourcePtr *>(asset_ptr);
      return asset->IsLoaded();
    };

    asset_info.IsError = [](void * asset_ptr)
    {
      AssetResourcePtr * asset = static_cast<AssetResourcePtr *>(asset_ptr);
      return asset->IsError();
    };

    asset_info.LoadingFinished = [](void * asset_ptr)
    {
      AssetResourcePtr * asset = static_cast<AssetResourcePtr *>(asset_ptr);
      return asset->LoadingFinished();
    };

    asset_info.m_Asset = &asset;
    asset_info.m_Path = file_path;
    m_Assets.push_back(asset_info);
  }

private:

  struct GlobalAssetInfo
  {
    void(*BeginLoad)(std::size_t asset_index);
    void(*Unload)(void * asset);
    bool(*IsLoaded)(void * asset);
    bool(*IsError)(void * asset);
    bool(*LoadingFinished)(void * asset);

    void * m_Asset;
    std::string m_Path;
  };

  std::vector<GlobalAssetInfo> m_Assets;
  int m_RefCount = 0;
};

extern GlobalAssetList g_GlobalAssetList;
extern PreMainCallList g_GlobalAssetListRegister;

#define GLOBAL_ASSET(AssetType, AssetPath, AssetVar) \
  AssetType AssetVar; \
  ADD_PREMAIN_CALL(g_GlobalAssetListRegister, AssetVar, []() { g_GlobalAssetList.CreateGlobalAsset(AssetVar, AssetPath); } );

