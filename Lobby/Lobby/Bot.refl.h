#pragma once

#include <HurricaneDDS/DDSDataObject.h>
#include <HurricaneDDS/DDSThrottle.refl.h>

#include <StormRefl/StormReflJsonStd.h>

#include "SharedTypes.refl.h"
#include "GameData.refl.h"
#include "GameServerMessages.refl.h"
<<<<<<< HEAD
=======
#include "LobbyConfig.h"

#if defined(ENABLE_BOTS) && defined(ENABLE_CHANNELS)
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c

struct BotDatabaseObject
{
  DDS_DATABASE_OBJECT(Bot);

  RString m_UserName;
  STORM_REFL_ATTR(UniqueIndex) RString m_UserNameLower;

  RString m_Password;
  RString m_Channel;

  RString m_WelcomeInfoTab;
};

struct Bot
{
  DDS_DATA_OBJECT(DDSDataObjectPriority::kMedium);
  Bot(DDSNodeInterface node_interface, BotDatabaseObject & db_object);

  void STORM_REFL_FUNC AddEndpoint(DDSResponder & responder, DDSKey key, std::string user_name, std::string password);
  void STORM_REFL_FUNC RemoveEndpoint(DDSKey key);

  void STORM_REFL_FUNC GotChat(DDSKey user_id, DDSKey endpoint_id, std::string user_name, std::string message);
  void STORM_REFL_FUNC HandleChannelUpdate(std::string data);
  void STORM_REFL_FUNC HandleServerListUpdate(std::string data);

  void STORM_REFL_FUNC SendChatToChannel(std::string message);
  void STORM_REFL_FUNC SendChatToUser(DDSKey user_id, std::string message);
  void STORM_REFL_FUNC SendChatToEndpoint(DDSKey endpoint_id, std::string message);

  void STORM_REFL_FUNC SetChannelMotd(std::string motd);

  void STORM_REFL_FUNC SetWelcomeInfoTab(DDSResponder & responder, std::string tab);
  void STORM_REFL_FUNC UpdateWelcomeInfo(std::string info);
  void STORM_REFL_FUNC HandleWelcomeInfoUpdateResponse(std::string data);

  void STORM_REFL_FUNC ProcessGameResult(GameServerGameResult result, DDSKey game_id);

  void STORM_REFL_FUNC GetInfo(DDSResponder & responder);

public:

  void BeginLoad();

public:
  bool m_HasChannelInfo;

  DDSKey m_ChannelKey;
  DDSKey m_EndpointKey;

  DDSKey m_ChannelSubscriptionId;
  DDSKey m_ServerListSubscriptionId;

public:

private:
  STORM_REFL_IGNORE DDSNodeInterface m_Interface;
  STORM_REFL_IGNORE BotDatabaseObject & m_Data;
};
<<<<<<< HEAD
=======

#endif
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
