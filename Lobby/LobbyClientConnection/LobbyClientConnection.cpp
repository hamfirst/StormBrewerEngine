
#include <StormRefl/StormReflJsonStd.h>
#include <StormRefl/StormReflMetaEnum.h>

#include <HurricaneDDS/DDSLoadBalancerMessages.refl.meta.h>

#include "TinySHA1/TinySHA1.h"

#include "Foundation/Common.h"
#include "Foundation/Buffer/BufferUtil.h"

#include "ProjectSettings/ProjectName.h"
#include "ProjectSettings/ProjectVersion.h"
#include "ProjectSettings/ProjectPorts.h"

#include "Game/SimulationEvents/GameSimulationStats.refl.meta.h"

#include "LobbyShared/SharedTypes.refl.meta.h"

#include "Lobby/UserConnectionMessages.refl.meta.h"

#include "LobbyClientConnection/LobbyClientConnection.h"

LobbyClientConnection::LobbyClientConnection(const LobbyClientConnectionSettings & settings) :
        m_State(LobbyClientConnectionState::kDisconnected),
        m_ClientState(LobbyClientState::kDisconnected),
        m_RelocationState(LobbyRelocationState::kNotRelocating),
        m_LastPingTime(time(nullptr)),
        m_LoginMode(settings.m_LoginMode),
        m_LoginToken(settings.m_Token),
        m_GuestUserName(settings.m_GuestUserName),
        m_LoadBalancerHost(settings.m_LoadBalancerHostName),
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
  m_WebSocket.StartConnect(m_LoadBalancerHost.c_str(), LOBBY_LB_PORT, "/", "stormbrewers.com", kProjectName);
  m_RelocationToken = 0;

  m_ConnectionError.clear();
}

void LobbyClientConnection::Update()
{
  if(m_RelocationState == LobbyRelocationState::kConnecting)
  {
    if(m_WebSocket.IsConnected())
    {
      UserMessageIdentifyResponse resp;
      resp.token = std::to_string(m_RelocationToken);

      SendMessage(resp, "lr");

      m_RelocationState = LobbyRelocationState::kAuthenticating;
      m_RelocationToken = 0;
    }
    else if(m_WebSocket.IsConnecting() == false)
    {
      SetDisconnected("Lost connection to server");
      return;
    }
    else
    {
      return;
    }
  }
  else if(m_RelocationState == LobbyRelocationState::kAuthenticating)
  {
    auto packet = m_WebSocket.PollPacket();

    if (packet == false)
    {
      if (m_WebSocket.IsConnected() == false)
      {
        SetDisconnected("Lost connection to server");
      }
      return;
    }

    auto str = BufferToString(packet->m_Buffer);

    UserMessageBase base_msg;
    StormReflParseJson(base_msg, str);

    if(base_msg.c != "relocated")
    {
      SetDisconnected("Relocation failure");
      return;
    }

    for(auto & msg : m_PendingMessages)
    {
      m_WebSocket.SendString(msg);
    }

    m_PendingMessages.clear();
    m_RelocationState = LobbyRelocationState::kNotRelocating;
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
          SetDisconnected("Failed to establish connection to server");
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
      SetDisconnected("Lost connection to server");
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

  if(m_State == LobbyClientConnectionState::kDisconnected)
  {
    return;
  }

  while (true)
  {
    auto packet = m_WebSocket.PollPacket();

    if (packet == false)
    {
      if (m_WebSocket.IsConnected() == false)
      {
        SetDisconnected("Lost connection to server");
      }
      return;
    }

    auto str = BufferToString(packet->m_Buffer);

    UserMessageBase base_msg;
    StormReflParseJson(base_msg, str);

    if(base_msg.c == "error")
    {
      UserMessageConnectionError err;
      if(StormReflParseJson(err, str) == false)
      {
        ParseError();
      }
      else
      {
        SetDisconnected(err.msg.c_str());
      }
      return;
    }

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
          switch(m_LoginMode)
          {
#ifdef ENABLE_AUTH_GUEST
          case LobbyLoginMode::kGuest:
            resp.user_name = m_GuestUserName;
            SendMessage(resp, "lguest");
            break;
#endif
          default:
            assert(false);
            break;
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
          else if(base_msg.c == "new_user")
          {
            m_ClientState = LobbyClientState::kNewUser;
          }
          else if(base_msg.c == "repick_new_user")
          {
            m_ClientState = LobbyClientState::kNewUserRepick;
          }
          else
          {
            ParseError();
            return;
          }
        }
        break;
      case LobbyClientConnectionState::kConnected:
        {
          if(base_msg.c == "local")
          {
            UserLocalInfoUpdate msg;
            if(StormReflParseJson(msg, str) == false)
            {
              ParseError();
              return;
            }

            if(m_UserLocalData.IsValid() == false)
            {
              m_UserLocalData.Emplace();
            }

            StormDataApplyChangePacket(m_UserLocalData.Value(), msg.data.c_str());
            m_LocalDataUpdateCallback();
            return;
          }
          else if(base_msg.c == "server")
          {
            UserLocalInfoUpdate msg;
            if(StormReflParseJson(msg, str) == false)
            {
              ParseError();
              return;
            }

            if(m_GameList.IsValid() == false)
            {
              m_GameList.Emplace();
            }

            StormDataApplyChangePacket(m_GameList.Value(), msg.data.c_str());
            m_GameListUpdateCallback();
            return;
          }
          else if(base_msg.c == "winfo")
          {
            UserLocalInfoUpdate msg;
            if (StormReflParseJson(msg, str) == false)
            {
              ParseError();
              return;
            }

            if (m_WelcomeInfo.IsValid() == false)
            {
              m_WelcomeInfo.Emplace();
            }

            StormDataApplyChangePacket(m_WelcomeInfo.Value(), msg.data.c_str());
            m_WelcomeInfoUpdateCallback();
            return;
          }
          else if(base_msg.c == "c")
          {
            UserChatMessageOutgoing msg;
            if(StormReflParseJson(msg, str) == false)
            {
              ParseError();
              return;
            }

            m_ChatCallback(msg.channel_id, msg.user, msg.msg, msg.i, msg.b, msg.t);
            return;
          }
          else if(base_msg.c == "rterr")
          {
            UserMessageRuntimeError msg;
            if(StormReflParseJson(msg, str) == false)
            {
              ParseError();
              return;
            }

            m_RuntimeErrorCallback(msg.msg);
            return;
          }
          else if(base_msg.c == "smsg")
          {
            UserMessageRuntimeError msg;
            if(StormReflParseJson(msg, str) == false)
            {
              ParseError();
              return;
            }

            m_ServerMessageCallback(msg.msg);
            return;
          }
          else if(base_msg.c == "stxt")
          {
            UserMessageRuntimeError msg;
            if(StormReflParseJson(msg, str) == false)
            {
              ParseError();
              return;
            }

            m_ServerTextCallback(msg.msg);
            return;
          }
          else if(base_msg.c == "join_game")
          {
            UserGameInfoUpdate msg;
            if(StormReflParseJson(msg, str) == false)
            {
              ParseError();
              return;
            }

            m_GameInfo.Emplace();
            StormDataApplyChangePacket(m_GameInfo.Value(), msg.data.c_str());
            m_GameJoinCallback();
          }
          else if(base_msg.c == "game")
          {
            UserGameInfoUpdate msg;
            if(StormReflParseJson(msg, str) == false)
            {
              ParseError();
              return;
            }

            if(m_GameInfo.IsValid())
            {
              StormDataApplyChangePacket(m_GameInfo.Value(), msg.data.c_str());
              m_GameDataUpdateCallback();
            }
          }
          else if(base_msg.c == "game_join_failed")
          {
            m_GameJoinFailedCallback();
          }
          else if(base_msg.c == "cancel_matchmaking")
          {
            m_CancelMatchmakingCallback();
          }
          else if(base_msg.c == "leave_game")
          {
            m_GameInfo.Clear();
            m_GameLaunchInfo.Clear();

            m_GameLeaveCallback();
          }
          else if(base_msg.c == "game_preview")
          {
            UserGamePreviewUpdate msg;
            if(StormReflParseJson(msg, str) == false)
            {
              ParseError();
              return;
            }

            if(msg.request_id != m_GameListPreviewRequestId)
            {
              return;
            }

            if(m_GameListPreview.IsValid() == false)
            {
              m_GameListPreview.Emplace();
            }

            StormDataApplyChangePacket(m_GameInfo.Value(), msg.data.c_str());
            m_GamePreviewUpdateCallback();
          }
          else if(base_msg.c == "game_preview_cancel")
          {
            m_GameListPreview.Clear();
            m_GamePreviewCancelCallback();
          }
          else if(base_msg.c == "launch_game")
          {
            UserLaunchGameMessage msg;
            if(StormReflParseJson(msg, str) == false)
            {
              ParseError();
              return;
            }

            m_GameLaunchInfo.Emplace();
            m_GameLaunchInfo->m_ServerIp = msg.server_ip;
            m_GameLaunchInfo->m_ServerPort = msg.server_port;
            m_GameLaunchInfo->m_UserId = msg.user_id;
            m_GameLaunchInfo->m_GameId = msg.game_id;
            m_GameLaunchInfo->m_Token = msg.token;

            m_LaunchGameCallback();
          }
          else if(base_msg.c == "reset_game")
          {
            m_ResetGameCallback();
            m_GameLaunchInfo.Clear();
          }
          else if(base_msg.c == "game_chat")
          {
            UserChatMessageGame msg;
            if(StormReflParseJson(msg, str) == false)
            {
              ParseError();
              return;
            }

            m_GameChatCallback(msg.user, msg.msg, msg.icon, msg.title);
          }
          else if(base_msg.c == "user_stats")
          {
            UserStatsData msg;
            if(StormReflParseJson(msg, str) == false)
            {
              ParseError();
              return;
            }

            m_StatsCallback(msg.name, msg.stats, msg.last_game_played);
          }
          else if(base_msg.c == "edit_lobby_info")
          {

          }
          else if(base_msg.c == "edit_channel_info")
          {

          }
#ifdef ENABLE_REWARDS
          else if(base_msg.c == "xp")
          {
            UserGotXP msg;
            if(StormReflParseJson(msg, str) == false)
            {
              ParseError();
              return;
            }

            m_XPCallback(msg.xp, msg.level, msg.last, msg.xp_info);
          }
#endif
        }
        break;
    }
  }
}


LobbyClientState LobbyClientConnection::GetState() const
{
  return m_ClientState;
}

const std::string & LobbyClientConnection::GetConnectionError() const
{
  return m_ConnectionError;
}

bool LobbyClientConnection::HasLatencySamples() const
{
  return m_LatencySamples.size() > 0;
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

void LobbyClientConnection::SendCreatePrivateGame(const GameInitSettings & settings, const std::string_view & password)
{
  UserGameCreate msg;

  msg.create_data = settings;
  msg.password = password;

  for(int zone = 0; zone < kNumProjectZones; ++zone)
  {
    msg.zone_info.m_Latencies[zone] = m_LatencySamples[zone];
  }

  SendMessage(msg, "create_game");
}

void LobbyClientConnection:: SendJoinPrivateGame(uint32_t join_code, const std::string_view & password, bool observer)
{
  UserJoinGame msg;
  msg.password = password;
  msg.join_code = join_code;
  msg.observer = observer;

  for(int zone = 0; zone < kNumProjectZones; ++zone)
  {
    msg.zone_info.m_Latencies[zone] = m_LatencySamples[zone];
  }

  SendMessage(msg, "join_game");
}

void LobbyClientConnection::SendJoinMatchmaker(uint32_t playlist_mask, bool ranked)
{
  UserMatchmakeRequest msg;

  msg.playlist_mask = playlist_mask;

  for(int zone = 0; zone < kNumProjectZones; ++zone)
  {
    msg.zone_info.m_Latencies[zone] = m_LatencySamples[zone];
  }

  SendMessage(msg, ranked ? "matchmake_competitive" : "matchmake_casual");
}

void LobbyClientConnection::CancelMatchmaker()
{
  UserMessageBase msg;
  SendMessage(msg, "cancel_matchmaking");
}

void LobbyClientConnection::SendGameReady(bool ready)
{
  UserReadyGame msg;
  msg.ready = ready;
  SendMessage(msg, "change_ready");
}

void LobbyClientConnection::SendGameStart()
{
  UserMessageBase msg;
  SendMessage(msg, "start_game");
}

#ifdef NET_USE_LOADOUT
void LobbyClientConnection::SendGameChangeLoadout(const GamePlayerLoadout & loadout)
{
  UserSwitchLoadout msg;
  msg.loadout = loadout;
  SendMessage(msg, "change_loadout");
}
#endif

void LobbyClientConnection::SendGameChangeSettings(const GameInitSettings & settings)
{
  UserSwitchSettings msg;
  msg.settings = settings;
  SendMessage(msg, "change_settings");
}

void LobbyClientConnection::SendGameTeamSwitch(DDSKey user_id, int team)
{
  UserSwitchTeam msg;
  msg.team = team;
  msg.target_user = user_id;
  SendMessage(msg, "change_team");
}

void LobbyClientConnection::SendGameKickUser(DDSKey user_id)
{
  UserKickUserFromGame msg;
  msg.user = user_id;
  SendMessage(msg, "kick_game_user");
}

void LobbyClientConnection::SendGameChat(const std::string_view & msg)
{
  UserChatMessageIncoming chat;
  chat.msg = msg;
  SendMessage(chat, "game_chat");
}

void LobbyClientConnection::SendCancelMatchmaking()
{
  UserMessageBase msg;
  SendMessage(msg, "cancel_matchmaking");
}

void LobbyClientConnection::SendLeaveGame()
{
  UserMessageBase msg;
  SendMessage(msg, "leave_game");
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
  SetDisconnected("Parse Error");
}

void LobbyClientConnection::SetDisconnected(czstr error_message)
{
  m_WebSocket.Close();

  m_State = LobbyClientConnectionState::kDisconnected;
  m_ClientState = LobbyClientState::kDisconnected;
  m_RelocationState = LobbyRelocationState::kNotRelocating;

  m_UserLocalData.Clear();
  m_GameInfo.Clear();
  m_WelcomeInfo.Clear();
  m_GameList.Clear();
  m_GameListPreview.Clear();
  m_GameLaunchInfo.Clear();

  m_ConnectionError = error_message;


}
