#pragma once

#include "Foundation/Network/WebSocket.h"
#include "Foundation/Delegate/Delegate.h"

#include "Game/GameNetworkData.refl.h"

#include "Lobby/LobbyConfig.h"
#include "Lobby/User.refl.h"
#include "Lobby/UserConnectionMessages.refl.h"

#include <ctime>

enum class LobbyClientConnectionState
{
  kDisconnected,
  kLoadBalancerConnecting,
  kConnecting,
  kAuthenticating,
  kIdentifying,
  kIdentifyingResponse,
  kWaitingForLatencySamples,
  kConnected,
};

enum class LobbyClientState
{
  kDisconnected,
  kConnecting,
  kNewUser,
  kNewUserRepick,
  kCreatingAccount,
  kConnected,
  kInGame,
  kStartedGame,
};

enum class LobbyLoginMode
{
#ifdef ENABLE_AUTH_GUEST
  kGuest,
#endif

#ifdef ENABLE_AUTH_STEAM
  kSteam,
#endif
};

class LobbyClientConnection
{
public:
  LobbyClientConnection(LobbyLoginMode login_mode, std::string token, std::string load_balancer_hostname);

  void Connect();
  void Update();

  LobbyClientState GetState() const;

  void SetLatencySamples(const std::vector<int> & samples);

  void SendNewUserName(const std::string_view & name);
  void SendJoinMatchmadeGame(int playlist, bool ranked);
  void SendCreatePrivateGame(const GameInitSettings & settings);
  void SendJoinPrivateGame(uint32_t join_code);

  void SendGameReady(bool ready);
  void SendGameStart();
  void SendGameChangeLoadout(const GamePlayerLoadout & loadout);
  void SendGameChangeSettings(const GameInitSettings & settings);
  void SendGameTeamSwitch(DDSKey user_id, int team);
  void SendGameKickUser(DDSKey user_id);
  void SendGameChat(const std::string_view & msg);

protected:
  template <typename T>
  void SendMessage(T & t, czstr msg);

  void Relocate(UserMessageRelocate & msg);

  void ParseError();

private:
  LobbyClientConnectionState m_State;
  LobbyClientState m_ClientState;

  WebSocket m_WebSocket;
  UserLocalData m_UserLocalData;

  LobbyLoginMode m_LoginMode;
  std::string m_LoginToken;

  std::string m_LoadBalancerHost;

  std::vector<int> m_LatencySamples;

  std::vector<std::string> m_PendingMessages;
  uint64_t m_RelocationToken;

  time_t m_LastPingTime;
};
