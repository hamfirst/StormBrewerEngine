#pragma once

#include <StormNet/NetReflectionStruct.h>
#include <StormNet/NetReflectionTypeDatabase.h>

#include <StormNet/NetReflection.h>

#include "Game/GameNetworkSettings.h"
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

struct GameJoinInfo
{
  NET_REFL;
  std::string m_UserName;
  GameInitSettings m_Settings;
};

struct CreatePrivateGameMessage : public ToServerMessage
{
  NET_REFL;
  GameJoinInfo m_JoinInfo;
};

struct JoinGameMessage : public ToServerMessage
{
  NET_REFL;
  uint32_t m_PrivateRoomId;
  GameJoinInfo m_JoinInfo;
};

struct ReadyMessage : public ToServerMessage
{
  NET_REFL;
  bool m_Ready;
};

struct KickPlayerMessage : public ToServerMessage
{
  NET_REFL;
  uint8_t m_PlayerIndex;
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
