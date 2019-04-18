#pragma once

#include <string>
#include <vector>

#include <StormRefl/StormRefl.h>

#include <HurricaneDDS/DDSKey.h>

#include "Lobby/GameData.refl.h"
#include "Lobby/LobbyConfig.h"

#include "Game/GameNetworkData.refl.h"


struct GeolocationResponse
{
  STORM_REFL;
  std::string as;
  std::string city;
  std::string country;
  std::string countryCode;
  std::string isp;
  float lat = 0;
  float lon = 0;
  std::string org;
  std::string query;
  std::string region;
  std::string regionName;
  std::string status;
  std::string timezone;
  std::string zip;
};

struct UserMessageBase
{
  STORM_REFL;

  std::string c;
};

struct UserVersionRequest
{
  STORM_REFL;

  std::string c;
#ifdef ENABLE_PROOF_OF_WORK
  std::string sha;
  std::string prefix;
#endif
};

struct UserMessageConnectionError
{
  STORM_REFL;
  std::string c;
  std::string msg;
};

struct UserMessageRuntimeError
{
  STORM_REFL;
  std::string c;
  std::string msg;
};

struct UserMessageVersionResponse
{
  STORM_REFL;

  std::string c;
  int ver = 0;
#ifdef ENABLE_PROOF_OF_WORK
  uint32_t sha = 0;
#endif
};

struct UserMessageIdentifyRequest
{
  STORM_REFL;
  std::string c;
};

struct UserMessageIdentifyResponse
{
  STORM_REFL;
  std::string c;
  std::string user_name;
  std::string token;
};

struct UserMessageCreateName
{
  STORM_REFL;
  std::string c;
  std::string uname;
};

struct UserLocalInfoUpdate
{
  STORM_REFL;
  std::string c;
  std::string data;
};

struct UserGamePreviewUpdate
{
  STORM_REFL;
  std::string c;
  std::string data;
  int request_id;
};

struct UserGamePreviewCancel
{
  STORM_REFL;
  std::string c;
  int request_id;
};


struct UserGameInfoUpdate
{
  STORM_REFL;
  std::string c;
  std::string data;
  int game_id;
};

struct UserChannelInfoUpdate
{
  STORM_REFL;
  std::string c;
  std::string data;
  DDSKey channel_id;
};

struct UserMessageRelocate
{
  STORM_REFL;
  std::string c;
  std::string new_host;
  int new_port;
  uint64_t relocation_token;
};

struct UserChatMessageIncoming
{
  STORM_REFL;
  std::string c;
  std::string msg;
  DDSKey channel_id = 0;
};

struct UserChatMessageOutgoing
{
  STORM_REFL;
  std::string c;
  std::string user;
  std::string msg;
  std::string b;
  int t = 0;
  DDSKey channel_id = 0;
};

struct UserChatMessageGame
{
  STORM_REFL;
  std::string c;
  std::string user;
  std::string title;
  std::string msg;
};

struct UserServerMessageGame
{
  STORM_REFL;
  std::string c;
  std::string msg;
};


struct UserGameCreate
{
  STORM_REFL;
  std::string c;
  DDSKey server_id;
  GameInitSettings create_data;
  std::string password;
};

struct UserJoinGame
{
  STORM_REFL;
  std::string c;
  DDSKey server_id;
  DDSKey game_id;
  std::string password;
  bool observer;
};

struct UserDestroyGame
{
  STORM_REFL;
  std::string c;
  DDSKey game_id;
};

struct UserStartGame
{
  STORM_REFL;
  std::string c;
  std::string ip_addr;
  std::string port;
  std::string token;
};

struct UserSwitchTeam
{
  STORM_REFL;
  std::string c;
  DDSKey target_user = 0;
  int team;
};

struct UserCreateSquad
{
  STORM_REFL;
  std::string c;
  std::string name;
  std::string tag;
};

struct UserSquadAction
{
  STORM_REFL;
  std::string c;
  DDSKey squad;
};

struct UserSquadMemberAction
{
  STORM_REFL;
  std::string c;
  DDSKey squad;
  DDSKey user;
};

struct UserSquadLookupAction
{
  STORM_REFL;
  std::string c;
  std::string squad;
};

struct UserSquadMemberLookupAction
{
  STORM_REFL;
  std::string c;
  DDSKey squad;
  DDSKey user_platform_id;
};

struct UserSquadMemberPermissions
{
  STORM_REFL;
  std::string c;
  DDSKey squad;
  DDSKey member;
  int rank;
};

struct UserSquadMotd
{
  STORM_REFL;
  std::string c;
  DDSKey squad;
  std::string motd;
};

struct UserSquadLock
{
  STORM_REFL;
  std::string c;
  DDSKey squad;
  bool lock;
};

struct UserStatsData
{
  STORM_REFL;
  std::string c;
  std::string name;

  int last_game_played;
  GameStatsData stats;

#ifdef ENABLE_REWARDS
  int rank;
  int xp;
#endif
};

struct UserEditInfo
{
  STORM_REFL;
  std::string c;
  std::string data;
};

struct UserEditChannelInfo
{
  STORM_REFL;
  std::string c;
  std::string data;
  DDSKey channel_id;
};

struct UserFetchStats
{
  STORM_REFL;
  std::string c;
  DDSKey user;
};

struct UserSetProfileVal
{
  STORM_REFL;
  std::string c;
  int val;
};

struct UserSetProfileSquad
{
  STORM_REFL;
  std::string c;
  DDSKey val;
};

struct UserPreviewGame
{
  STORM_REFL;
  std::string c;
  DDSKey server_id;
  DDSKey game_id;
  int request_id;
};

struct UserAutoJoinModify
{
  STORM_REFL;
  std::string c;
  std::string channel;
};

struct UserPersistentModify
{
  STORM_REFL;
  std::string c;
  std::string change;
};


struct UserGotXP
{
  STORM_REFL;
  std::string c;
  int xp;
  int level;
  bool last;

#ifdef ENABLE_REWARDS
  UserXPGain xp_info;
#endif
};
