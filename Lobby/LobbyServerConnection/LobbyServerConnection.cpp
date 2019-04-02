
#include <StormRefl/StormReflJsonStd.h>
#include <StormRefl/StormReflMetaEnum.h>

#include "Foundation/Common.h"
#include "Foundation/Buffer/BufferUtil.h"

#include "UniballSimulation/Sim.refl.meta.h"

#include "LobbyServerConnection.h"
#include "MapList.h"

#include "ServerSettings.refl.h"
#include "GameServerMessages.refl.meta.h"

#include <ctime>


LobbyServerConnection::LobbyServerConnection(MapList & map_list) :
  m_State(LobbyServerConnectionState::kDisconnected),
  m_MapList(map_list),
  m_LastPingTime(time(nullptr)),
  m_NextValidationId(1),
  m_WantsRedownload(false)
{
  
}

bool LobbyServerConnection::Connect()
{
  if (m_State != LobbyServerConnectionState::kDisconnected)
  {
    return false;
  }
  
  m_State = LobbyServerConnectionState::kConnecting;
  if (m_WebSocket.Connect(g_ServerSettings.LobbyServerHost.data(), g_ServerSettings.LobbyServerPort, "/", "uniball"))
  {
    m_State = LobbyServerConnectionState::kAuthenticating;

    GameServerIdentifyNew msg = {};
    msg.m_Version = kGameServerVersion;
    SendMessage(msg);
    return true;
  }
  else
  {
    m_State = LobbyServerConnectionState::kDisconnected;
    return false;
  }
}

void LobbyServerConnection::Update()
{
  if (m_State == LobbyServerConnectionState::kDisconnected)
  {
    return;
  }

  auto cur_time = time(nullptr);
  if (cur_time - m_LastPingTime > 10)
  {
    m_LastPingTime = cur_time;
    m_WebSocket.SendPacket(Buffer{}, WebSocketPacketType::kPing);
  }

  while (true)
  {
    auto packet = m_WebSocket.PollPacket();

    if (packet == false)
    {
      if (m_WebSocket.IsConnected() == false)
      {
        m_State = LobbyServerConnectionState::kDisconnected;
      }
      return;
    }

    if (packet->m_Type == WebSocketPacketType::kPong)
    {
      continue;
    }

    auto str = BufferToString(packet->m_Buffer);
    const char * data_start = str.data();

    Hash type_hash = crc32begin();
    while (*data_start != ' ')
    {
      if (*data_start == 0)
      {
        ParseError();
        return;
      }

      type_hash = crc32additive(type_hash, *data_start);
      data_start++;
    }

    type_hash = crc32end(type_hash);
    
    GameServerMessageType type;
    if (StormReflGetEnumFromHash(type, type_hash) == false)
    {
      ParseError();
      return;
    }

    data_start++;

    switch (m_State)
    {
    case LobbyServerConnectionState::kAuthenticating:
      {
        if(type == GameServerMessageType::kRedownload)
        {
          m_WantsRedownload = true;
          return;
        }

        GameServerAuthenticateRequest req;
        if (type != GameServerMessageType::kAuthRequest || StormReflParseJson(req, data_start) == false)
        {
          ParseError();
          return;
        }

        uint64_t challenge_response = crc64(std::to_string(req.m_Challenge)) ^ kGameServerChallengePad;
        GameServerAuthenticateResponse resp;
        resp.m_Challenge = challenge_response;
        resp.m_Name = g_ServerSettings.ServerName;
        resp.m_Location = g_ServerSettings.ServerLocation;
        resp.m_Maps = m_MapList.GetMapList();
        resp.m_Host = g_ServerSettings.OverrideHost;
        resp.m_GamePort = g_ServerSettings.GamePort;
        resp.m_PingPort = g_ServerSettings.PingPort;

        SendMessage(resp);

        m_State = LobbyServerConnectionState::kConnected;
      }
      break;
    case LobbyServerConnectionState::kConnected:
      {
        if (type == GameServerMessageType::kRedownload)
        {
          m_WantsRedownload = true;
          return;
        }
        else if (type == GameServerMessageType::kAuthUserSuccess)
        {
          GameServerAuthenticateUserSuccess msg;
          if (StormReflParseJson(msg, data_start) == false)
          {
            ParseError();
            return;
          }

          auto val = m_Validations.find(msg.m_ResponseId);
          if (val == m_Validations.end())
          {
            return;
          }

          val->second(msg);
          m_Validations.erase(val);
          return;
        }
        else if (type == GameServerMessageType::kAuthUserFail)
        {
          GameServerAuthenticateUserFailure msg;
          if (StormReflParseJson(msg, data_start) == false)
          {
            ParseError();
            return;
          }

          auto val = m_Validations.find(msg.m_ResponseId);
          if (val == m_Validations.end())
          {
            return;
          }

#ifdef _DEBUG
          GameServerAuthenticateUserSuccess new_msg;
          new_msg.m_ResponseId = msg.m_ResponseId;
          new_msg.m_UserId = rand();
          new_msg.m_AccountId = rand();
          new_msg.m_GameId = 0;

          new_msg.m_Name = "User" + std::to_string(rand());

          new_msg.m_GameData.m_Map = "miniball";
          new_msg.m_GameData.m_Name = "miniball";
          new_msg.m_GameData.m_PlayerLimit = 6;
          new_msg.m_GameData.m_ScoreLimit = 10;
          new_msg.m_GameData.m_TimeLimit = 0;

          val->second(new_msg);
#else
          val->second({});
#endif
          m_Validations.erase(val);
          return;
        }
        else if (type == GameServerMessageType::kTeamSwitch)
        {
          GameServerTeamSwitch msg;
          if (StormReflParseJson(msg, data_start) == false)
          {
            ParseError();
            return;
          }

          m_TeamSwitchCallback(msg.m_UserId, msg.m_GameId, msg.m_Team);
        }
        else if (type == GameServerMessageType::kForceDisconnect)
        {
          GameServerForceUserDisconnect msg;
          if (StormReflParseJson(msg, data_start) == false)
          {
            ParseError();
            return;
          }

          m_DisconnectCallback(msg.m_UserId, msg.m_GameId);
        }
        else if (type == GameServerMessageType::kRelocate)
        {
          GameServerRelocate msg;
          if (StormReflParseJson(msg, data_start) == false)
          {
            ParseError();
            return;
          }

          Relocate(msg);
        }
        else if (type == GameServerMessageType::kKillGame)
        {
          GameServerKillGame msg;
          if (StormReflParseJson(msg, data_start) == false)
          {
            ParseError();
            return;
          }

          m_KillGameCallback(msg.m_GameId);
        }
        else if (type == GameServerMessageType::kResetGame)
        {
          GameServerResetGame msg;
          if (StormReflParseJson(msg, data_start) == false)
          {
            ParseError();
            return;
          }

          m_ResetGameCallback(msg.m_GameId);
        }
        else if (type == GameServerMessageType::kChangeCreator)
        {
          GameServerChangeCreator msg;
          if (StormReflParseJson(msg, data_start) == false)
          {
            ParseError();
            return;
          }

          m_ChangeCreatorCallback(msg.m_GameId, msg.m_Creator);
        }
        break;
      }
    case LobbyServerConnectionState::kRelocating:
    {
      if (type == GameServerMessageType::kRelocated)
      {
        for (auto & packet : m_PendingMessages)
        {
          m_WebSocket.SendString(packet);
        }

        m_PendingMessages.clear();
        m_State = LobbyServerConnectionState::kConnected;
      }
      else if (type == GameServerMessageType::kRelocate)
      {
        GameServerRelocate msg;
        if (StormReflParseJson(msg, data_start) == false)
        {
          ParseError();
          return;
        }

        Relocate(msg);
      }
    }
    break;
    }
  }
}

bool LobbyServerConnection::IsConnected()
{
  return m_WebSocket.IsConnected();
}

bool LobbyServerConnection::WantsRedownload()
{
  return m_WantsRedownload;
}

void LobbyServerConnection::SetTeamSwitchCallback(LobbyTeamSwitchCallback callback)
{
  m_TeamSwitchCallback = callback;
}

void LobbyServerConnection::SetDisconnectCallback(LobbyDisconnectCallback callback)
{
  m_DisconnectCallback = callback;
}

void LobbyServerConnection::SetResetGameCallback(LobbyResetGameCallback callback)
{
  m_ResetGameCallback = callback;
}

void LobbyServerConnection::SetKillGameCallback(LobbyKillGameCallback callback)
{
  m_KillGameCallback = callback;
}

void LobbyServerConnection::SetChangeCreatorCallback(LobbyChangeCreatorCallback callback)
{
  m_ChangeCreatorCallback = callback;
}

int LobbyServerConnection::RequestValidation(uint64_t user_token, LobbyValidationCallback && callback)
{
  m_Validations.emplace(std::make_pair(m_NextValidationId, std::move(callback)));

  GameServerAuthenticateUser req;
  req.m_ResponseId = m_NextValidationId;
  req.m_UserToken = user_token;

  SendMessage(req);

  return m_NextValidationId++;
}

void LobbyServerConnection::CancelValidation(int request_id)
{
  m_Validations.erase(request_id);
}

void LobbyServerConnection::RequestTeamSwitch(uint64_t user_id, uint64_t game_id, int team)
{
  GameServerRequestTeamSwitch req;
  req.m_UserId = user_id;
  req.m_GameId = game_id;
  req.m_Team = team;
  req.m_Force = false;

  SendMessage(req);

#ifdef _DEBUG
  m_TeamSwitchCallback(user_id, game_id, team);
#endif
}

void LobbyServerConnection::RequestRanomizeTeams(uint64_t game_id)
{
  GameServerRandomizeTeams req;
  req.m_GameId = game_id;
  SendMessage(req);
}

void LobbyServerConnection::UpdateScore(uint64_t game_id, const std::string & score)
{
  GameServerScore req;
  req.m_GameId = game_id;
  req.m_Score = score;

  SendMessage(req);
}

void LobbyServerConnection::NotifyPlayerLeft(uint64_t user_id, uint64_t game_id)
{
  GameServerUserDisconnected msg;
  msg.m_UserId = user_id;
  msg.m_GameId = game_id;

  SendMessage(msg);
}

void LobbyServerConnection::SendStats(uint64_t account_id, SimStats & stats, const GameInstanceData & settings)
{
  GameServerStats msg = {};
  msg.m_AccountId = account_id;
  
  StormReflAggregate(msg.m_Stats, stats);
  msg.m_Settings = settings;

  SendMessage(msg);
}

void LobbyServerConnection::SendGameComplete(uint64_t game_id, bool complete, const std::vector<std::pair<uint64_t, SimStats>> & players, const std::vector<int> & team_scores)
{
  GameServerGameResult msg = {};
  msg.m_GameCompleted = complete;
  msg.m_GameId = game_id;

  for (auto & player : players)
  {
    GameServerResultPlayer player_info;
    player_info.m_AccountId = player.first;
    StormReflAggregate(player_info.m_Stats, player.second);

    msg.m_ConnectedUsers.push_back(player_info);
  }

  for (auto & score : team_scores)
  {
    msg.m_TeamScores.push_back(score);
  }

  SendMessage(msg);
}

template <typename T>
void LobbyServerConnection::SendMessage(const T & t)
{
  if (m_State == LobbyServerConnectionState::kDisconnected)
  {
    return;
  }

  std::string packet_data = StormReflGetEnumAsString(T::Type);
  packet_data += ' ';
  StormReflEncodeJson(t, packet_data);

  if (m_State == LobbyServerConnectionState::kRelocating)
  {
    m_PendingMessages.emplace_back(std::move(packet_data));
  }
  else
  {
    m_WebSocket.SendString(packet_data);
  }
}

void LobbyServerConnection::Relocate(GameServerRelocate & msg)
{
  m_RelocationToken = msg.m_RelocationKey;

  if (m_WebSocket.Connect(msg.m_HostAddr.c_str(), msg.m_Port, "/", "uniball"))
  {
    GameServerIdentifyRelocate msg = { m_RelocationToken };
    SendMessage(msg);

    m_State = LobbyServerConnectionState::kRelocating;
  }
  else
  {
    m_State = LobbyServerConnectionState::kDisconnected;
  }
}

void LobbyServerConnection::ParseError()
{
  m_WebSocket.Close();
  m_State = LobbyServerConnectionState::kDisconnected;
}
