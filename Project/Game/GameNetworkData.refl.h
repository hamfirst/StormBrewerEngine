#pragma once


#include "Foundation/Common.h"

#include "StormNet/NetReflectionStruct.h"
#include "StormNet/NetReflectionTypeDatabase.h"

#include "StormNet/NetReflection.h"
#include "StormNet/NetMessageSender.h"

#include "Game/GameServerTypes.h"

#include "ProjectSettings/ProjectNetworkSettings.h"
#include "ProjectSettings/ProjectPerspective.h"

#if PROJECT_PERSPECTIVE == PERSPECTIVE_SIDESCROLLER
#define PLATFORMER_MOVEMENT
#endif

#if (NET_MODE == NET_MODE_GGPO)
static const int kMaxRewindFrames = 20;
static const int kMaxHistoryFrames = 30;
#endif

#if (NET_MODE == NET_MODE_TURN_BASED_DETERMINISTIC)
static const int kTurnMaxTime = 60 * 50;
static const int kTurnUpdateTime = 60 * 2;
#endif

#ifdef NET_USE_COUNTDOWN
static const int kMaxCountdown = 180;
#endif

#ifdef NET_USE_ROUND_TIMER
static const int kMaxRoundTimer = 60 * 60 * 5;

enum STORM_REFL_ENUM class RoundState
{
  kPreRound,
  kRound,
  kPostRound,
};
#endif

class GameStage;

struct GameInitSettings
{
  NET_REFL;
  uint8_t m_StageIndex = 0;

#ifdef NET_USE_PLAYER_LIMIT
  uint8_t m_PlayerCount = 0;
#endif

#ifdef NET_USE_SCORE_LIMIT
  uint16_t m_ScoreLimit = 0;
#endif

#ifdef NET_USE_SCORE_LIMIT
  uint16_t m_TimeLimit = 0;
#endif
};

// Data sent from the server to the client
struct ClientLocalData
{
  NET_REFL;
  NetRangedNumber<int, -1, kMaxPlayers> m_PlayerIndex = -1;

#ifdef NET_ALLOW_OBSERVERS
  NetRangedNumber<int, -1, kMaxPlayers> m_ObserverIndex = -1;
#endif
};

struct ClientInput
{
  NET_REFL;

#ifdef PLATFORMER_MOVEMENT

  bool m_JumpHeld;
  GameNetVal m_XInput;
  GameNetVal m_YInput;

#else

  GameNetVal m_InputAngle;
  GameNetVal m_InputStr;

#endif
};

// Data sent from the client to the server
struct ClientAuthData
{
  NET_REFL;

#if (NET_MODE == NET_MODE_GGPO)
  int m_Frame;
#endif

  ClientInput m_Input;
};

struct AIPlayerInfo
{
  NET_REFL;
};

struct GamePlayerLoadout
{
  NET_REFL;
};

struct GamePlayer
{
  NET_REFL;

  std::string m_UserName;
  NetRangedNumber<int, 0, kMaxTeams - 1> m_Team;
  GamePlayerLoadout m_Loadout;
};

#ifdef NET_ALLOW_OBSERVERS
struct GameObserver
{
  NET_REFL;
  std::string m_UserName;
};
#endif

struct GameInstanceLowFrequencyData
{
  NET_REFL;
  GameInitSettings m_Settings;
  NetSparseList<GamePlayer, kMaxPlayers> m_Players;
#ifdef NET_ALLOW_OBSERVERS
  NetSparseList<GameObserver, 128> m_Observers;
#endif

};

struct GameInstanceData
{
  NET_REFL;

  NetSparseList<AIPlayerInfo, kMaxPlayers> m_AIPlayerInfo;

#ifdef NET_USE_SCORE
  NetRangedNumber<int, 0, kMaxScore> m_Score[kMaxTeams];
#endif
  NetOptional<NetRangedNumber<int, -1, kMaxTeams>> m_WiningTeam;

#ifdef NET_USE_COUNTDOWN
  NetRangedNumber<int, 0, kMaxCountdown> m_Countdown = 0;
#endif

#ifdef NET_USE_ROUND_TIMER
  NetEnum<RoundState> m_RoundState;
  NetRangedNumber<int, 0, kMaxRoundTimer> m_RoundTimer = kMaxCountdown;
#endif

#ifdef NET_USE_RANDOM
  NetRandom m_Random;
#endif

#if NET_MODE == NET_MODE_GGPO
  int m_FrameCount = 0;
#elif (NET_MODE == NET_MODE_TURN_BASED_DETERMINISTIC)
  NetRangedNumber<int, -1, kMaxTeams - 1> m_ActiveTurn = -1;


#ifdef NET_MODE_TURN_BASED_RUN
  bool m_Running = false;
  NetRangedNumber<int, 0, kTurnMaxTime> m_TimeExpiration = 0;
#endif

#endif
};

