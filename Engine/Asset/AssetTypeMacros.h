#pragma once


#define ASSET_HEADER_FUNCS(AssetType)                                                                               \
friend class AssetManager<AssetType>;                                                                               \
                                                                                                                    \
AssetType() = default;                                                                                              \
AssetType(const AssetType & rhs) = delete;                                                                          \
AssetType(AssetType && rhs) = delete;                                                                               \
                                                                                                                    \
struct LoadCallbackLink                                                                                             \
{                                                                                                                   \
  DelegateLink<void, NullOptPtr<AssetType>> m_DelegateLink;                                                         \
  AssetReference<AssetType> m_AssetRef;                                                                             \
  LoadCallbackLink() = default;                                                                                     \
  LoadCallbackLink(const LoadCallbackLink & rhs) = delete;                                                          \
  LoadCallbackLink(LoadCallbackLink && rhs) = default;                                                              \
  LoadCallbackLink & operator = (const LoadCallbackLink & rhs) = delete;                                            \
  LoadCallbackLink & operator = (LoadCallbackLink && rhs) = default;                                                \
                                                                                                                    \
  ~LoadCallbackLink() { m_DelegateLink = {}; m_AssetRef = {}; }                                                     \
  NullOptPtr<AssetType> Get() { return m_AssetRef.Resolve(); }                                                      \
  NullOptPtr<const AssetType> Get() const { return m_AssetRef.Resolve(); }                                          \
};                                                                                                                  \
                                                                                                                    \
                                                                                                                    \
using LoadCallback = Delegate<void, NullOptPtr<AssetType>>;                                                         \
                                                                                                                    \
static AssetReference<AssetType> Load(czstr file_path, bool load_deps = true);                                      \
static LoadCallbackLink LoadWithCallback(czstr file_path, LoadCallback && del, bool load_deps = true);              \
                                                                                                                    \
LoadCallbackLink AddLoadCallback(LoadCallback && del);                                                              \
                                                                                                                    \
private:                                                                                                            \
                                                                                                                    \
DelegateList<void, NullOptPtr<AssetType>> m_LoadCallbackList;                                                       \
void CallAssetLoadCallbacks() override;                                                                             \


#define ASSET_SOURCE_FUNCS(AssetType)                                                                               \
static AssetManager<AssetType> s_##AssetType##Manager;                                                              \
                                                                                                                    \
AssetReference<AssetType> AssetType::Load(czstr file_path, bool deps)                                               \
{                                                                                                                   \
  return AssetReference<AssetType>(s_##AssetType##Manager.LoadAsset(file_path, deps));                              \
}                                                                                                                   \
                                                                                                                    \
AssetType::LoadCallbackLink AssetType::LoadWithCallback(                                                            \
  czstr file_path, LoadCallback && del, bool deps)                                                                  \
{                                                                                                                   \
  AssetType * asset = s_##AssetType##Manager.LoadAsset(file_path, deps);                                            \
  return asset->AddLoadCallback(std::move(del));                                                                    \
}                                                                                                                   \
                                                                                                                    \
AssetType::LoadCallbackLink AssetType::AddLoadCallback(LoadCallback && del)                                         \
{                                                                                                                   \
  if (m_State == AssetState::kLoadError)                                                                            \
  {                                                                                                                 \
    del.Call(this);                                                                                                 \
  }                                                                                                                 \
  else if (m_State == AssetState::kLoaded)                                                                          \
  {                                                                                                                 \
    del.Call(this);                                                                                                 \
  }                                                                                                                 \
                                                                                                                    \
  return AssetType::LoadCallbackLink{                                                                               \
    m_LoadCallbackList.AddDelegate(std::move(del)), AssetReference<AssetType>(this) };                              \
}                                                                                                                   \
                                                                                                                    \
                                                                                                                    \
void AssetType::CallAssetLoadCallbacks()                                                                            \
{                                                                                                                   \
  m_LoadCallbackList.Call(this);                                                                                    \
  Asset::CallAssetLoadCallbacks();                                                                                  \
}                                                                                                                   \




