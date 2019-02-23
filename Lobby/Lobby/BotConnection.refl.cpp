
#include <hash/Hash64.h>

#include <HurricaneDDS/DDSRandom.h>

#include <StormRefl/StormReflJsonStd.h>

#include "BotConnection.refl.meta.h"
#include "BotMessages.refl.meta.h"
#include "Bot.refl.meta.h"
#include "GameServerConnection.refl.meta.h"

#if defined(ENABLE_BOTS) && defined(ENABLE_CHANNELS)

BotConnection::BotConnection(DDSNodeInterface node_interface) :
  m_Interface(node_interface), m_State(BotConnectionState::kWaitingForConnection), m_Error(false), m_Relocating(false)
{
  
}

void BotConnection::ConnectToEndpoint(DDSConnectionId connection_id)
{
  if (m_ConnectionId)
  {
    m_Interface.DisconnectLocalConnection(connection_id);
    return;
  }

  m_ConnectionId = connection_id;

  for (auto & data : m_PendingMessages)
  {
    m_Interface.SendDataToLocalConnection(*m_ConnectionId, data);
  }

  m_PendingMessages.clear();
}

void BotConnection::ParseError()
{
  if (m_ConnectionId)
  {
    m_Interface.DisconnectLocalConnection(*m_ConnectionId);
  }

  m_Error = true;
  return;
}

void BotConnection::PreDestroy()
{
  if (m_Relocating == false && m_State == BotConnectionState::kConnected)
  {
    m_Interface.Call(&Bot::RemoveEndpoint, m_BotId, m_Interface.GetLocalKey());
  }
}

void BotConnection::PreMoveObject()
{
  DDSLog::LogVerbose("Moving connection to new server %llu", m_Interface.GetLocalKey());

  auto node_info = m_Interface.GetNodeInfo(m_Interface.GetLocalKey());
  if (node_info)
  {
    std::string ip_addr = GetNodeAddrAsString(node_info->get().m_Addr);
    BotMessageRelocate relocate{ "relocate", ip_addr, node_info->get().m_EndpointPorts[0], m_Interface.GetLocalKey() };
    SendData(StormReflEncodeJson(relocate));
    m_Relocating = true;
  }
  else
  {
    if (m_ConnectionId)
    {
      m_Interface.DisconnectLocalConnection(*m_ConnectionId);
    }
  }

  m_ConnectionId = {};
}


void BotConnection::LoadBot(std::string user_name, std::string password)
{
  std::transform(user_name.begin(), user_name.end(), user_name.begin(), tolower);
  m_BotId = crc64(user_name);

  m_Interface.CallWithResponderErrorBack(&Bot::AddEndpoint, m_BotId, &BotConnection::HandleBotLoad, &BotConnection::HandleBotLoadFail, this, m_Interface.GetLocalKey(), user_name, password);
}

void BotConnection::GotMessage(std::string cmd, std::string data)
{
  if (m_State != BotConnectionState::kConnected)
  {
    return;
  }

  if (cmd == "chat")
  {
    BotMessageSendChatToChannel msg;
    if (StormReflParseJson(msg, data.c_str()) == false)
    {
      ParseError();
      return;
    }

    m_Interface.Call(&Bot::SendChatToChannel, m_BotId, msg.msg);
  }
  else if (cmd == "motd")
  {
    BotMessageChannelMotd msg;
    if (StormReflParseJson(msg, data.c_str()) == false)
    {
      ParseError();
      return;
    }

    m_Interface.Call(&Bot::SetChannelMotd, m_BotId, msg.motd);
  }
  else if (cmd == "winfo")
  {
    BotMessageChannelMotd msg;
    if (StormReflParseJson(msg, data.c_str()) == false)
    {
      ParseError();
      return;
    }

    m_Interface.Call(&Bot::UpdateWelcomeInfo, m_BotId, msg.motd);
  }
  else if (cmd == "notify")
  {
    BotMessageSendChatToUser msg;
    if (StormReflParseJson(msg, data.c_str()) == false)
    {
      ParseError();
      return;
    }

    m_Interface.Call(&Bot::SendChatToUser, m_BotId, msg.user_id, msg.msg);
  }
  else if (cmd == "notify_ep")
  {
    BotMessageSendChatToUser msg;
    if (StormReflParseJson(msg, data.c_str()) == false)
    {
      ParseError();
      return;
    }

    m_Interface.Call(&Bot::SendChatToEndpoint, m_BotId, msg.user_id, msg.msg);
  }
  else if (cmd == "game")
  {
    BotMessageCreateGame msg;
    if (StormReflParseJson(msg, data.c_str()) == false)
    {
      ParseError();
      return;
    }

    m_Interface.Call(&GameServerConnection::CreateBotGame, msg.server_id, m_BotId, msg.game_id, msg.game_settings, msg.players);
  }
}

void STORM_REFL_FUNC BotConnection::HandleBotLoad(bool success)
{
  if (success == false)
  {
    SendPacket(BotErrorMessage{"err", "This bot already has a connection"});

    if (m_ConnectionId)
    {
      m_Interface.DisconnectLocalConnection(*m_ConnectionId);
    }
    return;
  }

  m_State = BotConnectionState::kConnected;
  SendPacket(BotMessageBase{ "connected" });
}

void STORM_REFL_FUNC BotConnection::HandleBotLoadFail()
{
  SendPacket(BotErrorMessage{ "err", "Invalid credentials" });

  if (m_ConnectionId)
  {
    m_Interface.DisconnectLocalConnection(*m_ConnectionId);
  }
}

void BotConnection::SendData(std::string data)
{
  if (m_ConnectionId)
  {
    m_Interface.SendDataToLocalConnection(*m_ConnectionId, data);
  }
  else
  {
    m_PendingMessages.emplace_back(data);
  }
}

template <typename T>
void BotConnection::SendPacket(const T & t)
{
  std::string packet_data;
  StormReflEncodeJson(t, packet_data);

  SendData(packet_data);
}

#endif