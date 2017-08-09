#pragma once

#include <StormNet/NetReflectionStruct.h>
#include <StormNet/NetReflectionTypeDatabase.h>

#include <StormNet/NetReflection.h>
#include <StormNet/NetMessageSender.h>

#include "Game/GameNetworkSettings.h"

#include "Foundation/Common.h"

static const int kMaxPlayers = 4;
static const int kMaxTeams = 4;
static const int kServerUpdateRate = 8;

#if (NET_MODE == NET_MODE_GGPO)
static const int kMaxRewindFrames = 10;
#endif

#if (NET_MODE == NET_MODE_TURN_BASED_DETERMINISTIC)
static const int kTurnMaxTime = 60 * 50;
static const int kTurnUpdateTime = 60 * 2;
#endif

#ifdef NET_USE_COUNTDOWN
static const int kMaxCountdown = 180;
#endif

#ifdef NET_USE_ROUND_TIMER
static const int kMaxRoundTimer = 60 * 90;
#endif

class GameStage;

struct GameInitSettings
{
  uint8_t m_StageIndex;
  NET_REFL;
};

// Data sent from the server to the client
struct ClientLocalData
{
  NET_REFL;
  NetRangedNumber<int, 0, kMaxPlayers> m_PlayerIndex;
};

struct ClientInput
{
  NET_REFL;
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

struct GameInput
{
  ClientInput m_PlayerInput[kMaxPlayers];
};

struct PackageInfo
{
  NET_REFL;
  uint8_t m_Town;
  bool m_PickedUp;
};

struct DeliveryInfo
{
  NET_REFL;
  uint8_t m_Town;
  uint8_t m_Reward;
};

struct AIPlayerInfo
{
  NET_REFL;
};

struct GamePlayer
{
  NET_REFL;

  std::string m_UserName;
  NetRangedNumber<int, 0, kMaxTeams - 1> m_Team;
  NetOptional<AIPlayerInfo> m_AIPlayerInfo;
  bool m_Ready;
};

struct GameInstanceData
{
  NET_REFL;

  NetSparseList<GamePlayer, kMaxPlayers> m_Players;

  bool m_Started = false;
  NetRangedNumber<int, -1, kMaxTeams> m_WiningTeam = -1;

#ifdef NET_USE_COUNTDOWN
  NetRangedNumber<int, 0, kMaxCountdown> m_Countdown = 0;
#endif

#ifdef NET_USE_ROUND_TIMER
  NetRangedNumber<int, 0, kMaxRoundTimer> m_RoundTimer = 0;
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
