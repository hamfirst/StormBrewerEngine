
#include <StormData/StormDataChangePacket.h>

#include <HurricaneDDS/DDSResponderCall.h>
#include <HurricaneDDS/DDSResponder.refl.meta.h>

#include <hash/Hash64.h>
#include <sb/vector.h>

#include "Bot.refl.meta.h"
#include "BotConnection.refl.meta.h"
#include "BotMessages.refl.meta.h"
#include "Channel.refl.meta.h"
#include "User.refl.meta.h"
#include "UserConnection.refl.meta.h"
#include "ServerList.refl.meta.h"
#include "WelcomeInfo.refl.meta.h"


#if defined(ENABLE_BOTS) && defined(ENABLE_CHANNELS)

Bot::Bot(DDSNodeInterface node_interface, BotDatabaseObject & db_object) :
  m_Interface(node_interface), m_Data(db_object),
  m_EndpointKey(0),
  m_ChannelKey(Channel::GetChannelKeyFromName(db_object.m_Channel.c_str()))
{

}

void Bot::AddEndpoint(DDSResponder & responder, DDSKey key, std::string user_name, std::string password)
{
  if (m_EndpointKey != 0)
  {
    DDSResponderCall(responder, false);
    return;
  }

  m_EndpointKey = key;

  m_Interface.Call(&Channel::AddBot, m_ChannelKey, m_Interface.GetLocalKey(), m_Data.m_UserName);
  m_ChannelSubscriptionId = m_Interface.CreateSubscription(DDSSubscriptionTarget<Channel>{}, m_ChannelKey, ".m_ChannelInfo", &Bot::HandleChannelUpdate, true);
  m_ServerListSubscriptionId = m_Interface.CreateSubscription(DDSSubscriptionTarget<ServerList>{}, m_ChannelKey, "", &Bot::HandleServerListUpdate, true);
  DDSResponderCall(responder, true);
}

void Bot::RemoveEndpoint(DDSKey key)
{
  if (m_EndpointKey == key)
  {
    m_EndpointKey = 0;

    m_Interface.Call(&Channel::RemoveBot, m_ChannelKey, m_Interface.GetLocalKey());
    m_Interface.DestroySubscription<Channel>(m_ChannelKey, m_ChannelSubscriptionId);
    m_Interface.DestroySubscription<ServerList>(m_ChannelKey, m_ServerListSubscriptionId);
  }
}

void Bot::GotChat(DDSKey user_id, DDSKey endpoint_id, std::string user_name, std::string message)
{
  m_Interface.Call(&BotConnection::SendData, m_EndpointKey, StormReflEncodeJson(BotMessageChannelChat{ "chat", user_name, message, user_id, endpoint_id }));
}

void Bot::HandleChannelUpdate(std::string data)
{
  m_Interface.Call(&BotConnection::SendData, m_EndpointKey, StormReflEncodeJson(BotMessageUpdate{ "channel", data }));
}

void Bot::HandleServerListUpdate(std::string data)
{
  m_Interface.Call(&BotConnection::SendData, m_EndpointKey, StormReflEncodeJson(BotMessageUpdate{ "server", data }));
}

void Bot::SendChatToChannel(std::string message)
{
  m_Interface.Call(&Channel::SendBotChatToChannel, m_ChannelKey, m_Interface.GetLocalKey(), message);
}

void Bot::SendChatToUser(DDSKey user_id, std::string message)
{
  m_Interface.Call(&User::SendNotification, user_id, m_Data.m_UserName.ToString() + ": " + message);
}

void Bot::SendChatToEndpoint(DDSKey endpoint_id, std::string message)
{
  m_Interface.Call(&UserConnection::SendNotification, endpoint_id, m_Data.m_UserName.ToString() + ": " + message);
}

void Bot::SetChannelMotd(std::string motd)
{
  auto responder = CreateEmptyResponder(m_Interface);
  m_Interface.CallWithForwardedResponder(&Channel::UpdateChannelMotd, m_ChannelKey, responder, motd);
}

void Bot::SetWelcomeInfoTab(DDSResponder & responder, std::string tab)
{
  m_Data.m_WelcomeInfoTab = tab;
  DDSResponderCall(responder, "Successfully set welcome info tab");
}

void Bot::UpdateWelcomeInfo(std::string info)
{
  if (m_Data.m_WelcomeInfoTab.length() == 0)
  {
    return;
  }

  auto responder = CreateEmptyResponder(m_Interface);
  m_Interface.CallSharedWithResponder(&WelcomeInfo::UpdateInfo, &Bot::HandleWelcomeInfoUpdateResponse, this, m_Data.m_WelcomeInfoTab.ToString(), info);
}

void Bot::HandleWelcomeInfoUpdateResponse(std::string data)
{

}

void Bot::ProcessGameResult(GameServerGameResult result, DDSKey game_id)
{
  BotMessageGameResult msg;
  msg.c = "game_result";
  msg.game_id = game_id;
  msg.game_info = result;

  m_Interface.Call(&BotConnection::SendData, m_EndpointKey, StormReflEncodeJson(msg));
}

void Bot::GetInfo(DDSResponder & responder)
{
  
}

void Bot::BeginLoad()
{
  m_Interface.FinalizeObjectLoad();
}

#endif

