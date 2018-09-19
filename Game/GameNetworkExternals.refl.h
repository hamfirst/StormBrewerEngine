#pragma once

#include <StormNet/NetReflectionStruct.h>
#include <StormNet/NetReflectionTypeDatabase.h>

#include <StormNet/NetReflection.h>

#include "Game/GameNetworkSettings.h"
#include "Game/GameServerTypes.h"

struct GameNetworkExternalEvent
{
  NET_DECLARE_BASE_TYPE;
  NET_REFL;
};

struct PlayerJoinedEvent : public GameNetworkExternalEvent
{
  NET_REFL;
  std::string m_UserName;
  uint32_t m_RandomSeed;
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
