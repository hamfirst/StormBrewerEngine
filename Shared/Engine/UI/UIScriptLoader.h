
#pragma once

#include "Foundation/Script/ScriptState.h"
#include "Foundation/Script/ScriptInterface.h"

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

  void InitLoad(bool immediate_load, Delegate<void> && load_complete_callback);
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
  friend class UIManager;

  static const int kIdMask       = 0xFF000000;
  static const int kIndexMask    = 0x00FFFFFF;
  static const int kTextureId    = 0x01000000;
  static const int kBoundTexture = 0x02000000;
  static const int kAudioId      = 0x03000000;
  static const int kMusicId      = 0x04000000;
  static const int kFontId       = 0x05000000;
  static const int kAtlasId      = 0x06000000;
  static const int kSpriteId     = 0x07000000;

  enum State
  {
    kIdle,
    kLoadingScripts,
    kLoadingAssets,
    kComplete
  };

  State m_State;
  NotNullPtr<ScriptState> m_ScriptState;
  ScriptInterface m_LoaderInterface;

  std::vector<GenericBinaryResourcePtr> m_ScriptResources;

  std::vector<TextureAsset::AssetRef> m_TextureAssets;
  std::vector<AudioAsset::AssetRef> m_AudioAssets;
  std::vector<MusicAsset::AssetRef> m_MusicAssets;
  static int m_NextFontId;

  std::vector<AtlasPtr> m_AtlasAssets;
  std::vector<SpritePtr> m_SpriteAssets;

  Delegate<void> m_LoadCompleteCallback;
};
