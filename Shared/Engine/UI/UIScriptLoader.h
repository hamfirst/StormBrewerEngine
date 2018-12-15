
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

  void DebugPrint();
  int LoadTexture(std::string path);
  int LoadAudio(std::string path);
  int LoadMusic(std::string path);
  int LoadFont(std::string path, int size);

  int LoadAtlas(std::string path);
  int LoadSprite(std::string path);

private:

  friend class UIScriptInterface;

  static const int kIdMask    = 0xFF000000;
  static const int kIndexMask = 0x00FFFFFF;
  static const int kTextureId = 0x01000000;
  static const int kAudioId   = 0x02000000;
  static const int kMusicId   = 0x03000000;
  static const int kFontId    = 0x04000000;
  static const int kAtlasId   = 0x05000000;
  static const int kSpriteId  = 0x06000000;

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
  int m_NextFontId = 0;

  std::vector<AtlasPtr> m_AtlasAssets;
  std::vector<SpritePtr> m_SpriteAssets;
};