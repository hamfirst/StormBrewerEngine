#pragma once


#include <HurricaneDDS/DDSDataObjectTypeList.h>
#include <HurricaneDDS/DDSSharedObjectList.h>

#include "UserConnection.refl.meta.h"
#include "GameServerConnection.refl.meta.h"
#include "User.refl.meta.h"
#include "Channel.refl.meta.h"
#include "BuiltInChannel.refl.meta.h"
#include "BotConnection.refl.meta.h"
#include "Squad.refl.meta.h"
#include "Bot.refl.meta.h"

#include "BanList.refl.meta.h"
#include "ServerList.refl.meta.h"
#include "WelcomeInfo.refl.meta.h"
#include "Rewards.refl.meta.h"
#include "ServerManager.refl.meta.h"
#include "LobbyConfig.h"


using DataObjectList = DDSDataObjectTypeList<
#ifdef ENABLE_BOTS
  BotConnection, void,
  Bot, BotDatabaseObject,
#endif
#ifdef ENABLE_CHANNELS
  Channel, void,
  BuiltInChannel, BuiltInChannelDatabaseObject,
#endif
#ifdef ENABLE_SQUADS
  Squad, SquadDatabaseObject,
#endif
  UserConnection, void,
  User, UserDatabaseObject,
  GameServerConnection, void>;

using SharedObjectList = DDSSharedObjectTypeList<
#ifdef ENABLE_BAN_LIST
    BanList,
#endif
#ifdef ENABLE_SERVER_LIST
    ServerList,
#endif
#ifdef ENABLE_WELCOME_INFO
    WelcomeInfo,
#endif
#ifdef ENABLE_REWARDS
    Rewards,
#endif
    ServerManager
    >;
