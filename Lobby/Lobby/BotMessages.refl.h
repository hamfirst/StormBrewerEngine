#pragma once

#include <string>
#include <vector>

#include <StormRefl/StormRefl.h>

#include <HurricaneDDS/DDSKey.h>

#include "GameData.refl.h"
#include "GameServerMessages.refl.h"


#if defined(ENABLE_BOTS) && defined(ENABLE_CHANNELS)

struct BotMessageBase
{
  STORM_REFL;
  std::string c;
};

struct BotErrorMessage
{
  STORM_REFL;
  std::string c;
  std::string err;
};

struct BotIdentify
{
  STORM_REFL;
  std::string c;
  std::string user_name;
  std::string password;
  DDSKey relocation_key = 0;
};

struct BotMessageUpdate
{
  STORM_REFL;
  std::string c;
  std::string data;
};

struct BotMessageChannelChat
{
  STORM_REFL;
  std::string c;
  std::string user_name;
  std::string msg;
  DDSKey user_id;
  DDSKey endpoint_id;
};

struct BotMessageRelocate
{
  STORM_REFL;
  std::string c;
  std::string new_host;
  int new_port;
  uint64_t relocation_token;
};

struct BotMessageSendChatToChannel
{
  STORM_REFL;
  std::string c;
  std::string msg;
};

struct BotMessageChannelMotd
{
  STORM_REFL;
  std::string c;
  std::string motd;
};

struct BotMessageSendChatToUser
{
  STORM_REFL;
  std::string c;
  std::string msg;
  DDSKey user_id = 0;
};

struct BotMessageGameResult
{
  STORM_REFL;
  std::string c;
  DDSKey game_id;
  GameServerGameResult game_info;
};

struct BotMessageCreateGame
{
  STORM_REFL;
  std::string c;
  DDSKey server_id;
  DDSKey game_id;
  GameInstanceData game_settings;
  std::vector<std::tuple<DDSKey, DDSKey, int>> players;
};

#endif