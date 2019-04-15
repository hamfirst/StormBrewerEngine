#pragma once

#include "StormNet/NetReflectionStruct.h"
#include "StormNet/NetReflectionTypeDatabase.h"

#include "StormNet/NetReflection.h"

#include "Game/GameNetworkData.refl.h"
#include "Game/GameNetworkExternals.refl.h"
#include "Game/GameNetworkEvents.refl.h"

#include "ProjectSettings/ProjectNetworkSettings.h"

#include "Runtime/ServerObject/ServerObjectManager.h"
#include "Runtime/ServerObject/ServerObjectSerialize.h"

struct GameFullState
{
  NET_REFL;
  STORM_REFL_NODEFAULT;

  ServerObjectManager m_ServerObjectManager;
  GameInstanceData m_InstanceData;
};

struct GameStateStagingPlayer
{
  NET_REFL;
  std::string m_UserName;
  bool m_GameLeader = false;

#if defined(NET_USE_READY) || defined(NET_USE_READY_PRIVATE_GAME)
  bool m_Ready = false;
#endif

  GamePlayerLoadout m_Loadout;
  NetRangedNumber<int, -1, kMaxTeams - 1> m_Team = 0;
};

struct GameStateLoadingPlayer
{
  NET_REFL;
  std::string m_UserName;
  bool m_Loaded = false;
  GamePlayerLoadout m_Loadout;
  NetRangedNumber<int, -1, kMaxTeams - 1> m_Team = 0;
};

struct GameStateLoading
{
  NET_REFL;
  NetSparseList<GameStateLoadingPlayer, kMaxPlayers> m_Players;
};

#if NET_MODE == NET_MODE_GGPO

struct GameHistoryInput
{
  NET_REFL;
  NetRangedNumber<int, 0, kMaxPlayers> m_PlayerIndex;
  int m_Frame = 0;
  ClientInput m_Input;
};

struct GameHistoryEvent
{
  NET_REFL;
  NetRangedNumber<int, 0, kMaxPlayers> m_PlayerIndex;
  int m_Frame = 0;
  NetPolymorphic<ClientNetworkEvent> m_Event;
};

struct GameHistoryClientEvent
{
  NET_REFL;
  int m_Frame = 0;
  NetPolymorphic<ClientNetworkEvent> m_Event;
};


struct GameHistoryExternal
{
  NET_REFL;
  int m_Frame = 0;
  NetPolymorphic<GameNetworkExternalEvent> m_Event;
};

struct GameHistoryAuthEvent
{
  NET_REFL;
  int m_Frame = 0;
  NetPolymorphic<ServerAuthNetworkEvent> m_Event;
};

struct GameHistoryClientLocal
{
  NET_REFL;
  int m_Frame = 0;
  ClientLocalData m_Data;
};

struct GameGGPOServerGameState
{
  NET_REFL;
  STORM_REFL_NODEFAULT;

  int m_AckFrame = 0;
  int m_ServerFrame = 0;
  int m_EventStartFrame = 0;

  std::shared_ptr<GameFullState> m_State;
  NetOptional<GameInstanceLowFrequencyData> m_LowFrequencyData;

  NetOptional<NetArrayList<GameHistoryInput, 1023>> m_Inputs;
  NetOptional<NetArrayList<GameHistoryEvent, 1023>> m_Events;
  NetOptional<NetArrayList<GameHistoryExternal, 1023>> m_Externals;
  NetOptional<NetArrayList<GameHistoryClientLocal, 1023>> m_LocalData;
  NetOptional<NetArrayList<GameHistoryAuthEvent, 1023>> m_ServerAuthEvents;
};

struct GameGGPOClientUpdate
{
  NET_REFL;

  int m_AckFrame = 0;
  int m_ClientFrame = 0;
  NetOptional<NetArrayList<ClientAuthData, 127>> m_Inputs;
  NetOptional<NetArrayList<GameHistoryClientEvent, 127>> m_Events;
};

#endif

