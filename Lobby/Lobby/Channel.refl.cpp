
#include "Channel.refl.meta.h"
#include "Squad.refl.meta.h"
#include "BuiltInChannel.refl.meta.h"
#include "User.refl.meta.h"
#include "UserConnection.refl.meta.h"
#include "UserConnectionMessages.refl.meta.h"
#include "Bot.refl.meta.h"

#include <sb/vector.h>
#include <hash/Hash64.h>

#include <StormData/StormDataChangePacket.h>

#include <HurricaneDDS/DDSResponderCall.h>

<<<<<<< HEAD
=======

#ifdef ENABLE_CHANNELS

>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
static const time_t epoch = 1388534400; // Jan 1, 2014

Channel::Channel(DDSNodeInterface node_interface)
  : m_Interface(node_interface), m_State(ChannelState::kCheckingForBuiltIn)
{
}

void Channel::AddUser(DDSResponder & responder, DDSKey user_key, int admin_level, std::string channel_name)
{
   for(auto user : m_ChannelInfo.m_Users)
   {
     if (user.second.m_UserKey == user_key)
     {
       DDSResponderCall(responder, ChannelJoinResult::kAlreadyIn);
       return;
     }
   }

  if (m_State == ChannelState::kWaitingForFirstMember)
  {
    DDSLog::LogInfo("Finalizing channel %llu as temporary %s", m_Interface.GetLocalKey(), channel_name.c_str());

    m_ChannelInfo.m_Name = channel_name;
    m_ChannelInfo.m_ChannelKey = m_Interface.GetLocalKey();
    m_State = ChannelState::kTemporary;
  }

  if (m_State == ChannelState::kTemporary)
  {
    AddPendingMember(responder, user_key);
  }
  else if (m_State == ChannelState::kBuiltIn)
  {
    if (m_BuiltInChannelInfo.m_RequiredAdminLevel <= admin_level)
    {
      AddPendingMember(responder, user_key);
    }
    else
    {
      RefusePendingMember(responder, user_key);
    }
  }
  else if (m_State == ChannelState::kSquad)
  {
    if (m_SquadInfo.m_Locked == false || admin_level > 0)
    {
      AddPendingMember(responder, user_key);
    }
    else
    {
      for (auto squad_member : m_SquadInfo.m_Users)
      {
        if (squad_member.second.m_UserKey == user_key)
        {
          AddPendingMember(responder, user_key);
          return;
        }
      }

      RefusePendingMember(responder, user_key);
    }
  }
}

void Channel::RemoveUser(DDSKey user_key)
{
  auto itr = m_MemberSubscriptionIds.find(user_key);
  if (itr == m_MemberSubscriptionIds.end())
  {
    return;
  }

  m_Interface.DestroySubscription<User>(user_key, itr->second);
  m_MemberSubscriptionIds.erase(itr);

  for (auto user : m_ChannelInfo.m_Users)
  {
    if (user.second.m_UserKey == user_key)
    {
      m_ChannelInfo.m_Users.RemoveAt(user.first);
      return;
    }
  }
}

void Channel::KickUser(DDSKey endpoint_id, DDSKey user_key, DDSKey src_user, int src_admin_level)
{
  int target_user_squad_level = -1;
  int src_user_squad_level = 0;
  for (auto user : m_ChannelInfo.m_Users)
  {
    if (user.second.m_UserKey == user_key)
    {
      target_user_squad_level = user.second.m_MembershipFlags;
    }

    if (user.second.m_UserKey == src_user)
    {
      src_user_squad_level = user.second.m_MembershipFlags;
    }
  }

  if (target_user_squad_level == -1)
  {
    if (endpoint_id != 0)
    {
      m_Interface.Call(&UserConnection::SendNotification, endpoint_id, "User not found");
    }

    return;
  }

  if (target_user_squad_level >= src_user_squad_level && src_admin_level == 0)
  {
    if (endpoint_id != 0)
    {
      m_Interface.Call(&UserConnection::SendNotification, endpoint_id, "You do not have the ability to remove that user");
    }

    return;
  }

  m_Interface.Call(&User::SendNotification, user_key, std::string("You have been kicked out of channel ") + m_ChannelInfo.m_Name.ToString());
  m_Interface.Call(&User::LeaveChannel, user_key, m_Interface.GetLocalKey());

  m_Interface.Call(&UserConnection::SendNotification, endpoint_id, std::string("User removed from channel ") + m_ChannelInfo.m_Name.ToString());
}

void Channel::SendChatToChannel(DDSKey user_key, DDSKey endpoint_id, std::string message, std::string title)
{
  bool in_channel = false;
  std::string user_name;

  for (auto user : m_ChannelInfo.m_Users)
  {
    if (user.second.m_UserKey == user_key)
    {
      user_name = user.second.m_Name.ToString();
      in_channel = true;
      break;
    }
  }

  if (in_channel == false)
  {
    return;
  }

  UserChatMessageOutgoing chat_msg;
  chat_msg.c = "c";
  chat_msg.b = title;
  chat_msg.msg = message;
  chat_msg.user = user_name;
  chat_msg.t = (int)(time(nullptr) - epoch);
  chat_msg.channel_id = m_Interface.GetLocalKey();

  std::string chat_data = StormReflEncodeJson(chat_msg);
  for (auto user : m_ChannelInfo.m_Users)
  {
    m_Interface.Call(&User::SendToAllEndpoints, user.second.m_UserKey, chat_data);
  }

  for (auto bot : m_ChannelInfo.m_Bots)
  {
    m_Interface.Call(&Bot::GotChat, bot.second.m_BotKey, user_key, endpoint_id, user_name, message);
  }
}

void Channel::AddBot(DDSKey bot_key, std::string user_name)
{
  ChannelBot bot;
  bot.m_BotKey = bot_key;
  bot.m_Name = user_name;

  m_ChannelInfo.m_Bots.EmplaceBack(bot);
}

void Channel::RemoveBot(DDSKey bot_key)
{
  for (auto bot : m_ChannelInfo.m_Bots)
  {
    if (bot.second.m_BotKey == bot_key)
    {
      m_ChannelInfo.m_Bots.RemoveAt(bot.first);
      return;
    }
  }
}

void Channel::SendBotChatToChannel(DDSKey bot_key, std::string message)
{
  bool in_channel = false;
  std::string user_name;

  for (auto bot : m_ChannelInfo.m_Bots)
  {
    if (bot.second.m_BotKey == bot_key)
    {
      user_name = bot.second.m_Name.ToString();
      in_channel = true;
      break;
    }
  }

  if (in_channel == false)
  {
    return;
  }

  UserChatMessageOutgoing chat_msg;
  chat_msg.c = "c";
  chat_msg.msg = message;
  chat_msg.user = user_name;
  chat_msg.t = (int)(time(nullptr) - epoch);
  chat_msg.channel_id = m_Interface.GetLocalKey();

  std::string chat_data = StormReflEncodeJson(chat_msg);
  for (auto user : m_ChannelInfo.m_Users)
  {
    m_Interface.Call(&User::SendToAllEndpoints, user.second.m_UserKey, chat_data);
  }
}

void Channel::HandleSquadDoesntExist()
{
  if (m_State == ChannelState::kSquad)
  {
    m_State = ChannelState::kTemporary;
    m_ChannelInfo.m_Locked = false;
    m_ChannelInfo.m_Motd = "";
  }
  else
  {
    m_State = ChannelState::kWaitingForFirstMember;
    m_Interface.FinalizeObjectLoad();
  }

}

void Channel::HandleBuiltinDoesntExist()
{
  DDSLog::LogInfo("Checking channel %llu for squad", m_Interface.GetLocalKey());

  m_Interface.DestroyDatabaseSubscription<BuiltInChannelDatabaseObject>(m_Interface.GetLocalKey(), m_ChannelSubscription);

  m_State = ChannelState::kCheckingForSquad;

  m_ChannelSubscription = m_Interface.CreateDataSubscription(DDSSubscriptionTarget<SquadDatabaseObject>{},
    m_Interface.GetLocalKey(), ".m_DatabaseInfo", &Channel::HandleSquadUpdate, true, &Channel::HandleSquadDoesntExist, true);
}

void Channel::HandleBuiltInChannelUpdate(std::string data)
{
  ReflectionChangeNotification change_notification;
  StormDataParseChangePacket(change_notification, data.data());

  StormDataApplyChangePacket(m_BuiltInChannelInfo, change_notification);

  if (m_State == ChannelState::kCheckingForBuiltIn)
  {
    DDSLog::LogInfo("Finalizing channel %llu as builtin %s", m_Interface.GetLocalKey(), m_BuiltInChannelInfo.m_ChannelName.data());

    m_State = ChannelState::kBuiltIn;
    m_ChannelInfo.m_Name = m_BuiltInChannelInfo.m_ChannelName;
    m_ChannelInfo.m_Motd = m_BuiltInChannelInfo.m_Motd;
    m_ChannelInfo.m_ChannelKey = m_Interface.GetLocalKey();
    m_ChannelInfo.m_Locked = m_BuiltInChannelInfo.m_RequiredAdminLevel > 0;

    m_Interface.FinalizeObjectLoad();
  }
  else
  {
    m_ChannelInfo.m_Motd = m_BuiltInChannelInfo.m_Motd;
  }
}

void Channel::HandleSquadUpdate(std::string data)
{
  ReflectionChangeNotification change_notification;
  StormDataParseChangePacket(change_notification, data.data());

  StormDataApplyChangePacket(m_SquadInfo, change_notification);

  if (m_State == ChannelState::kCheckingForSquad)
  {
    DDSLog::LogInfo("Finalizing channel %llu as squad %s", m_Interface.GetLocalKey(), m_SquadInfo.m_Name.c_str());

    m_State = ChannelState::kSquad;

    m_ChannelInfo.m_Name = m_SquadInfo.m_Tag;
    m_ChannelInfo.m_Motd = m_SquadInfo.m_Motd;
    m_ChannelInfo.m_Locked = m_SquadInfo.m_Locked;
    m_ChannelInfo.m_ChannelKey = m_Interface.GetLocalKey();

    m_Interface.FinalizeObjectLoad();
  }
  else if (m_State == ChannelState::kTemporary)
  {
    m_State = ChannelState::kSquad;
    m_ChannelInfo.m_Name = m_SquadInfo.m_Tag;
    m_ChannelInfo.m_Motd = m_SquadInfo.m_Motd;
    m_ChannelInfo.m_Locked = m_SquadInfo.m_Locked;

    UpdateChannelMembershipFlags();
  }
  else if(m_State == ChannelState::kSquad)
  {
    if (change_notification.m_Path == ".m_Motd")
    {
      m_ChannelInfo.m_Motd = m_SquadInfo.m_Motd;
    }

    if (change_notification.m_Path == ".m_Locked")
    {
      m_ChannelInfo.m_Locked = m_SquadInfo.m_Locked;
    }

    if (StormDataMatchPathWildcard(change_notification.m_Path.data(), ".m_Users[*].m_MembershipFlags"))
    {
      UpdateChannelMembershipFlags();
    }
  }
}

void Channel::HandleMemberUpdate(DDSKey user_key, std::string data)
{
  auto itr = m_ChannelInfo.m_Users.begin();
  while (itr != m_ChannelInfo.m_Users.end())
  {
    if (itr->second.m_UserKey == user_key)
    {
      break;
    }
    ++itr;
  }

  if (itr == m_ChannelInfo.m_Users.end())
  {
    auto sub_itr = m_MemberSubscriptionIds.find(user_key);
    if (sub_itr == m_MemberSubscriptionIds.end())
    {
      return;
    }

    UserInfo user_info;
    StormDataApplyChangePacket(user_info, data.data());

    ChannelMember member;
    member.m_Name = user_info.m_Name;
    member.m_SquadTag = user_info.m_SquadTag;
    member.m_UserKey = user_key;
    member.m_PlatformId = user_info.m_PlatformId;
    member.m_Icon = user_info.m_Icon;
    member.m_AdminLevel = user_info.m_AdminLevel;
    member.m_VisibleFlags = user_info.m_VisibleFlags;
    member.m_MembershipFlags = 0;

    if (m_State == ChannelState::kSquad)
    {
      for (auto squad_member : m_SquadInfo.m_Users)
      {
        if (squad_member.second.m_UserKey == user_key)
        {
          member.m_MembershipFlags = squad_member.second.m_MembershipFlags;
        }
      }
    }

    m_ChannelInfo.m_Users.PushBack(member);
    return;
  }

  StormDataApplyChangePacket(itr->second, data.data());
}

void Channel::FetchChannelMotd(DDSResponder & responder)
{
  DDSResponderCall(responder, m_ChannelInfo.m_Motd.ToString());
}

void Channel::UpdateChannelMotd(DDSResponder & responder, std::string motd)
{
  if (m_State == ChannelState::kTemporary)
  {
    m_ChannelInfo.m_Motd = motd;
  }
  else if (m_State == ChannelState::kBuiltIn)
  {
    m_Interface.Call(&BuiltInChannel::UpdateMotd, m_Interface.GetLocalKey(), motd);
  }
  else if (m_State == ChannelState::kSquad)
  {
    m_Interface.Call(&Squad::UpdateMotd, m_Interface.GetLocalKey(), motd);
  }
  else
  {
    DDSResponderCall(responder, "Error updating channel info");
    return;
  }

  DDSResponderCall(responder, "Updated channel info");
}


void Channel::GetInfo(DDSResponder & responder)
{
  std::string data = "Channel info for " + m_ChannelInfo.m_Name.ToString() + "\n";
  StormReflEncodePrettyJson(m_ChannelInfo, data);

  DDSResponderCall(responder, data);
}

void Channel::BeginLoad()
{
  DDSLog::LogInfo("Loading channel %llu", m_Interface.GetLocalKey());

  m_ChannelSubscription = m_Interface.CreateDataSubscription(DDSSubscriptionTarget<BuiltInChannelDatabaseObject>{},
    m_Interface.GetLocalKey(), ".m_ChannelInfo", &Channel::HandleBuiltInChannelUpdate, true, &Channel::HandleBuiltinDoesntExist, true);
}

void Channel::AddPendingMember(DDSResponder & responder, DDSKey user_key)
{
  DDSKey sub_id =
    m_Interface.CreateSubscription(DDSSubscriptionTarget<User>{}, user_key, ".m_UserInfo", &Channel::HandleMemberUpdate, true, user_key);

  m_MemberSubscriptionIds.emplace(std::make_pair(user_key, sub_id));
  DDSResponderCall(responder, ChannelJoinResult::kSuccess);
}

void Channel::RefusePendingMember(DDSResponder & responder, DDSKey user_key)
{
  DDSResponderCall(responder, ChannelJoinResult::kLocked);
}

void Channel::UpdateChannelMembershipFlags()
{
  for (auto squad_member : m_SquadInfo.m_Users)
  {
    for (auto user : m_ChannelInfo.m_Users)
    {
      if (squad_member.second.m_UserKey == user.second.m_UserKey)
      {
        if (user.second.m_MembershipFlags != squad_member.second.m_MembershipFlags)
        {
          user.second.m_MembershipFlags = squad_member.second.m_MembershipFlags;
        }
      }
    }
  }
}

DDSKey Channel::GetChannelKeyFromName(const char * name)
{
  return crc64lowercase(name);
}
<<<<<<< HEAD
=======

#endif
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
