#pragma once

#include <string>
#include <vector>

#include <StormRefl/StormRefl.h>

#include "Game/GameNetworkData.refl.h"
#include "Lobby/GameData.refl.h"


static const uint64_t kGameServerChallengePad = 0xfd3473e1a57de6ff;
static const int kGameServerVersion = 5;

struct GameServerMapData
{
  STORM_REFL;
  std::string m_Map;
  std::string m_Creator;
  int m_GameMode;
  int m_ScoreLimit;
  int m_TimeLimit;
  int m_MaxPlayers;
  int m_MaxTeams;
};

enum STORM_REFL_ENUM class GameServerMessageType
{
  kIdentifyNew,
  kIdentifyRelocate,
  kRelocated,
  kPing,
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

struct GameServerAuthenticateResponse
{
  STORM_REFL;
  static const GameServerMessageType Type = GameServerMessageType::kAuthResponse;

  uint64_t m_Challenge = 0;

  std::string m_Name;
  std::string m_Zone;
  std::string m_ResourceId;
  std::string m_ExternalIp;
};

struct GameServerAuthenticateUser
{
  STORM_REFL;
  static const GameServerMessageType Type = GameServerMessageType::kAuthUser;

  uint64_t m_UserToken = 0;
  uint32_t m_ResponseId = 0;
};

struct GameServerAuthenticateUserSuccess
{
  STORM_REFL;
  static const GameServerMessageType Type = GameServerMessageType::kAuthUserSuccess;

  uint32_t m_ResponseId = 0;
  uint64_t m_UserId = 0;
  uint64_t m_AccountId = 0;
  uint64_t m_GameId = 0;

  std::string m_Name;
  std::string m_Squad;
  std::string m_Creator;
  int m_RequiredPlayers = 0;
  int m_Team = 0;
  int m_AdminLevel = 0;
  int m_Celebration = 0;
  bool m_NewPlayer = false;

  GameInitSettings m_GameData;
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

struct GameServerMeta
{
  STORM_REFL;
  std::string m_LobbyServerIp = "127.0.0.1";
  std::string m_ServerKey;
  std::string m_ServerName;
  std::string m_ServerZone;
  std::string m_ServerResourceId;
  std::string m_ExternalIp;
};
