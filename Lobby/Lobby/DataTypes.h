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


using DataObjectList = DDSDataObjectTypeList<
  UserConnection, void,
  GameServerConnection, void,
  BotConnection, void,
  Channel, void,
  User, UserDatabaseObject,
  BuiltInChannel, BuiltInChannelDatabaseObject,
  Squad, SquadDatabaseObject,
  Bot, BotDatabaseObject>;

using SharedObjectList = DDSSharedObjectTypeList<BanList, ServerList, WelcomeInfo, Rewards>;
