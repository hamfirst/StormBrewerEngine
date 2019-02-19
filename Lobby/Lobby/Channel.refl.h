#pragma once

#include <HurricaneDDS/DDSDataObject.h>
#include <HurricaneDDS/DDSConnectionId.h>

#include "SharedTypes.refl.h"
#include "Squad.refl.h"
#include "BuiltInChannel.refl.h"

enum STORM_REFL_ENUM class ChannelState
{
  kCheckingForBuiltIn,
  kCheckingForSquad,
  kWaitingForFirstMember,
  kTemporary,
  kBuiltIn,
  kSquad,
};

struct Channel
{
  DDS_TEMPORARY_OBJECT(true, DDSDataObjectPriority::kLow);

  Channel(DDSNodeInterface node_interface);

  void STORM_REFL_FUNC AddUser(DDSResponder & responder, DDSKey user_key, int admin_level, std::string channel_name);
  void STORM_REFL_FUNC RemoveUser(DDSKey user_key);
  void STORM_REFL_FUNC KickUser(DDSKey endpoint_id, DDSKey user_key, DDSKey src_user, int src_admin_level);

  void STORM_REFL_FUNC SendChatToChannel(DDSKey user_key, DDSKey endpoint_id, std::string message, std::string title);

  void STORM_REFL_FUNC AddBot(DDSKey bot_key, std::string user_name);
  void STORM_REFL_FUNC RemoveBot(DDSKey bot_key);
  void STORM_REFL_FUNC SendBotChatToChannel(DDSKey bot_key, std::string message);

  void STORM_REFL_FUNC HandleSquadDoesntExist();
  void STORM_REFL_FUNC HandleBuiltinDoesntExist();

  void STORM_REFL_FUNC HandleBuiltInChannelUpdate(std::string data);
  void STORM_REFL_FUNC HandleSquadUpdate(std::string data);

  void STORM_REFL_FUNC HandleMemberUpdate(DDSKey user_key, std::string data);

  void STORM_REFL_FUNC FetchChannelMotd(DDSResponder & responder);
  void STORM_REFL_FUNC UpdateChannelMotd(DDSResponder & responder, std::string motd);


  void STORM_REFL_FUNC GetInfo(DDSResponder & responder);

public:

  void BeginLoad();
  void AddPendingMember(DDSResponder & responder, DDSKey user_key);
  void RefusePendingMember(DDSResponder & responder, DDSKey user_key);

  void UpdateChannelMembershipFlags();

  static DDSKey GetChannelKeyFromName(const char * name);

public:

  REnum<ChannelState> m_State;

  ChannelInfo m_ChannelInfo;
  DDSKey m_ChannelSubscription;

  BuiltInChannelInfo m_BuiltInChannelInfo;
  SquadDatabaseInfo m_SquadInfo;

  std::map<DDSKey, DDSKey> m_MemberSubscriptionIds;

private:
  DDSNodeInterface m_Interface;
};
