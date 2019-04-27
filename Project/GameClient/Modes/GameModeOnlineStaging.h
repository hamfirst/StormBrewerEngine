#pragma once

#include "Foundation/Time/StopWatch.h"
#include "Foundation/Sequencer/Sequencer.h"

#include "GameClient/Modes/GameModeStagingBase.h"

#include "LobbyShared/SharedTypes.refl.h"

#include "Engine/UI/UIManager.h"

class GameModeOnlineStaging : public GameModeStagingBase
{
public:
  GameModeOnlineStaging(GameContainer & game);
  ~GameModeOnlineStaging() override;
  
private:
  bool IsOnline() override { return true; }
  bool AllowChat() override { return true; }
  bool AllowPlayerList() override { return true; }

  bool AllowLoadout() override;
  bool AllowReady() override;
  bool AllowMapChange() override;
  bool AllowGameTimer() override;

  std::string GetGameName() override;
  std::string GetGameCode() override;
  std::string GetGameTimer() override;
  int GetTeamCount() override;
  int GetPlayerCount(int team_index) override;
  int GetPlayerMaxCount(int team_index) override;
  int GetPlayerId(int team, int player_index) override;
  std::string GetPlayerName(int player_id) override;
  int GetPlayerState(int player_id) override;
  bool GetPlayerReady(int player_id) override;
  std::unordered_map<std::string, std::string> GetPlayerActions(int player_id) override;

  void Ready(bool ready) override;
  void SendChat(const std::string & chat) override;

  bool TransitionToNextState() override;
  void Quit() override;
private:

  void UpdateGameInfo();
  NullOptPtr<GameMember> FindMember(int player_id);

private:

  GameInfo m_GameInfo;
  bool m_IsGameLeader = false;
};