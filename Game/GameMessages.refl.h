#pragma once

#include <StormNet/NetReflectionStruct.h>
#include <StormNet/NetReflectionTypeDatabase.h>

#include <StormNet/NetReflection.h>

#include "Game/GameNetworkData.refl.h"

struct FromServerMessage
{
  NET_DECLARE_BASE_TYPE;
  NET_REFL;
};

struct LoadLevelMessage : public FromServerMessage
{
  NET_REFL;
  GameInitSettings m_Settings;
  uint64_t m_LoadToken;
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
  std::string m_UserName;
  GameInitSettings m_Settings;
};

struct FinishLoadingMessage : public ToServerMessage
{
  NET_REFL;
  uint64_t m_LoadToken;
};

