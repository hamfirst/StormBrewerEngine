
#include <StormRefl/StormReflJsonStd.h>
#include <StormRefl/StormReflMetaEnum.h>

#include "Foundation/Common.h"
#include "Foundation/Buffer/BufferUtil.h"

#include "ProjectSettings/ProjectName.h"
#include "ProjectSettings/ProjectVersion.h"
#include "ProjectSettings/ProjectPorts.h"

#include "Game/SimulationEvents/GameSimulationStats.refl.meta.h"

#include "Lobby/GameServerMessages.refl.meta.h"

#include "LobbyServerConnection/LobbyServerConnection.h"



LobbyServerConnection::LobbyServerConnection(const GameServerLobbySettings & lobby_settings, const GameServerInfo & server_info) :
  m_State(LobbyServerConnectionState::kDisconnected),
  m_LastPingTime(time(nullptr)),
  m_NextValidationId(1),
  m_LobbySettings(lobby_settings),
  m_ServerInfo(server_info)
{
  
}

void LobbyServerConnection::Connect()
{
  if (m_State != LobbyServerConnectionState::kDisconnected)
  {
    return;
  }
  
  m_State = LobbyServerConnectionState::kConnecting;
  m_WebSocket.StartConnect(m_LobbySettings.m_LobbyServerIp.c_str(), m_LobbySettings.m_LobbyServerPort, "/", "stormbrewers.com", kProjectName);
}

void LobbyServerConnection::Update()
{
  if (m_State == LobbyServerConnectionState::kDisconnected)
  {
    Connect();
    return;
  }

  if(m_State == LobbyServerConnectionState::kConnecting)
  {
    if(m_WebSocket.IsConnected())
    {
      m_State = LobbyServerConnectionState::kAuthenticating;

      GameServerIdentifyNew msg = {};
      msg.m_Version = kProjectVersion;
      SendMessage(msg);
    }
    else if(m_WebSocket.IsConnecting() == false)
    {
      m_State = LobbyServerConnectionState::kDisconnected;
      return;
    }
    else
    {
      return;
    }
  }

  if(m_State == LobbyServerConnectionState::kRelocateConnecting)
  {
    if(m_WebSocket.IsConnected())
    {
      m_State = LobbyServerConnectionState::kRelocating;

      GameServerIdentifyRelocate msg = { m_RelocationToken };
      SendMessage(msg);
    }
    else if(m_WebSocket.IsConnecting() == false)
    {
      m_State = LobbyServerConnectionState::kDisconnected;
      return;
    }
    else
    {
      return;
    }
  }

  auto cur_time = time(nullptr);
  if (cur_time - m_LastPingTime > 10)
  {
    m_LastPingTime = cur_time;

    GameServerPing ping;
    SendMessage(ping);
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
        GameServerAuthenticateRequest req;
        if (type != GameServerMessageType::kAuthRequest || StormReflParseJson(req, data_start) == false)
        {
          ParseError();
          return;
        }

        uint64_t challenge_response = crc64(std::to_string(req.m_Challenge)) ^ kGameServerChallengePad;
        GameServerAuthenticateResponse resp;
        resp.m_Challenge = challenge_response;
        resp.m_ServerInfo = m_ServerInfo;

        SendMessage(resp);

        m_State = LobbyServerConnectionState::kConnected;
      }
      break;
    case LobbyServerConnectionState::kConnected:
      {
        if (type == GameServerMessageType::kAuthUserSuccess)
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


          val->second({});
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
        else if (type == GameServerMessageType::kCreateGame)
        {
          GameServerCreateGame msg;
          if (StormReflParseJson(msg, data_start) == false)
          {
            ParseError();
            return;
          }

          m_CreateGameCallback(msg);
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

void LobbyServerConnection::SetCreateGameCallback(LobbyCreateGameCallback callback)
{
  m_CreateGameCallback = callback;
}

void LobbyServerConnection::SetKillGameCallback(LobbyKillGameCallback callback)
{
  m_KillGameCallback = callback;
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

void LobbyServerConnection::SetChangeCreatorCallback(LobbyChangeCreatorCallback callback)
{
  m_ChangeCreatorCallback = callback;
}

int LobbyServerConnection::RequestValidation(const JoinServerMessage & join_info, LobbyValidationCallback && callback)
{
  m_Validations.emplace(std::make_pair(m_NextValidationId, std::move(callback)));

  GameServerAuthenticateUser req;
  req.m_ResponseId = m_NextValidationId;
  req.m_GameId = join_info.m_GameId;
  req.m_UserId = join_info.m_UserId;
  req.m_JoinToken = join_info.m_JoinToken;

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

void LobbyServerConnection::RequestRandomizeTeams(uint64_t game_id)
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

void LobbyServerConnection::NotifyAcceptingPlayers(uint64_t game_id, bool accepting)
{
  GameServerAcceptingPlayers msg;
  msg.m_GameId = game_id;
  msg.m_AcceptingPlayers = accepting;

  SendMessage(msg);
}

void LobbyServerConnection::SendStats(uint64_t account_id, GameSimulationStats & stats, const GameInitSettings & settings)
{
  GameServerStats msg = {};
  msg.m_AccountId = account_id;
  
  StormReflAggregate(msg.m_Stats, stats);

  SendMessage(msg);
}

void LobbyServerConnection::SendGameComplete(uint64_t game_id, bool complete, const std::vector<std::pair<uint64_t, GameSimulationStats>> & players, const std::vector<int> & team_scores)
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
  m_WebSocket.StartConnect(msg.m_HostAddr.c_str(), msg.m_Port, "/", kProjectName);
}

void LobbyServerConnection::ParseError()
{
  m_WebSocket.Close();
  m_State = LobbyServerConnectionState::kDisconnected;
}
