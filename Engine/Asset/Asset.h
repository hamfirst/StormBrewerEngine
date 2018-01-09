#pragma once

#include <atomic>

#include "Foundation/Delegate/DelegateList.h"
#include "Foundation/Delegate/DelegateLink.h"

#include "Engine/EngineCommon.h"
#include "Engine/Asset/AssetReference.h"


enum class AssetState
{
  kLoading,
  kLoadError,
  kFinalizing,
  kLoaded,
};

template <typename AssetType>
class AssetManager;

class ENGINE_EXPORT GenericLoadCallbackLink
{
public:
  GenericLoadCallbackLink() = default;
  GenericLoadCallbackLink(const GenericLoadCallbackLink & rhs) = delete;
  GenericLoadCallbackLink(GenericLoadCallbackLink && rhs) = default;
  GenericLoadCallbackLink & operator = (const GenericLoadCallbackLink & rhs) = delete;
  GenericLoadCallbackLink & operator = (GenericLoadCallbackLink && rhs) = default;
  ~GenericLoadCallbackLink() { m_DelegateLink = {}; m_AssetRef = {}; }
  NullOptPtr<Asset> Get() { return m_AssetRef.m_Asset; }

private:

  friend class Asset;

  GenericLoadCallbackLink(DelegateLink<void, NullOptPtr<Asset>> && delegate_link, AssetReferenceBase && asset_ref) :
    m_DelegateLink(std::move(delegate_link)),
    m_AssetRef(std::move(asset_ref))
  {

  }

  DelegateLink<void, NullOptPtr<Asset>> m_DelegateLink;
  AssetReferenceBase m_AssetRef;
};

class ENGINE_EXPORT Asset
{
public:
  bool IsLoaded() const;
  bool IsError() const;

  const std::string & GetFileName() const;

  using GenericLoadCallback = Delegate<void, NullOptPtr<Asset>>;

  GenericLoadCallbackLink AddLoadCallback(GenericLoadCallback del);

protected:
  friend class AssetLoader;
  friend class AssetReferenceBase;

  Asset();

  void IncRef();
  void DecRef();

  void FinalizeAssetLoad();
  void CallAssetLoadCallbacksWithFailure();

public:

protected:
  virtual int PreProcessLoadedData(Buffer & file_data, bool load_deps); // This is called from the loader thread
  virtual void OnDataLoadComplete(Buffer & file_data, bool load_deps);
  virtual void CallAssetLoadCallbacks();
  virtual void CleanupAsset();

protected:

  template <typename AssetType>
  friend class AssetManager;

  struct AssetHandle // Type erased plf::colony::iterator
  {
    char m_Buffer[sizeof(void *) * 3];
  };

  std::atomic_int m_RefCount;
  AssetState m_State = AssetState::kLoading;
  int m_LoadError = 0;
  bool m_LoadedDeps = false;

  AssetHandle m_Handle;
  void * m_AssetManager = nullptr;
  void(*m_Deleter)(void * asset_manager, const AssetHandle &) = nullptr;

  DelegateList<void, NullOptPtr<Asset>> m_GenericLoadCallbackList;

  uint32_t m_FileNameHash = 0;
  std::string m_FileName;
};
