#pragma once

#include "Foundation/Network/WebSocket.h"
#include "Foundation/Delegate/Delegate.h"

#include "Game/GameNetworkData.refl.h"

#include "Lobby/LobbyConfig.h"
#include "Lobby/UserConnectionMessages.refl.h"

#include <ctime>

enum class LobbyClientConnectionState
{
  kDisconnected,
  kLoadBalancerConnecting,
  kConnecting,
  kAuthenticating,
  kIdentifying,
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

  LobbyClientState GetState();

protected:
  template <typename T>
  void SendMessage(T & t, czstr msg);

  void Relocate(UserMessageRelocate & msg);

  void ParseError();

private:
  LobbyClientConnectionState m_State;
  LobbyClientState m_ClientState;

  WebSocket m_WebSocket;

  LobbyLoginMode m_LoginMode;
  std::string m_LoginToken;

  std::string m_LoadBalancerHost;

  std::vector<std::string> m_PendingMessages;
  uint64_t m_RelocationToken;

  time_t m_LastPingTime;
};
