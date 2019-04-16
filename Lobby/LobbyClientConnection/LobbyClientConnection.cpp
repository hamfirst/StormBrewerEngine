
#include <StormRefl/StormReflJsonStd.h>
#include <StormRefl/StormReflMetaEnum.h>

#include <HurricaneDDS/DDSLoadBalancerMessages.refl.meta.h>

#include "TinySHA1/TinySHA1.h"

#include "Foundation/Common.h"
#include "Foundation/Buffer/BufferUtil.h"

#include "ProjectSettings/ProjectName.h"
#include "ProjectSettings/ProjectVersion.h"
#include "ProjectSettings/ProjectPorts.h"

#include "Game/GameSimulationStats.refl.meta.h"

#include "Lobby/UserConnectionMessages.refl.meta.h"
#include "Lobby/SharedTypes.refl.meta.h"

#include "LobbyClientConnection/LobbyClientConnection.h"

LobbyClientConnection::LobbyClientConnection(LobbyLoginMode login_mode, std::string token, std::string load_balancer_host) :
        m_State(LobbyClientConnectionState::kDisconnected),
        m_ClientState(LobbyClientState::kDisconnected),
        m_LastPingTime(time(nullptr)),
        m_LoginMode(login_mode),
        m_LoginToken(std::move(token)),
        m_LoadBalancerHost(std::move(load_balancer_host)),
        m_RelocationToken(0)
{

}

void LobbyClientConnection::Connect()
{
  if (m_State != LobbyClientConnectionState::kDisconnected)
  {
    return;
  }

  m_State = LobbyClientConnectionState::kLoadBalancerConnecting;
  m_ClientState = LobbyClientState::kConnecting;
  m_WebSocket.StartConnect(m_LoadBalancerHost.c_str(), LOBBY_LB_PORT, "/", "localhost", kProjectName);
  m_RelocationToken = 0;
}

void LobbyClientConnection::Update()
{
  if (m_State == LobbyClientConnectionState::kDisconnected)
  {
    Connect();
    return;
  }

  if(m_State == LobbyClientConnectionState::kLoadBalancerConnecting)
  {
    if(m_WebSocket.IsConnecting())
    {
      return;
    }
    else
    {
      auto packet = m_WebSocket.PollPacket();

      if (packet == false)
      {
        if (m_WebSocket.IsConnected() == false)
        {
          m_State = LobbyClientConnectionState::kDisconnected;
        }
        return;
      }

      auto str = BufferToString(packet->m_Buffer);

      DDSLoadBalancerResponse resp;
      StormReflParseJson(resp, str);

      m_WebSocket.StartConnect(resp.host.c_str(), resp.port, "/", "localhost", kProjectName);
      m_State = LobbyClientConnectionState ::kConnecting;
    }
  }

  if(m_State == LobbyClientConnectionState::kConnecting)
  {
    if(m_WebSocket.IsConnected())
    {
      m_State = LobbyClientConnectionState::kAuthenticating;
    }
    else if(m_WebSocket.IsConnecting() == false)
    {
      m_State = LobbyClientConnectionState::kDisconnected;
      return;
    }
    else
    {
      return;
    }
  }

  if(m_State == LobbyClientConnectionState::kConnected)
  {
    auto cur_time = time(nullptr);
    if (cur_time - m_LastPingTime > 10)
    {
      m_LastPingTime = cur_time;

      UserMessageBase ping;
      SendMessage(ping, "ping");
    }
  }

  while (true)
  {
    auto packet = m_WebSocket.PollPacket();

    if (packet == false)
    {
      if (m_WebSocket.IsConnected() == false)
      {
        m_State = LobbyClientConnectionState::kDisconnected;
      }
      return;
    }

    auto str = BufferToString(packet->m_Buffer);

    UserMessageBase base_msg;
    StormReflParseJson(base_msg, str);

    switch (m_State)
    {
      case LobbyClientConnectionState::kAuthenticating:
        {
          UserVersionRequest msg;
          if (base_msg.c != "version" || StormReflParseJson(msg, str) == false)
          {
            ParseError();
            return;
          }

          UserMessageVersionResponse resp;
          resp.ver = LOBBY_VERSION;

#ifdef ENABLE_PROOF_OF_WORK
          sha1::SHA1 hash;
          for(int index = 0; index < 100000; ++index)
          {
            char proof_str[128];
            auto len = snprintf(proof_str, sizeof(proof_str), "%s%d", msg.prefix.c_str(), index);

            hash.reset();
            hash.processBytes(proof_str, len);

            uint32_t digest[5];
            hash.getDigest(digest);
            char tmp[48];
            snprintf(tmp, 45, "%08X%08X%08X%08X%08X", digest[0], digest[1], digest[2], digest[3], digest[4]);

            if(msg.sha == tmp)
            {
              resp.sha = index;
            }
          }
#endif

          SendMessage(resp, "version");
          m_State = LobbyClientConnectionState::kIdentifying;
        }
        break;
      case LobbyClientConnectionState::kIdentifying:
        {
          if (base_msg.c != "identify")
          {
            ParseError();
            return;
          }

          UserMessageIdentifyResponse resp;
          if(m_RelocationToken != 0)
          {
            resp.c = "lr";
            resp.token = std::to_string(m_RelocationToken);
          }
          else
          {
            switch(m_LoginMode)
            {
#ifdef ENABLE_AUTH_GUEST
            case LobbyLoginMode::kGuest:
              resp.c = "lguest";
              break;
#endif
            default:
              assert(false);
              break;
            }
          }

          m_State = LobbyClientConnectionState::kIdentifyingResponse;
        }
        break;
      case LobbyClientConnectionState::kIdentifyingResponse:
        {
          if(base_msg.c == "logged_in")
          {
            if(m_LatencySamples.size() == 0)
            {
              m_State = LobbyClientConnectionState::kWaitingForLatencySamples;
            }
            else
            {
              m_State = LobbyClientConnectionState::kConnected;
              m_ClientState = LobbyClientState::kConnected;
            }
          }
          else if(base_msg.c == "")
          {

          }
        }
        break;
      case LobbyClientConnectionState::kConnected:
        break;
    }
  }
}


LobbyClientState LobbyClientConnection::GetState() const
{
  return m_ClientState;
}

void LobbyClientConnection::SetLatencySamples(const std::vector<int> & samples)
{
  m_LatencySamples = samples;

  if(m_State == LobbyClientConnectionState::kWaitingForLatencySamples)
  {
    m_State = LobbyClientConnectionState::kConnected;
    m_ClientState = LobbyClientState::kConnected;
  }
}

void LobbyClientConnection::SendNewUserName(const std::string_view & name)
{
  UserMessageCreateName msg;
  msg.uname = name;

  SendMessage(msg, "user_name");
}

void LobbyClientConnection::SendGameChat(const std::string_view & msg)
{
  UserChatMessageIncoming chat;
  chat.msg = msg;
  SendMessage(chat, "game_chat");
}

template <typename T>
void LobbyClientConnection::SendMessage(T & t, czstr msg)
{
  if (m_State == LobbyClientConnectionState::kDisconnected)
  {
    return;
  }

  t.c = msg;
  auto packet_data = StormReflEncodeJson(t);
  if (m_State == LobbyClientConnectionState::kConnecting)
  {
    m_PendingMessages.emplace_back(std::move(packet_data));
  }
  else
  {
    m_WebSocket.SendString(packet_data);
  }
}

void LobbyClientConnection::Relocate(UserMessageRelocate & msg)
{
  m_RelocationToken = msg.relocation_token;
  m_WebSocket.StartConnect(msg.new_host.c_str(), msg.new_port, "/", kProjectName);
}

void LobbyClientConnection::ParseError()
{
  m_WebSocket.Close();
  m_State = LobbyClientConnectionState::kDisconnected;
}
