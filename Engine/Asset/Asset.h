#pragma once

#include <atomic>

#include "Foundation/Buffer/Buffer.h"
#include "Foundation/Delegate/Delegate.h"
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

class Asset
{
public:
  bool IsLoaded();
  bool IsError();

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
  virtual void PreProcessLoadedData(Buffer & file_data) { } // This is called from the loader thread
  virtual bool OnDataLoadComplete(Buffer & file_data) { return true; }
  virtual void CallAssetLoadCallbacks(bool success) = 0;

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

  AssetHandle m_Handle;
  void * m_AssetManager = nullptr;
  void(*m_Deleter)(void * asset_manager, const AssetHandle &) = nullptr;

  uint64_t m_FileNameHash = 0;
  std::string m_FileName;
};
