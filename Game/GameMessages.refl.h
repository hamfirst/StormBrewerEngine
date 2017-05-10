#pragma once

#include <StormNet/NetReflectionStruct.h>
#include <StormNet/NetReflectionTypeDatabase.h>

#include <StormNet/NetReflection.h>

#include "Game/GameSimulation.refl.h"

struct FromServerMessage
{
  NET_DECLARE_BASE_TYPE;
  NET_REFL;
};

struct PongMessage : public FromServerMessage
{
  NET_REFL;
};

struct ToServerMessage
{
  NET_DECLARE_BASE_TYPE;
  NET_REFL;
};

struct PingMessage : public ToServerMessage
{
  NET_REFL;
};

struct JoinGameMessage : public ToServerMessage
{
  NET_REFL;
  uint64_t m_GameId;
  std::string m_Name;
  GameInitSettings m_Settings;
};

struct SimEventBase
{
  NET_REFL;
  NET_DECLARE_BASE_TYPE;
};

struct PlaceholderEvent : public SimEventBase
{
  NET_REFL;
};

