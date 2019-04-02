#pragma once

#include "Foundation/Network/WebSocket.h"
#include "Foundation/Delegate/Delegate.h"

#include "Game/GameNetworkData.refl.h"
#include "Game/GameSimulationStats.refl.h"

#include "Lobby/GameServerMessages.refl.h"

using LobbyValidationCallback = Delegate<void, const Optional<GameServerAuthenticateUserSuccess> &>;

using LobbyTeamSwitchCallback = Delegate<void, uint64_t, uint64_t, int>;
using LobbyDisconnectCallback = Delegate<void, uint64_t, uint64_t>;
using LobbyKillGameCallback = Delegate<void, uint64_t>;
using LobbyResetGameCallback = Delegate<void, uint64_t>;
using LobbyChangeCreatorCallback = Delegate<void, uint64_t, const std::string &>;

enum class LobbyServerConnectionState
{
  kDisconnected,
  kConnecting,
  kAuthenticating,
  kConnected,
  kRelocateConnecting,
  kRelocating,
};

static const int kInvalidValidationRequestId = 0;

class LobbyServerConnection
{
public:
  LobbyServerConnection(const char * lobby_host);

  void Connect();
  void Update();

  bool IsConnected();
  bool WantsRedownload();

  void SetTeamSwitchCallback(LobbyTeamSwitchCallback callback);
  void SetDisconnectCallback(LobbyDisconnectCallback callback);
  void SetResetGameCallback(LobbyResetGameCallback callback);
  void SetKillGameCallback(LobbyKillGameCallback callback);
  void SetChangeCreatorCallback(LobbyChangeCreatorCallback callback);

  int RequestValidation(uint64_t user_token, LobbyValidationCallback && callback);
  void CancelValidation(int request_id);

  void RequestTeamSwitch(uint64_t user_id, uint64_t game_id, int team);
  void RequestRanomizeTeams(uint64_t game_id);
  void UpdateScore(uint64_t game_id, const std::string & score);

  void NotifyPlayerLeft(uint64_t user_id, uint64_t game_id);
  void SendStats(uint64_t account_id, GameSimulationStats & stats, const GameInstanceData & settings);
  void SendGameComplete(uint64_t game_id, bool complete, const std::vector<std::pair<uint64_t, GameSimulationStats>> & players, const std::vector<int> & team_scores);

protected:

  template <typename T>
  void SendMessage(const T & t);

  void Relocate(GameServerRelocate & msg);

  void ParseError();

private:
  LobbyServerConnectionState m_State;
  WebSocket m_WebSocket;
  std::string m_LobbyHost;

  bool m_WantsRedownload;

  std::vector<std::string> m_PendingMessages;
  uint64_t m_RelocationToken;

  time_t m_LastPingTime;

  int m_NextValidationId;
  std::unordered_map<int, LobbyValidationCallback> m_Validations;

  LobbyTeamSwitchCallback m_TeamSwitchCallback;
  LobbyDisconnectCallback m_DisconnectCallback;
  LobbyKillGameCallback m_KillGameCallback;
  LobbyResetGameCallback m_ResetGameCallback;
  LobbyChangeCreatorCallback m_ChangeCreatorCallback;
};