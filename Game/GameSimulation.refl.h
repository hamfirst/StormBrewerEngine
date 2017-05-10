#pragma once

#include <StormNet/NetReflectionStruct.h>
#include <StormNet/NetReflectionTypeDatabase.h>

#include <StormNet/NetReflection.h>
#include <StormNet/NetMessageSender.h>

#include "Foundation/Common.h"

static const int kMaxPlayers = 10;
static const int kMaxTeams = 2;
static const int kMaxRewindFrames = 10;

class GameStage;

struct GameInitSettings
{
  NET_REFL;
};

struct ClientLocalData
{
  NET_REFL;
  NetRangedNumber<int, 0, kMaxPlayers> m_PlayerIndex;
};

struct ClientInput
{
  NET_REFL;
};

struct ClientAuthData
{
  NET_REFL;
  int m_Frame;
  ClientInput m_Input;
};

using GameInputState = ClientInput[kMaxPlayers];

class SimEventHandler
{
public:
  virtual void HandleWinGame(int winning_team) {};
};

struct GamePlayer
{
  NET_REFL;

  std::string m_Name;
  NetRangedNumber<int, 0, kMaxTeams - 1> m_Team;
};


struct GameSimulation
{
  NET_REFL;

  int m_FrameCount;

  NetSparseList<GamePlayer, kMaxPlayers> m_Players;

public:
  void Init(GameStage & stage);
  bool Step(GameStage & stage, GameInputState & input, NullOptPtr<SimEventHandler> event_hander, bool authority);

  void AddPlayer(GameStage & stage, int player_index, const std::string & name, int team, uint32_t seed);
  void RemovePlayer(int player_index);

};
