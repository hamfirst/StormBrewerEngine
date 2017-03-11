#pragma once


#define ASSET_HEADER_FUNCS(AssetType)                                               \
friend class AssetManager<AssetType>;                                               \
                                                                                    \
AssetType() = default;                                                              \
AssetType(const AssetType & rhs) = delete;                                          \
AssetType(AssetType && rhs) = default;                                              \
                                                                                    \
struct LoadCallbackLink                                                             \
{                                                                                   \
  AssetReference<AssetType> m_AssetRef;                                             \
  DelegateLink<void, AssetType *, bool> m_DelegateLink;                             \
  AssetType * Get() { return m_AssetRef.Resolve(); }                                \
};                                                                                  \
                                                                                    \
using LoadCallback = Delegate<void, AssetType *, bool>;                             \
                                                                                    \
static AssetReference<AssetType> Load(czstr file_path);                             \
static LoadCallbackLink LoadWithCallback(czstr file_path, LoadCallback & del);      \
                                                                                    \
LoadCallbackLink AddLoadCallback(LoadCallback del);                               \
                                                                                    \
private:                                                                            \
                                                                                    \
DelegateList<void, AssetType *, bool> m_LoadCallbackList;                           \
void CallAssetLoadCallbacks(bool success) override;                                 \


#define ASSET_SOURCE_FUNCS(AssetType)                                               \
static AssetManager<AssetType> s_AssetManager;                                      \
                                                                                    \
AssetReference<AssetType> AssetType::Load(czstr file_path)                          \
{                                                                                   \
  return AssetReference<AssetType>(s_AssetManager.LoadAsset(file_path));            \
}                                                                                   \
                                                                                    \
AssetType::LoadCallbackLink AssetType::LoadWithCallback(                            \
  czstr file_path, LoadCallback & del)                                              \
{                                                                                   \
  AssetType * asset = s_AssetManager.LoadAsset(file_path);                          \
  return asset->AddLoadCallback(del);                                               \
}                                                                                   \
                                                                                    \
AssetType::LoadCallbackLink AssetType::AddLoadCallback(LoadCallback del)          \
{                                                                                   \
  if (m_State == AssetState::kLoadError)                                            \
  {                                                                                 \
    del.Call(this, false);                                                          \
  }                                                                                 \
  else if (m_State == AssetState::kLoaded)                                          \
  {                                                                                 \
    del.Call(this, true);                                                           \
  }                                                                                 \
                                                                                    \
  return AssetType::LoadCallbackLink{                                               \
        AssetReference<AssetType>(this), m_LoadCallbackList.AddDelegate(del) };     \
}                                                                                   \
                                                                                    \
void AssetType::CallAssetLoadCallbacks(bool success)                                \
{                                                                                   \
  m_LoadCallbackList.Call(this, success);                                           \
}                                                                                   \




