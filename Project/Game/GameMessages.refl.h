#pragma once

#include "StormNet/NetReflectionStruct.h"
#include "StormNet/NetReflectionTypeDatabase.h"

#include "StormNet/NetReflection.h"

#include "ProjectSettings/ProjectNetworkSettings.h"

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

struct GotTextChatMessage : public FromServerMessage
{
  NET_REFL;
  std::string m_UserName;
  std::string m_Message;
  NetRangedNumber<int, -1, kMaxTeams - 1> m_Team;
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

struct JoinServerMessage : public ToServerMessage
{
  NET_REFL;
  uint64_t m_UserId;
  uint64_t m_GameId;
  uint64_t m_JoinToken;
};

struct FinishLoadingMessage : public ToServerMessage
{
  NET_REFL;
  uint64_t m_LoadToken;
};

struct SendTextChatMessage : public ToServerMessage
{
  NET_REFL;
  std::string m_Message;
  bool m_TeamOnly;
};

#ifdef NET_USE_LOADOUT
struct ChangeLoadoutMessage : public ToServerMessage
{
  NET_REFL;
  uint8_t m_PlayerIndex;
  GamePlayerLoadout m_Loadout;
};
#endif