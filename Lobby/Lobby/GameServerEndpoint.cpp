
#include "GameServerEndpoint.h"

#include "GameServerConnection.refl.meta.h"
#include "GameServerMessages.refl.meta.h"

GameServerEndpoint::GameServerEndpoint(const DDSEndpointInterface & endpoint_interface) :
  m_State(EndpointState::kIdentify),
  m_EndpointInterface(endpoint_interface)
{

}

void GameServerEndpoint::HandleData(const char * data)
{
  Hash hash = crc32begin();
  while (true)
  {
    if (*data == ' ')
    {
      break;
    }

    if (*data == 0)
    {
      m_EndpointInterface.ForceDisconnect();
      return;
    }

    hash = crc32additive(hash, *data);
    data++;
  }

  hash = crc32end(hash);
  data++;

  if (*data == 0)
  {
    m_EndpointInterface.ForceDisconnect();
    return;
  }

  GameServerMessageType type;
  if (StormReflGetEnumFromHash(type, hash) == false)
  {
    m_EndpointInterface.ForceDisconnect();
    return;
  }

  switch (m_State)
  {
  case kIdentify:
    {
      if(type == GameServerMessageType::kIdentifyNew)
      {
        GameServerIdentifyNew msg;
        if (StormReflParseJson(msg, data) == false)
        {
          m_EndpointInterface.ForceDisconnect();
          return;
        }

        if (msg.m_Version != kGameServerVersion)
        {
          SendPacket(GameServerRedownload{});
          m_EndpointInterface.ForceDisconnect();
          return;
        }

        m_State = kCreatingObject;
        ConnectToObject();
      }
      else if (type == GameServerMessageType::kIdentifyRelocate)
      {
        GameServerIdentifyRelocate msg;
        if (StormReflParseJson(msg, data) == false)
        {
          m_EndpointInterface.ForceDisconnect();
          return;
        }

        if (m_EndpointInterface.IsLocalKey(msg.m_RelocationKey))
        {
          m_ServerKey = msg.m_RelocationKey;
          if (m_EndpointInterface.ConnectToLocalObject(&GameServerConnection::ConnectToEndpoint, m_ServerKey) == false)
          {
            m_EndpointInterface.ForceDisconnect();
            return;
          }

          SendPacket(GameServerRelocated{});
          m_State = kConnected;
        }
        else
        {
          auto node_info = m_EndpointInterface.GetNodeInfo(msg.m_RelocationKey);
          if (node_info)
          {
            std::string ip_addr = GetNodeAddrAsString(node_info->m_Addr);
            GameServerRelocate relocate{ ip_addr, node_info->m_EndpointPorts[1], msg.m_RelocationKey };

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
        m_EndpointInterface.ForceDisconnect();
        return;
      }
    }
    break;
  case kCreatingObject:
    {
      m_EndpointInterface.ForceDisconnect();
      return;
    }
    break;
  case kConnected:
    {
      m_EndpointInterface.Call(&GameServerConnection::GotMessage, m_ServerKey, type, std::string(data));
    }
    break;
  case kDisconnecting:
    break;
  }
}

void GameServerEndpoint::HandleDisconnect()
{
  if (m_State == kConnected)
  {
    m_EndpointInterface.DestroyObject<GameServerConnection>(m_ServerKey);
  }
}

void GameServerEndpoint::ConnectToObject()
{
  if (m_EndpointInterface.CreateObject<GameServerConnection>(m_ServerKey) == false)
  {
    m_EndpointInterface.CreateTimer(m_Callback, std::chrono::seconds(1), [this] { ConnectToObject(); });
    return;
  }

  m_State = kConnected;
  m_EndpointInterface.Call(&GameServerConnection::SetRemoteHost, m_ServerKey, m_EndpointInterface.GetRemoteIpAsString());
  m_EndpointInterface.ConnectToLocalObject(&GameServerConnection::ConnectToEndpoint, m_ServerKey);
}

template <typename T>
void GameServerEndpoint::SendPacket(const T & t)
{
  std::string packet_data = StormReflGetEnumAsString(T::Type);
  packet_data += ' ';
  StormReflEncodeJson(t, packet_data);

  m_EndpointInterface.SendData(packet_data);
}
