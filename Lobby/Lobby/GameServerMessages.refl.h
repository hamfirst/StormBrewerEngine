#pragma once

#include <string>
#include <vector>

#include <StormRefl/StormRefl.h>

#include "ProjectSettings/ProjectVersion.h"
#include "ProjectSettings/ProjectPorts.h"
#include "ProjectSettings/ProjectRandom.h"

#include "Game/GameNetworkData.refl.h"
#include "Lobby/GameData.refl.h"
#include "LobbyShared/SharedTypes.refl.h"


static const uint64_t kGameServerChallengePad = kProjectRandom1;
static const int kGameServerMinorVersion = 0;


enum class STORM_REFL_ENUM GameServerMessageType
{
  kIdentifyNew,
  kIdentifyRelocate,
  kRelocated,
  kPing,
  kCreateGame,
  kDestroyGame,
  kAuthRequest,
  kAuthResponse,
  kAuthUser,
  kAuthUserSuccess,
  kAuthUserFail,
  kRequestTeamSwitch,
  kTeamSwitch,
  kRandomizeTeams,
  kResetGame,
  kForceDisconnect,
  kUserDisconnected,
  kKillGame,
  kGameScore,
  kUserStats,
  kRelocate,
  kChangeCreator,
  kAcceptingNewPlayers,
  kGameResult,
};

struct GameServerIdentifyNew
{
  STORM_REFL;
  static const GameServerMessageType Type = GameServerMessageType::kIdentifyNew;
  int m_Version;
};

struct GameServerIdentifyRelocate
{
  STORM_REFL;
  static const GameServerMessageType Type = GameServerMessageType::kIdentifyRelocate;
  uint64_t m_RelocationKey;
};

struct GameServerRelocated
{
  STORM_REFL;
  static const GameServerMessageType Type = GameServerMessageType::kRelocated;
};

struct GameServerPing
{
  STORM_REFL;
  static const GameServerMessageType Type = GameServerMessageType::kPing;
};

struct GameServerAuthenticateRequest
{
  STORM_REFL;
  static const GameServerMessageType Type = GameServerMessageType::kAuthRequest;

  uint64_t m_Challenge = 0;
};

struct GameServerLobbySettings
{
  STORM_REFL;
  std::string m_LobbyServerIp = "127.0.0.1";
  int m_LobbyServerPort = LOBBY_GAME_PORT;
};

struct GameServerInfo
{
  STORM_REFL;
  std::string m_ServerName;
  std::string m_ServerZone;
  std::string m_ServerResourceId;
  std::string m_ExternalIp;
  int m_ExternalPort = DEFAULT_GAME_PORT;
};

struct GameServerCreateGame
{
  STORM_REFL;
  static const GameServerMessageType Type = GameServerMessageType::kCreateGame;
  GameInitSettings m_Settings;
  uint64_t m_GameId = 0;
  GameInfoTeamSizes m_TeamInfo;
};

struct GameServerDestroyGame
{
  STORM_REFL;
  static const GameServerMessageType Type = GameServerMessageType::kDestroyGame;
  uint64_t m_GameId = 0;
};

struct GameServerAuthenticateResponse
{
  STORM_REFL;
  static const GameServerMessageType Type = GameServerMessageType::kAuthResponse;

  GameServerInfo m_ServerInfo;
  uint64_t m_Challenge = 0;
};


struct GameServerAuthenticateUser
{
  STORM_REFL;
  static const GameServerMessageType Type = GameServerMessageType::kAuthUser;

  uint64_t m_GameId = 0;
  uint64_t m_UserId = 0;
  uint64_t m_JoinToken = 0;
  uint32_t m_ResponseId = 0;
};

struct GameServerAuthenticateUserSuccess
{
  STORM_REFL;
  static const GameServerMessageType Type = GameServerMessageType::kAuthUserSuccess;

  uint32_t m_ResponseId = 0;
  DDSKey m_GameId = 0;
  DDSKey m_UserId = 0;

  std::string m_Name;

#ifdef ENABLE_SQUADS
  std::string m_Squad;
#endif

  int m_Team = 0;

  int m_AdminLevel = 0;
  int m_Icon = 0;
  int m_Title = 0;
  int m_Celebration = 0;

  bool m_NewPlayer = false;

#ifdef NET_USE_LOADOUT
  GamePlayerLoadout m_Loadout;
#endif
};

struct GameServerAuthenticateUserFailure
{
  STORM_REFL;
  static const GameServerMessageType Type = GameServerMessageType::kAuthUserFail;

  uint32_t m_ResponseId;
};

struct GameServerRequestTeamSwitch
{
  STORM_REFL;
  static const GameServerMessageType Type = GameServerMessageType::kRequestTeamSwitch;
  uint64_t m_UserId = 0;
  uint64_t m_GameId = 0;
  int m_Team = 0;
  bool m_Force = false;
};

struct GameServerRandomizeTeams
{
  STORM_REFL;
  uint64_t m_GameId = 0;
  static const GameServerMessageType Type = GameServerMessageType::kRandomizeTeams;
};

struct GameServerResetGame
{
  STORM_REFL;
  uint64_t m_GameId;
  static const GameServerMessageType Type = GameServerMessageType::kResetGame;
};

struct GameServerTeamSwitch
{
  STORM_REFL;
  static const GameServerMessageType Type = GameServerMessageType::kTeamSwitch;
  uint64_t m_UserId;
  uint64_t m_GameId;
  int m_Team;
};

struct GameServerForceUserDisconnect
{
  STORM_REFL;
  static const GameServerMessageType Type = GameServerMessageType::kForceDisconnect;

  uint64_t m_UserId = 0;
  uint64_t m_GameId = 0;
};

struct GameServerUserDisconnected
{
  STORM_REFL;
  static const GameServerMessageType Type = GameServerMessageType::kUserDisconnected;

  uint64_t m_UserId = 0;
  uint64_t m_GameId = 0;
};

struct GameServerRelocate
{
  STORM_REFL;
  static const GameServerMessageType Type = GameServerMessageType::kRelocate;

  std::string m_HostAddr;
  int m_Port;
  uint64_t m_RelocationKey;
};

struct GameServerKillGame
{
  STORM_REFL;
  static const GameServerMessageType Type = GameServerMessageType::kKillGame;

  uint64_t m_GameId;
};

struct GameServerScore
{
  STORM_REFL;
  static const GameServerMessageType Type = GameServerMessageType::kGameScore;

  uint64_t m_GameId;
  std::string m_Score;
};

struct GameServerStats
{
  STORM_REFL;
  static const GameServerMessageType Type = GameServerMessageType::kUserStats;

  uint64_t m_AccountId;
  GameStatsData m_Stats;
  GameInitSettings m_Settings;
};

struct GameServerChangeCreator
{
  STORM_REFL;
  static const GameServerMessageType Type = GameServerMessageType::kChangeCreator;
  uint64_t m_GameId;
  std::string m_Creator;
};


struct GameServerAcceptingPlayers
{
  STORM_REFL;
  static const GameServerMessageType Type = GameServerMessageType::kAcceptingNewPlayers;
  uint64_t m_GameId;
  bool m_AcceptingPlayers;
};

struct GameServerResultPlayer
{
  STORM_REFL;
  uint64_t m_AccountId;
  int m_Team;
  GameStatsData m_Stats;
};

struct GameServerGameResult
{
  STORM_REFL;
  static const GameServerMessageType Type = GameServerMessageType::kGameResult;

  uint64_t m_GameId = 0;
  bool m_GameCompleted = false;
  std::vector<int> m_TeamScores;
  std::vector<GameServerResultPlayer> m_ConnectedUsers;
};

