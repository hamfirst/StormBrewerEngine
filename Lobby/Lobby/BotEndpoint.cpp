
#include "BotEndpoint.h"

#include "BotConnection.refl.meta.h"
#include "BotMessages.refl.meta.h"


#if defined(ENABLE_BOTS) && defined(ENABLE_CHANNELS)

BotEndpoint::BotEndpoint(const DDSEndpointInterface & endpoint_interface) :
  m_State(EndpointState::kIdentify),
  m_EndpointInterface(endpoint_interface),
  m_Error(false)
{

}

void BotEndpoint::HandleData(const char * data)
{
  if (m_Error)
  {
    return;
  }

  DDSLog::LogVerbose("Got data %s\n", data);

  const char * cmd_start = StormDataFindJsonStartByPath(".c", data);
  std::string cmd;

  if (cmd_start)
  {
    StormReflParseJson(cmd, cmd_start);
  }


  if (m_State == kIdentify)
  {
    BotIdentify msg;
    if (StormReflParseJson(msg, data) == false)
    {
      m_EndpointInterface.ForceDisconnect();
      return;
    }

    if (msg.relocation_key != 0)
    {
      if (m_EndpointInterface.IsLocalKey(msg.relocation_key))
      {
        m_BotKey = msg.relocation_key;
        if (m_EndpointInterface.ConnectToLocalObject(&BotConnection::ConnectToEndpoint, m_BotKey) == false)
        {
          m_EndpointInterface.ForceDisconnect();
          return;
        }

        SendPacket(BotMessageBase{"relocated"});
        m_State = kConnected;
      }
      else
      {
        auto node_info = m_EndpointInterface.GetNodeInfo(msg.relocation_key);
        if (node_info)
        {
          std::string ip_addr = GetNodeAddrAsString(node_info->get().m_Addr);
          BotMessageRelocate relocate{ "relocate", ip_addr, node_info->get().m_EndpointPorts[1], msg.relocation_key };

          SendPacket(relocate);
        }
        else
        {
          m_EndpointInterface.ForceDisconnect();
          m_State = kDisconnecting;
        }
      }
    }
    else
    {
      m_UserName = msg.user_name;
      m_Password = msg.password;

      m_State = kCreatingObject;
      ConnectToObject();
    }
  }
  else if (m_State == kConnected)
  {
    m_EndpointInterface.Call(&BotConnection::GotMessage, m_BotKey, cmd, std::string(data));
  }
}

void BotEndpoint::HandleDisconnect()
{
  if (m_State == kConnected)
  {
    m_EndpointInterface.DestroyObject<BotConnection>(m_BotKey);
  }
}

void BotEndpoint::ConnectToObject()
{
  if (m_EndpointInterface.CreateObject<BotConnection>(m_BotKey) == false)
  {
    m_EndpointInterface.CreateTimer(m_Callback, std::chrono::seconds(1), [this] { ConnectToObject(); });
    return;
  }

  m_State = kConnected;
  m_EndpointInterface.ConnectToLocalObject(&BotConnection::ConnectToEndpoint, m_BotKey);
  m_EndpointInterface.Call(&BotConnection::LoadBot, m_BotKey, m_UserName, m_Password);
}

template <typename T>
void BotEndpoint::SendPacket(const T & t)
{
  std::string packet_data;
  StormReflEncodeJson(t, packet_data);

  m_EndpointInterface.SendData(packet_data);
}

#endif