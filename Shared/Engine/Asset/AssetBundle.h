#pragma once

#include "Engine/EngineCommon.h"
#include "Engine/Audio/VolumeCategory.h"
#include "Foundation/Any/Any.h"

class RenderState;

class AnimationState;
class TextureAsset;
class MusicAsset;
class SpriteResource;

class AssetBundle
{
public:

  AssetBundle();
  ~AssetBundle();

  AssetBundle(const AssetBundle & rhs) = delete;
  AssetBundle(AssetBundle && rhs) = delete;

  AssetBundle & operator =(const AssetBundle & rhs) = delete;
  AssetBundle & operator =(AssetBundle && rhs) = delete;

  template <typename AssetType>
  void LoadAsset(czstr file_path, czstr name = "")
  {
    m_LoadSuccess.push_back(false);
    m_LoadComplete.push_back(false);
    m_AssetNames.push_back(crc32(name));
    auto load_data = AssetType::LoadWithCallback(file_path, [this, index = m_LoadData.size()](NotNullPtr<AssetType> asset) 
    { 
      m_LoadSuccess[index] = asset->IsLoaded();
      m_LoadComplete[index] = true;
    });

    m_LoadData.emplace_back(Any(std::move(load_data)));
  }

  void DrawTexture(czstr name, Vector2 pos, RenderState & render_state);
  void PlaySoundEffect(czstr name, VolumeCategory cat = VolumeCategory::kSoundEffects, float volume = 1.0f, float pan = 0.0f);
  NullOptPtr<TextureAsset> GetTexture(czstr name);
  NullOptPtr<SpriteResource> GetSprite(czstr name);

  bool AllLoadedSuccessfully() const;
  bool LoadingComplete() const;
  bool IsLoaded() const;

private:

  std::vector<bool> m_LoadSuccess;
  std::vector<bool> m_LoadComplete;
  std::vector<Any> m_LoadData;
  std::vector<uint32_t> m_AssetNames;
};

