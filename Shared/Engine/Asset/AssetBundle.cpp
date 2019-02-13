
#include "Engine/EngineCommon.h"
#include "Engine/Asset/AssetBundle.h"
#include "Engine/Asset/TextureAsset.h"
#include "Engine/Rendering/RenderState.h"
#include "Runtime/Sprite/SpriteResource.h"

NullOptPtr<TextureAsset> GetAssetBundleTexture(Any & load_data);
void DrawAssetBundleTexture(Any & load_data, Vector2 pos, RenderState & render_state);
void PlayAssetBundleSound(Any & load_data, VolumeCategory cat, float volume, float pan);

AssetBundle::AssetBundle()
{

}

AssetBundle::~AssetBundle()
{

}

void AssetBundle::DrawTexture(czstr name, Vector2 pos, RenderState & render_state)
{
  auto name_hash = crc32(name);
  for (std::size_t index = 0, end = m_AssetNames.size(); index < end; ++index)
  {
    if (m_AssetNames[index] == name_hash)
    {
      DrawAssetBundleTexture(m_LoadData[index], pos, render_state);
      return;
    }
  }
}

void AssetBundle::PlaySoundEffect(czstr name, VolumeCategory cat, float volume, float pan)
{
  auto name_hash = crc32(name);
  for (std::size_t index = 0, end = m_AssetNames.size(); index < end; ++index)
  {
    if (m_AssetNames[index] == name_hash)
    {
      PlayAssetBundleSound(m_LoadData[index], cat, volume, pan);
      return;
    }
  }
}

NullOptPtr<TextureAsset> AssetBundle::GetTexture(czstr name)
{
  auto name_hash = crc32(name);
  for (std::size_t index = 0, end = m_AssetNames.size(); index < end; ++index)
  {
    if (m_AssetNames[index] == name_hash)
    {
      return GetAssetBundleTexture(m_LoadData[index]);
    }
  }
  return nullptr; 
}

NullOptPtr<SpriteResource> AssetBundle::GetSprite(czstr name)
{
  auto name_hash = crc32(name);
  for (std::size_t index = 0, end = m_AssetNames.size(); index < end; ++index)
  {
    if (m_AssetNames[index] == name_hash)
    {
      auto load_link = m_LoadData[index].Get<SpriteLoadLink>();
      return load_link ? load_link->GetResource() : nullptr;
    }
  }
  return nullptr;
}

bool AssetBundle::AllLoadedSuccessfully() const
{
  for (auto b : m_LoadSuccess)
  {
    if (!b)
    {
      return false;
    }
  }

  return true;
}

bool AssetBundle::LoadingComplete() const
{
  for (auto b : m_LoadComplete)
  {
    if (!b)
    {
      return false;
    }
  }

  return true;
}

bool AssetBundle::IsLoaded() const
{
  return LoadingComplete();
}


void DrawAssetBundleTexture(Any & load_data, Vector2 pos, RenderState & render_state)
{
  auto load_link = load_data.Get<TextureAsset::LoadCallbackLink>();
  if (load_link == nullptr)
  {
    return;
  }

  auto texture = load_link->Get();
  if (texture == nullptr || texture->IsLoaded() == false)
  {
    return;
  }

  render_state.DrawDebugTexturedQuad(Box::FromFrameCenterAndSize(pos, texture->GetSize()), Color(255, 255, 255, 255), texture->GetTexture());
}

NullOptPtr<TextureAsset> GetAssetBundleTexture(Any & load_data)
{
  auto load_link = load_data.Get<TextureAsset::LoadCallbackLink>();
  if (load_link == nullptr)
  {
    return nullptr;
  }
  
  auto texture = load_link->Get();
  if (texture == nullptr || texture->IsLoaded() == false)
  {
    return nullptr;
  }

  return texture;
}
