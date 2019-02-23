#pragma once

#include <HurricaneDDS/DDSDataObject.h>

#include "SharedTypes.refl.h"
#include "LobbyConfig.h"

#ifdef ENABLE_CHANNELS

struct BuiltInChannelInfo
{
  STORM_DATA_DEFAULT_CONSTRUCTION(BuiltInChannelInfo);

  RString m_ChannelName;
  RString m_Motd;
  RInt m_RequiredAdminLevel = 0;
};

struct BuiltInChannelDatabaseObject
{
  DDS_DATABASE_OBJECT(BuiltInChannel);

  STORM_REFL_ATTR(UniqueIndex) RString m_ChannelNameLower;

  BuiltInChannelInfo m_ChannelInfo;
};

struct BuiltInChannel
{
  DDS_DATA_OBJECT(DDSDataObjectPriority::kMedium);
  BuiltInChannel(DDSNodeInterface node_interface, BuiltInChannelDatabaseObject & db_object);

public:

  void STORM_REFL_FUNC GetChannelName(DDSResponder & responder);
  void STORM_REFL_FUNC UpdateMotd(std::string motd);

private:
  STORM_REFL_IGNORE DDSNodeInterface m_Interface;
  STORM_REFL_IGNORE BuiltInChannelDatabaseObject & m_Data;
};

#endif