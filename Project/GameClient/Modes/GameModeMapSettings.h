
#pragma once

#include "GameClient/Modes/GameModeOnlineBase.h"
#include "Game/NetworkEvents/GameNetworkData.refl.h"

#include "Engine/UI/UIManager.h"
#include "Engine/UI/UITextureBinding.h"

enum class GameModeMapSettingsNextScreen
{
  kOfflineStaging,
  kPrivateGame,
};

class GameModeMapSettings : public GameModeOnlineBase
{
public:
  GameModeMapSettings(GameContainer & game, GameModeMapSettingsNextScreen next_screen);

  void Initialize() override;
  void Deinit() override;
  void OnAssetsLoaded() override;

  void Update() override;
  void Render() override;

protected:

  void Back();
  void Submit();
  void LoadMap(int map_index);
  void SetMapOptions(int player_count, int score_limit, int time_limit);

private:

  GameModeMapSettingsNextScreen m_NextScreen;
  NotNullPtr<ScriptInterface> m_ScriptInterface;
  AssetReference<TextureAsset> m_MapImage;
  Optional<UITextureBinding> m_MapImageBinding;

  GameInitSettings m_Settings;
};

