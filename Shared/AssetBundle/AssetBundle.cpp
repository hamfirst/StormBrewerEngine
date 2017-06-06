
#include "Shared/SharedCommon.h"
#include "Shared/AssetBundle/AssetBundle.h"

#include "Runtime/Sprite/SpriteResource.h"

NullOptPtr<TextureAsset> GetAssetBundleTexture(Any & load_data);
void DrawAssetBundleTexture(Any & load_data, Vector2 pos, RenderState & render_state, RenderUtil & render_util);
void PlayAssetBundleSound(Any & load_data, float volume, float pan);

AssetBundle::AssetBundle()
{

}

AssetBundle::~AssetBundle()
{

}

void AssetBundle::DrawTexture(czstr name, Vector2 pos, RenderState & render_state, RenderUtil & render_util)
{
  auto name_hash = crc32(name);
  for (std::size_t index = 0, end = m_AssetNames.size(); index < end; ++index)
  {
    if (m_AssetNames[index] == name_hash)
    {
      DrawAssetBundleTexture(m_LoadData[index], pos, render_state, render_util);
      return;
    }
  }
}

void AssetBundle::PlaySoundEffect(czstr name, float volume, float pan)
{
  auto name_hash = crc32(name);
  for (std::size_t index = 0, end = m_AssetNames.size(); index < end; ++index)
  {
    if (m_AssetNames[index] == name_hash)
    {
      PlayAssetBundleSound(m_LoadData[index], volume, pan);
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


bool AssetBundle::AllLoadedSuccessfully()
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

bool AssetBundle::LoadingComplete()
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
