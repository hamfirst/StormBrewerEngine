#pragma once

#include <StormRefl/StormRefl.h>
#include <StormData/StormDataTypes.h>

#include <HurricaneDDS/DDSDataObject.h>

#include "ProjectSettings/ProjectNetworkSettings.h"
#include "ProjectSettings/ProjectZones.h"

#include "LobbyConfig.h"

#include "Game/GameNetworkData.refl.h"

enum STORM_REFL_ENUM class ChannelJoinResult
{
  kSuccess,
  kLocked,
  kAlreadyIn,
};

struct UserGameInfo
{
  STORM_DATA_DEFAULT_CONSTRUCTION(UserGameInfo);

  RKey m_GameId;
};

struct UserZoneInfo
{
  STORM_REFL;
  int m_Latencies[kNumProjectZones] = {};
};

struct UserInfo
{
  STORM_DATA_DEFAULT_CONSTRUCTION(UserInfo);

  RString m_Name;
  RString m_Platform;
  DDSKey m_PlatformId;

#ifdef ENABLE_SQUADS
  RString m_Squad;
  RString m_SquadTag;
#endif

  RString m_Icon;

#ifdef ENABLE_CHANNELS
  RInt m_VisibleFlags;
#endif

  RInt m_AdminLevel;
  UserGameInfo m_Game;
};

struct UserApplication
{
  STORM_DATA_DEFAULT_CONSTRUCTION(UserApplication);

  RString m_SquadName;
  RString m_SquadTag;
  RKey m_SquadId;
};

struct ChannelMember
{
  STORM_DATA_DEFAULT_CONSTRUCTION(ChannelMember);

  RString m_Name;

#ifdef ENABLE_SQUADS
  RString m_SquadTag;
  RInt m_VisibleFlags;
#endif

  DDSKey m_UserKey;
  DDSKey m_PlatformId;
  RString m_Icon;
  RInt m_AdminLevel;
  RInt m_MembershipFlags;
  UserGameInfo m_Game;
};

struct ChannelBot
{
  STORM_DATA_DEFAULT_CONSTRUCTION(ChannelBot);

  RString m_Name;
  DDSKey m_BotKey;
};

struct ChannelInfo
{
  STORM_DATA_DEFAULT_CONSTRUCTION(ChannelInfo);

  RString m_Name;
  RString m_Motd;

  RKey m_ChannelKey;

  RBool m_Locked;
  RSparseList<ChannelMember> m_Users;
  RMergeList<ChannelBot> m_Bots;
};

struct SquadMember
{
  STORM_DATA_DEFAULT_CONSTRUCTION(SquadMember);

  RKey m_UserKey;

  RString m_Name;
  RInt m_Joined;
  RInt m_MembershipFlags;
};

struct SquadApplication
{
  STORM_DATA_DEFAULT_CONSTRUCTION(SquadApplication);

  RString m_UserName;
  RKey m_UserKey;
};

struct SquadInfo
{
  STORM_DATA_DEFAULT_CONSTRUCTION(SquadInfo);

  RString m_Name;
  RString m_Tag;

  RString m_Motd;

  RKey m_SquadKey;

  RBool m_Locked;
  RSparseList<SquadMember> m_Users;
  RSparseList<SquadApplication> m_Applicants;
  RSparseList<SquadApplication> m_Requests;
};

struct GameMember
{
  STORM_DATA_DEFAULT_CONSTRUCTION(GameMember);

  RString m_Name;
  RInt m_Team;

#ifdef ENABLE_SQUADS
  RString m_SquadTag;
#endif

#if defined(NET_USE_READY) || defined(NET_USE_READY_PRIVATE_GAME)
  RBool m_Ready;
#endif

  RKey m_UserKey;
  RKey m_PlatformId;
  RString m_Platform;

  RString m_Icon;
  RString m_Title;
};


enum STORM_REFL_ENUM class LobbyGameState
{
  kInitializing,
  kWaiting,
  kCountdown,
  kAssigningServer,
  kStarted,
  kPostGame,
};

enum STORM_REFL_ENUM class LobbyGameType
{
  kCasual,
  kCompetitive,
  kPrivate,
};

struct GameInfo
{
  STORM_DATA_DEFAULT_CONSTRUCTION(GameInfo);

  REnum<LobbyGameState> m_State;
  REnum<LobbyGameType> m_Type;

  RInt m_Countdown;
  RKey m_GameLeader;
  RUInt m_JoinCode;
  RString m_Password;
  ROpaque<GameInitSettings> m_Settings;
  RSparseList<GameMember> m_Users;
};
