#pragma once

#include <StormNet/NetReflectionStruct.h>
#include <StormNet/NetReflectionTypeDatabase.h>

#include <StormNet/NetReflection.h>

struct GlobalNetworkEvent
{
  NET_DECLARE_BASE_TYPE;
  NET_REFL;
};

struct PlaceholderGlobalEvent : public GlobalNetworkEvent
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


#if (NET_MODE == NET_MODE_TURN_BASED_DETERMINISTIC)

struct EndTurnEvent : public ClientNetworkEvent
{
  NET_REFL;
};

#endif