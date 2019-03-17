#pragma once

#include <StormRefl/StormRefl.h>
#include <StormData/StormDataTypes.h>

#include <HurricaneDDS/DDSDataObject.h>

<<<<<<< HEAD
=======
#include "LobbyConfig.h"

>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
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
  RKey m_GameServerId;
};

struct UserInfo
{
  STORM_DATA_DEFAULT_CONSTRUCTION(UserInfo);

  RString m_Name;
<<<<<<< HEAD
  RString m_Squad;
  RString m_SquadTag;
  DDSKey m_PlatformId;
  RString m_Icon;
  RInt m_AdminLevel;
  RInt m_VisibleFlags;
  RBool m_Veteran;
=======
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
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
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
  RString m_SquadTag;
  DDSKey m_UserKey;
  DDSKey m_PlatformId;
  RString m_Icon;
  RInt m_AdminLevel;
  RInt m_VisibleFlags;
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

