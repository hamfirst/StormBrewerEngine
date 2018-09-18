#pragma once

#include "Runtime/RuntimeCommon.h"

#include "Foundation/CallList/CallList.h"
#include "Foundation/Any/Any.h"
#include "Foundation/Preprocessor/Preprocessor.h"

enum class ClientAssetType
{
  kAudio,
  kVfx,
  kEntity,
};

class GlobalAssetList;

extern GlobalAssetList g_GlobalAssetList;
extern PreMainCallList g_GlobalAssetListRegister;

class ClientAssetLoader
{
public:
  virtual void BeginLoad(Any & asset, czstr path, ClientAssetType type) {}
  virtual void Unload(Any & asset, ClientAssetType type) {}
  virtual bool IsLoaded(Any & asset, ClientAssetType type) { return true; }
  virtual bool IsError(Any & asset, ClientAssetType type) { return false; }
  virtual bool LoadingFinished(Any & asset, ClientAssetType type) { return true; }
};

class GlobalAssetList
{
public:
  void BeginAssetLoad(NotNullPtr<ClientAssetLoader> client_asset_loader);
  void UnloadAllAssets();

  bool AllAssetsLoaded();

  template <typename AssetResourcePtr>
  void CreateGlobalAsset(AssetResourcePtr & asset, czstr file_path)
  {
    using AssetType = typename AssetResourcePtr::AssetType;

    std::size_t index = m_GlobalAssets.size();

    GlobalAssetInfo asset_info;
    asset_info.BeginLoad = [](std::size_t asset_index) 
    {  
      auto & asset_info = g_GlobalAssetList.m_GlobalAssets[asset_index];
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
    m_GlobalAssets.push_back(asset_info);
  }

  template <typename AssetResourcePtr, typename ... Args>
  void CreateGlobalAssetArray(NotNullPtr<AssetResourcePtr> resource_ptr, const char * path, Args ... args)
  {
    CreateGlobalAsset(*resource_ptr, path);
    CreateGlobalAssetArray(resource_ptr + 1, args...);
  }

  template <typename AssetResourcePtr>
  void CreateGlobalAssetArray(NotNullPtr<AssetResourcePtr> resource_ptr)
  {

  }

  void CreateClientAsset(ClientAssetType type, czstr path);

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

  struct ClientAssetInfo
  {
    std::string m_Path;
    ClientAssetType m_Type;
    Any m_Asset;
  };

  NotNullPtr<ClientAssetLoader> m_ClientAssetLoader;

  std::vector<GlobalAssetInfo> m_GlobalAssets;
  std::vector<ClientAssetInfo> m_ClientAssets;
  int m_RefCount = 0;
};

#define GLOBAL_ASSET(AssetType, AssetPath, AssetVar) \
  AssetType AssetVar; \
  ADD_PREMAIN_CALL(g_GlobalAssetListRegister, AssetVar, []() { g_GlobalAssetList.CreateGlobalAsset(AssetVar, AssetPath); } );

#define GLOBAL_ASSET_ARRAY(AssetType, AssetVar, ...) \
  AssetType AssetVar[PP_NARG(__VA_ARGS__)]; \
  int AssetVar##Count = sizeof(AssetVar) / sizeof(AssetVar[0]); \
  ADD_PREMAIN_CALL(g_GlobalAssetListRegister, AssetVar, []() { g_GlobalAssetList.CreateGlobalAssetArray(AssetVar, __VA_ARGS__); } );

#define CLIENT_ASSET(ClientAssetType, AssetPath, AssetVar) \
  uint32_t AssetVar = crc32lowercase(AssetPath); \
  ADD_PREMAIN_CALL(g_GlobalAssetListRegister, AssetVar, []() { g_GlobalAssetList.CreateClientAsset(ClientAssetType, AssetPath); } );

