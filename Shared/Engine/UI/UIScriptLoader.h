
#pragma once

#include "Foundation/Script/ScriptState.h"

#include "Engine/Asset/TextureAsset.h"
#include "Engine/Asset/AudioAsset.h"
#include "Engine/Asset/MusicAsset.h"
#include "Engine/Asset/FontAsset.h"

#include "Runtime/Atlas/AtlasResource.h"
#include "Runtime/Sprite/SpriteResource.h"
#include "Runtime/BinaryResource/GenericBinaryResource.h"

class UIScriptLoader
{
public:
  UIScriptLoader(NotNullPtr<ScriptState> script_state);

  void InitLoad();
  void Update();

  bool AllScriptsLoaded() const;
  bool AllAssetsLoaded() const;
  bool Complete() const;

  int LoadTexture(std::string path);
  int LoadAudio(std::string path);
  int LoadMusic(std::string path);
  int LoadFont(std::string path);

  int LoadAtlas(std::string path);
  int LoadSprite(std::string path);

private:

  enum State
  {
    kIdle,
    kLoadingScripts,
    kLoadingAssets,
    kComplete
  };

  State m_State;
  NotNullPtr<ScriptState> m_ScriptState;

  std::vector<GenericBinaryResourcePtr> m_ScriptResources;

  std::vector<TextureAsset::AssetRef> m_TextureAssets;
  std::vector<AudioAsset::AssetRef> m_AudioAssets;
  std::vector<MusicAsset::AssetRef> m_MusicAssets;
  std::vector<FontAsset::AssetRef> m_FontAssets;

  std::vector<AtlasPtr> m_AtlasAssets;
  std::vector<SpritePtr> m_SpriteAssets;
};
