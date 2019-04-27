#pragma once

#include <StormNet/NetReflectionStruct.h>
#include <StormNet/NetReflectionTypeDatabase.h>

#include <StormNet/NetReflection.h>

#include "ProjectSettings/ProjectNetworkSettings.h"

#include "Game/GameServerTypes.h"
#include "Game/GameNetworkData.refl.h"

struct GameNetworkExternalEvent
{
  NET_DECLARE_BASE_TYPE;
  NET_REFL;
};

struct PlayerJoinedEvent : public GameNetworkExternalEvent
{
  NET_REFL;
  std::string m_UserName;
  uint8_t m_Team;
  uint8_t m_PlayerIndex;
};

struct PlayerLeaveEvent : public GameNetworkExternalEvent
{
  NET_REFL;
  uint8_t m_PlayerIndex;
};

#ifdef NET_ALLOW_OBSERVERS
struct ObserverJoinedEvent : public GameNetworkExternalEvent
{
  NET_REFL;
  std::string m_UserName;
  uint8_t m_PlayerIndex;
};

struct ObserverLeaveEvent : public GameNetworkExternalEvent
{
  NET_REFL;
  uint8_t m_PlayerIndex;
};
#endif

struct ChangePlayerNameEvent : public GameNetworkExternalEvent
{
  NET_REFL;
  uint8_t m_PlayerIndex;
  std::string m_Name;
};

#ifdef NET_ALLOW_OBSERVERS

struct ChangeObserverNameEvent : public GameNetworkExternalEvent
{
  NET_REFL;
  uint8_t m_ObserverIndex;
  std::string m_Name;
};

struct ChangeObserverToPlayer : public GameNetworkExternalEvent
{
  NET_REFL;
  uint8_t m_ObserverIndex;
  uint8_t m_PlayerIndex;
  NetRangedNumber<int, 0, kMaxTeams - 1> m_Team;
  uint32_t m_RandomSeed;

#ifdef NET_USE_LOADOUT
  GamePlayerLoadout m_Loadout;
#endif
};

struct ChangePlayerToObserver : public GameNetworkExternalEvent
{
  NET_REFL;
  uint8_t m_ObserverIndex;
  uint8_t m_PlayerIndex;
};

#endif

struct ChangePlayerTeam : public GameNetworkExternalEvent
{
  NET_REFL;
  uint8_t m_PlayerIndex;
  NetRangedNumber<int, 0, kMaxTeams - 1> m_Team;
};

#ifdef NET_USE_LOADOUT
struct ChangeLoadoutEvent : public GameNetworkExternalEvent
{
  NET_REFL;
  uint8_t m_PlayerIndex;
  GamePlayerLoadout m_Loadout;
};
#endif