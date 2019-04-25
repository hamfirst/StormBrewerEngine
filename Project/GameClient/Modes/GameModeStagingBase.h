
#pragma once

#include "GameClient/Modes/GameMode.h"
#include "Game/GameNetworkData.refl.h"

#include "Engine/UI/UIManager.h"
#include "Engine/UI/UITextureBinding.h"

class GameModeStagingBase : public GameMode
{
public:
  GameModeStagingBase(GameContainer & game);

  void OnAssetsLoaded() override;
  void Update() override;
  void Render() override;

protected:

  virtual bool AllowChat() { return true; }
  virtual bool AllowPlayerList() { return true; }
  virtual bool AllowLoadout() { return true; }
  virtual bool AllowReady() { return true; }
  virtual bool AllowMapChange() { return true; }
  virtual bool AllowGameTimer() { return false; }

  virtual std::string GetGameName() { return ""; }
  virtual std::string GetGameCode() { return ""; }
  virtual std::string GetGameTimer() { return ""; }
  virtual int GetTeamCount() { return kMaxTeams; }
  virtual int GetPlayerCount(int team_index) { return 0; }
  virtual int GetPlayerMaxCount(int team_index) { return kMaxPlayers; }
  virtual int GetPlayerId(int team, int player_index);
  virtual std::string GetTeamName(int team, int player_index);
  virtual std::tuple<float, float, float> GetTeamColor(int team);
  virtual std::tuple<float, float, float> GetTeamColorDark(int team);
  virtual std::string GetPlayerName(int player_id);
  virtual int GetPlayerState(int player_id);
  virtual bool GetPlayerReady(int player_id);
  virtual std::unordered_map<std::string, std::string> GetPlayerActions(int player_id);

  virtual void Ready(bool ready) {}
  virtual void SendChat(const std::string & chat) {}

  virtual void DefaultAction(int player_id) {}

  std::tuple<int, int, int, int> GetCurrentOptions();
  void LoadMap(int map_index);
  void SetMapOptions(int player_count, int score_limit, int time_limit);
  void CommitMapChanges();
  void CancelMapChanges();

  void Quit();

protected:

  virtual GameInitSettings GetAppliedOptions() { return {}; };
  virtual void ChangeMapOptions(const GameInitSettings & new_settings) {};

protected:

  NotNullPtr<ScriptInterface> m_ScriptInterface = nullptr;
  AssetReference<TextureAsset> m_MapImage;
  Optional<UITextureBinding> m_MapImageBinding;

  GameInitSettings m_Settings;
};

