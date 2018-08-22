#pragma once

#include "Engine/EngineCommon.h"

using AssetSyncUpdateCallback = Delegate<void>;

template <typename AssetType>
class AssetSync
{
public:
  AssetSync() :
    m_AssetLoadHash(0)
  {

  }

  NullOptPtr<AssetType> GetAsset()
  {
    return m_AssetLink.Get();
  }

  void LoadFile(czstr file_name)
  {
    auto hash = crc32(file_name);
    if (hash == m_AssetLoadHash)
    {
      return;
    }

    if (hash == 0)
    {
      m_AssetLink = {};
      m_AssetLoadHash = 0;
      return;
    }

    typename AssetType::LoadCallback cb(&AssetSync<AssetType>::HandleLoadCallback, this);
    m_AssetLink = AssetType::LoadWithCallback(file_name, std::move(cb));
    m_AssetLoadHash = hash;
  }

  void SetUpdateCallback(AssetSyncUpdateCallback && callback)
  {
    m_LoadDelegate = std::move(callback);
  }

private:

  void HandleLoadCallback(NullOptPtr<AssetType> asset)
  {
    m_LoadDelegate();
  }

private:

  using LinkType = typename  AssetType::LoadCallbackLink;

  AssetSyncUpdateCallback m_LoadDelegate;

  uint32_t m_AssetLoadHash;
  LinkType m_AssetLink;
};
