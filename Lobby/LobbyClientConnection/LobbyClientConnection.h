#pragma once

#include "Foundation/Network/WebSocket.h"
#include "Foundation/Delegate/Delegate.h"
#include "Foundation/Optional/Optional.h"

#include "Game/GameNetworkData.refl.h"

#include "LobbyShared/SharedTypes.refl.h"

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

enum class LobbyRelocationState
{
  kNotRelocating,
  kConnecting,
  kAuthenticating,
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

struct LobbyClientConnectionSettings
{
  LobbyLoginMode m_LoginMode;
  std::string m_Token;
  std::string m_LoadBalancerHostName;
};

class LobbyClientConnection
{
public:
  explicit LobbyClientConnection(const LobbyClientConnectionSettings & settings);

  void Connect();
  void Update();

  LobbyClientState GetState() const;
  const std::string & GetConnectionError() const;

  const Optional<UserLocalData> & GetUserLocalData() const { return m_UserLocalData; }
  const Optional<GameInfo> & GetGameInfo() { return m_GameInfo; }
  const Optional<RMergeList<WelcomeInfoTab>> & GetWelcomeInfo() { return m_WelcomeInfo; }
  const Optional<RMap<DDSKey, GameListGame>> & GetGameList() { return m_GameList; }
  const Optional<GameListGame> & GetGameListPreview() { return m_GameListPreview; }

  void SetLatencySamples(const std::vector<int> & samples);

  void SendNewUserName(const std::string_view & name);
  void SendCreatePrivateGame(const GameInitSettings & settings, const std::string_view & password);
  void SendJoinPrivateGame(uint32_t join_code, const std::string_view & password, bool observer);
  void SendJoinMatchmaker(uint32_t playlist_mask, bool ranked);

  void SendGameReady(bool ready);
  void SendGameStart();
  void SendGameChangeLoadout(const GamePlayerLoadout & loadout);
  void SendGameChangeSettings(const GameInitSettings & settings);
  void SendGameTeamSwitch(DDSKey user_id, int team);
  void SendGameKickUser(DDSKey user_id);
  void SendGameChat(const std::string_view & msg);

  void SetLocalDataUpdateCallback(Delegate<void> & cb) { m_LocalDataUpdateCallback = cb; }
  void SetGameJoinCallback(Delegate<void> & cb) { m_GameJoinCallback = cb; }
  void SetGameDataUpdateCallback(Delegate<void> & cb) { m_GameDataUpdateCallback = cb; }
  void SetGameListUpdateCallback(Delegate<void> & cb) { m_GameListUpdateCallback = cb; }
  void SetWelcomeInfoUpdateCallback(Delegate<void> & cb) { m_WelcomeInfoUpdateCallback = cb; }
  void SetGamePreviewUpdateCallback(Delegate<void> & cb) { m_GamePreviewUpdateCallback = cb; }
  void SetGamePreviewCancelCallback(Delegate<void> & cb) { m_GamePreviewCancelCallback = cb; }

  void SetNotificationCallback(const Delegate<void, const std::string_view &> & cb) { m_NotificationCallback = cb; }
  void SetServerMessageCallback(const Delegate<void, const std::string_view &> & cb) { m_ServerMessageCallback = cb; }
  void SetServerTextCallback(const Delegate<void, const std::string_view &> & cb) { m_ServerTextCallback = cb; }
  void SetRuntimeErrorCallback(const Delegate<void, const std::string_view &> & cb) { m_RuntimeErrorCallback = cb; }

  void SetLaunchGameCallback(const Delegate<void, const std::string_view &, int, DDSKey, DDSKey, DDSKey> & cb) { m_LaunchGameCallback = cb; }
  void SetResetGameCallback(const Delegate<void> & cb) { m_ResetGameCallback = cb; }

#ifdef ENABLE_REWARDS
  void SetXPCallback(const Delegate<void, int, int, bool, const UserXPGain &> & cb) { m_XPCallback = cb; }
#endif

  void SetGameChatCallback(const Delegate<void, const std::string_view &, const std::string_view &, int, int> & cb) { m_GameChatCallback = cb; }
  void SetChatCallback(const Delegate<void, DDSKey, const std::string_view &, const std::string_view &, int, int, time_t> & cb) { m_ChatCallback = cb; }

  void SetStatsCallback(const Delegate<void, const std::string_view &, const GameStatsData &, int> & cb) { m_StatsCallback = cb; }

protected:
  template <typename T>
  void SendMessage(T & t, czstr msg);

  void Relocate(UserMessageRelocate & msg);

  void ParseError();
  void SetDisconnected(czstr error_message);

private:
  LobbyClientConnectionState m_State;
  LobbyClientState m_ClientState;

  LobbyRelocationState m_RelocationState;
  std::vector<std::string> m_PendingMessages;
  uint64_t m_RelocationToken;

  WebSocket m_WebSocket;

  std::string m_LoadBalancerHost;
  LobbyLoginMode m_LoginMode;
  std::string m_LoginToken;

  std::vector<int> m_LatencySamples;

  Optional<UserLocalData> m_UserLocalData;
  Optional<GameInfo> m_GameInfo;
  Optional<RMergeList<WelcomeInfoTab>> m_WelcomeInfo;
  Optional<RMap<DDSKey, GameListGame>> m_GameList;
  Optional<GameListGame> m_GameListPreview;

  Delegate<void> m_LocalDataUpdateCallback;
  Delegate<void> m_GameJoinCallback;
  Delegate<void> m_GameDataUpdateCallback;
  Delegate<void> m_GameListUpdateCallback;
  Delegate<void> m_WelcomeInfoUpdateCallback;
  Delegate<void> m_GamePreviewUpdateCallback;
  Delegate<void> m_GamePreviewCancelCallback;

  Delegate<void, const std::string_view &> m_NotificationCallback;
  Delegate<void, const std::string_view &> m_ServerMessageCallback;
  Delegate<void, const std::string_view &> m_ServerTextCallback;
  Delegate<void, const std::string_view &> m_RuntimeErrorCallback;

  Delegate<void, const std::string_view &, int, DDSKey, DDSKey, DDSKey> m_LaunchGameCallback;
  Delegate<void> m_ResetGameCallback;

#ifdef ENABLE_REWARDS
  Delegate<void, int, int, bool, const UserXPGain &> m_XPCallback;
#endif

  Delegate<void, const std::string_view &, const std::string_view &, int, int> m_GameChatCallback;
  Delegate<void, DDSKey, const std::string_view &, const std::string_view &, int, int, time_t> m_ChatCallback;

  Delegate<void, const std::string_view &, const GameStatsData &, int> m_StatsCallback;


  std::string m_ConnectionError;
  time_t m_LastPingTime;
  int m_GameListPreviewRequestId = 0;
};
