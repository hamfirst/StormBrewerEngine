#pragma once

#include <StormNet/NetReflectionStruct.h>
#include <StormNet/NetReflectionTypeDatabase.h>

#include <StormNet/NetReflection.h>

#include "Game/GameNetworkSettings.h"
#include "Game/GameServerTypes.h"

struct GlobalNetworkEvent
{
  NET_DECLARE_BASE_TYPE;
  NET_REFL;
};

struct PlaySoundGlobalEvent : public GlobalNetworkEvent
{
  NET_REFL;
  uint32_t m_AssetHash;
  int16_t m_PositionX;
  int16_t m_PositionY;
};

struct PlayVfxGlobalEvent : public GlobalNetworkEvent
{
  NET_REFL;
  uint32_t m_AssetHash;
  int16_t m_PositionX;
  int16_t m_PositionY;
};

struct ServerAuthNetworkEvent
{
  NET_DECLARE_BASE_TYPE;
  NET_REFL;
};

struct PlaceholderServerAuthEvent : public ServerAuthNetworkEvent
{
  NET_REFL;
};

struct TargetNetworkEvent
{
  NET_DECLARE_BASE_TYPE;
  NET_REFL;
  NetRangedNumber<int, 0, 255> m_Target;
};

struct PlaceholderTargetEvent : public TargetNetworkEvent
{
  NET_REFL;
};

struct ClientNetworkEvent
{
  NET_DECLARE_BASE_TYPE;
  NET_REFL;
};

struct PlaceholderClientEvent : public ClientNetworkEvent
{
  NET_REFL;
};

struct JumpEvent : public ClientNetworkEvent
{
  NET_REFL;
};

#if (NET_MODE == NET_MODE_TURN_BASED_DETERMINISTIC)

struct EndTurnEvent : public ClientNetworkEvent
{
  NET_REFL;
};

#endif
