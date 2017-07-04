#pragma once

#include <StormNet/NetReflectionStruct.h>
#include <StormNet/NetReflectionTypeDatabase.h>

#include <StormNet/NetReflection.h>
#include <StormNet/NetMessageSender.h>

#include "Game/GameNetworkSettings.h"

#include "Foundation/Common.h"

static const int kMaxPlayers = 10;
static const int kMaxTeams = 2;
static const int kServerUpdateRate = 8;

#if (NET_MODE == NET_MODE_GGPO)
static const int kMaxRewindFrames = 10;
#endif

#if (NET_MODE == NET_MODE_TURN_BASED_DETERMINISTIC)
static const int kTurnMaxTime = 60 * 50;
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

struct GamePlayer
{
  NET_REFL;

  std::string m_Name;
  NetRangedNumber<int, 0, kMaxTeams - 1> m_Team;
};

struct GameGlobalData
{
  NET_REFL;

  bool m_Started = false;

#if NET_MODE == NET_MODE_GGPO
  int m_FrameCount = 0;
#elif (NET_MODE == NET_MODE_TURN_BASED_DETERMINISTIC)
  NetRangedNumber<int, -1, kMaxTeams - 1> m_ActiveTurn = -1;


#ifdef NET_MODE_TURN_BASED_RUN
  bool m_Running = false;
  NetRangedNumber<int, 0, kTurnMaxTime> m_TimeExpiration = 0;
#endif

#endif

  NetSparseList<GamePlayer, kMaxPlayers> m_Players;
};
