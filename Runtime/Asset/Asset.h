#pragma once

#include "Runtime/RuntimeCommon.h"

#include "Foundation/CallList/CallList.h"
#include "Foundation/Any/Any.h"
#include "Foundation/Preprocessor/Preprocessor.h"
#include "Foundation/FileSystem/Directory.h"

enum class ClientAssetType
{
  kAudio,
  kVfx,
  kEntity,
};

class GlobalAssetList;

extern GlobalAssetList g_GlobalAssetList;
extern PreMainCallList g_GlobalAssetListRegister;
extern PreMainCallList g_GlobalDependentAssetRegister;

class ClientAssetLoader
{
public:
  virtual void BeginLoad(Any & asset, czstr path, ClientAssetType type) {}
  virtual void Unload(Any & asset, ClientAssetType type) {}
  virtual bool IsLoaded(Any & asset, ClientAssetType type) { return true; }
  virtual bool IsError(Any & asset, ClientAssetType type) { return false; }
  virtual bool LoadingFinished(Any & asset, ClientAssetType type) { return true; }
};

struct EmptyGlobalAssetInfo
{

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

  template <typename AssetResourcePtr>
  void CreateGlobalDirectoryAssetArray(NotNullPtr<AssetResourcePtr> resource_ptr, const std::vector<std::string> & files)
  {
    for(auto & elem : files)
    {
      CreateGlobalAsset(*resource_ptr, elem.data());
      resource_ptr++;
    }
  }

  template <typename BaseAsset, typename DependentAssetContainer>
  void CreateDependentAssetContainerList(BaseAsset * base_asset_list, int * base_asset_count,
          DependentAssetContainer ** dependent_asset_container_list, int * dependent_asset_container_count,
          void (*LoadFunc)(const BaseAsset & base_asset, DependentAssetContainer & dependent_asset))
  {
    DependentGlobalAssetContainerInfo container_info;
    container_info.m_BaseAssetList = base_asset_list;
    container_info.m_BaseAssetListCount = base_asset_count;
    container_info.m_DependentAssetContainerList = dependent_asset_container_list;
    container_info.m_DependentAssetContainerListCount = dependent_asset_container_count;
    container_info.m_LoadFunc = StaticAny<8>(LoadFunc);

    using LoadFuncType = decltype(LoadFunc);

    container_info.BeginLoad = [](void * base_asset_list, int * base_asset_list_count,
                                  void * dependent_asset_list, int * dependent_asset_list_count,
                                  std::unique_ptr<StaticAny<40>[]> & load_links, StaticAny<8> & load_func)
    {
      auto base_asset_list_ptr = static_cast<BaseAsset *>(base_asset_list);
      auto dependent_asset_container_list_ptr = static_cast<DependentAssetContainer **>(dependent_asset_list);
      auto LoadFunc = *load_func.Get<LoadFuncType>();

      *dependent_asset_list_count = *base_asset_list_count;
      *dependent_asset_container_list_ptr = new DependentAssetContainer[*base_asset_list_count];
      load_links = std::make_unique<StaticAny<40>[]>(*base_asset_list_count);

      for(int index = 0; index < *base_asset_list_count; ++index)
      {
        auto base_asset = &base_asset_list_ptr[index];
        auto resource = base_asset->GetResource();
        if(resource)
        {
          load_links[index] = StaticAny<40>(
            resource->AddLoadCallback([=](auto asset_resource) { LoadFunc(*base_asset, (*dependent_asset_container_list_ptr)[index]); }));
        }
      }
    };

    container_info.Unload = [](void * dependent_asset_list, int * dependent_asset_list_count,
                               std::unique_ptr<StaticAny<40>[]> & load_links)
    {
      auto dependent_asset_container_list_ptr = static_cast<DependentAssetContainer **>(dependent_asset_list);
      delete [] *dependent_asset_container_list_ptr;

      *dependent_asset_list_count = 0;
      load_links.reset();
    };

    m_DependentAssetContainers.emplace_back(std::move(container_info));
  }

  template <typename AssetType>
  auto CreateDependentAsset(const char * path)
  {
    auto asset_ref = AssetType::Load(path);
    auto asset_ref_any = StaticAny<40>(asset_ref);
    using AssetRefType = decltype(asset_ref);

    m_GlobalDependentAssets.emplace_back(DependentGlobalAssetInfo{
      [](void * asset) { return static_cast<AssetRefType  *>(asset)->IsLoaded(); },
      [](void * asset) { return static_cast<AssetRefType  *>(asset)->IsError(); },
      std::move(asset_ref_any)
    });

    return asset_ref;
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

  struct DependentGlobalAssetContainerInfo
  {
    void(*BeginLoad)(void * base_asset_list, int * base_asset_list_count,
                     void * dependent_asset_list, int * dependent_asset_list_count,
                     std::unique_ptr<StaticAny<40>[]> & load_links, StaticAny<8> & load_func);

    void(*Unload)(void * dependent_asset_list, int * dependent_asset_list_count,
                  std::unique_ptr<StaticAny<40>[]> & load_links);

    void * m_BaseAssetList;
    int * m_BaseAssetListCount;
    void * m_DependentAssetContainerList;
    int * m_DependentAssetContainerListCount;

    std::unique_ptr<StaticAny<40>[]> m_LoadLinks;
    StaticAny<8> m_LoadFunc;
  };

  struct DependentGlobalAssetInfo
  {
    bool (*IsLoaded)(void * asset);
    bool(*IsError)(void * asset);

    StaticAny<40> m_Asset;
  };

  struct ClientAssetInfo
  {
    std::string m_Path;
    ClientAssetType m_Type;
    Any m_Asset;
  };

  NotNullPtr<ClientAssetLoader> m_ClientAssetLoader;

  std::vector<GlobalAssetInfo> m_GlobalAssets;
  std::vector<DependentGlobalAssetContainerInfo> m_DependentAssetContainers;
  std::vector<DependentGlobalAssetInfo> m_GlobalDependentAssets;
  std::vector<ClientAssetInfo> m_ClientAssets;
  int m_RefCount = 0;
};

#define GLOBAL_ASSET(AssetType, AssetPath, AssetVar) \
  AssetType AssetVar; \
  ADD_PREMAIN_CALL(g_GlobalAssetListRegister, AssetVar, []() { g_GlobalAssetList.CreateGlobalAsset(AssetVar, AssetPath); } );

#define GLOBAL_ASSET_ARRAY(AssetType, AssetVar, ...) \
  AssetType * AssetVar; \
  int AssetVar##Count = PP_NARG(__VA_ARGS__); \
  ADD_PREMAIN_CALL(g_GlobalAssetListRegister, AssetVar, \
          []() { static auto ptr = std::make_unique<AssetType[]>(PP_NARG(__VA_ARGS__)); \
                 AssetVar = ptr.get(); \
                 g_GlobalAssetList.CreateGlobalAssetArray(AssetVar, __VA_ARGS__); } );

#define GLOBAL_ASSET_DIRECTORY(AssetType, AssetVar, AssetDir, Extension)  \
  AssetType * AssetVar; \
  int AssetVar##Count = 0; \
  ADD_PREMAIN_CALL(g_GlobalAssetListRegister, AssetVar, \
          []() { auto files = GetFilesInDirectory(AssetDir, Extension); \
                 static auto ptr = std::make_unique<AssetType[]>(files.size()); \
                 AssetVar##Count = (int)files.size(); \
                 AssetVar = ptr.get(); \
                 g_GlobalAssetList.CreateGlobalDirectoryAssetArray(AssetVar, files); } );

#define GLOBAL_DEPENDENT_ASSET_ARRAY(AssetType, AssetVar, BaseAssetArray, LoadFunc) \
  AssetType * AssetVar; \
  int AssetVar##Count; \
  ADD_PREMAIN_CALL(g_GlobalDependentAssetRegister, AssetVar, []() { \
    g_GlobalAssetList.CreateDependentAssetContainerList(BaseAssetArray, &BaseAssetArray##Count, \
            &AssetVar, &AssetVar##Count, LoadFunc); \
  });

#define EXTERN_GLOBAL_ASSAET_ARRAY(AssetType, AssetVar) \
  extern AssetType * AssetVar; \
  extern int AssetVar##Count;

#define DECLARE_STATIC_LIST_TYPE(StaticListTypeName, AssetVar) \
  using StaticListTypeName = NetReflectionStaticListPtr<std::template decay_t<decltype(AssetVar[0])>, &AssetVar, &AssetVar##Count, true>;

#define CLIENT_ASSET(ClientAssetType, AssetPath, AssetVar) \
  uint32_t AssetVar = crc32lowercase(AssetPath); \
  ADD_PREMAIN_CALL(g_GlobalAssetListRegister, AssetVar, []() { g_GlobalAssetList.CreateClientAsset(ClientAssetType, AssetPath); } );

