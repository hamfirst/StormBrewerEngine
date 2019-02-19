
#include <algorithm>

#include "HurricaneDDS/DDSRandom.h"
#include "HurricaneDDS/DDSChallenge.h"
#include "HurricaneDDS/DDSResponderCall.h"

#include "GameServerConnection.refl.meta.h"
#include "User.refl.meta.h"
#include "UserConnection.refl.meta.h"
#include "ServerList.refl.meta.h"
#include "Bot.refl.meta.h"

#include "GameServerMessages.refl.meta.h"
#include "UserConnectionMessages.refl.meta.h"

STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(GameLobbySettings);
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(GameLobbyPlayer);
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(GameLobby);
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(GameLobbyPrivateData);


GameServerConnection::GameServerConnection(DDSNodeInterface node_interface) :
  m_State(GameServerConnectionState::kWaitingForConnection),
  m_Interface(node_interface),
  m_Error(false)
{

}

void GameServerConnection::SetRemoteHost(std::string host)
{
  m_RemoteHost = host;
}

void GameServerConnection::GotMessage(GameServerMessageType cmd, std::string data)
{
  if (m_Error)
  {
    return;
  }

  switch (m_State)
  {
  case GameServerConnectionState::kWaitingForConnection:
    ForceDisconnect();
    break;
  case GameServerConnectionState::kAuthenticating:
    if (cmd == GameServerMessageType::kAuthResponse)
    {
      GameServerAuthenticateResponse resp;
      if (StormReflParseJson(resp, data.data()) == false)
      {
        ForceDisconnect();
        return;
      }
      
      if (resp.m_Challenge != m_ExpectedChallengeResponse)
      {
        ForceDisconnect();
        return;
      }

      m_ServerName = resp.m_Name;
      m_ServerLocation = resp.m_Location;
      m_ServerHost = resp.m_Host;

      if (m_ServerHost.length() == 0)
      {
        m_ServerHost = m_RemoteHost;
      }

      m_GamePort = resp.m_GamePort;
      m_PingPort = resp.m_PingPort;
      m_Maps = std::move(resp.m_Maps);
      
      m_State = GameServerConnectionState::kConnected;

      m_Interface.CallShared(&ServerList::AddServer, m_Interface.GetLocalKey(), m_ServerName, m_ServerLocation, m_ServerHost, m_PingPort);
    }
    else
    {
      ForceDisconnect();
    }
    break;
  case GameServerConnectionState::kConnected:
    if (cmd == GameServerMessageType::kAuthUser)
    {
      GameServerAuthenticateUser msg;
      if (StormReflParseJson(msg, data.data()) == false)
      {
        ForceDisconnect();
        return;
      }

      //GameServerAuthenticateUserSuccess resp;
      //resp.m_ResponseId = msg.m_ResponseId;
      //resp.m_Name = "Player";
      //resp.m_Team = 0;
      //resp.m_AdminLevel = 0;
      //resp.m_UserId = 0;
      //resp.m_AccountId = 0;
      //resp.m_GameId = 0;
      //resp.m_GameData.m_Map = "miniball";
      //resp.m_GameData.m_Name = "Game";
      //resp.m_GameData.m_PlayerLimit = 6;
      //resp.m_GameData.m_ScoreLimit = 10;
      //resp.m_GameData.m_TimeLimit = 0;
      //resp.m_Creator = "Player";
      //resp.m_RequiredPlayers = 0;

      //SendPacket(resp);

      GameLobby * game;
      GameLobbyPrivateData * game_private;
      GameLobbyPlayer * player;

      if (RedeemToken(msg.m_UserToken, game, game_private, player) == false)
      {
        GameServerAuthenticateUserFailure resp{ msg.m_ResponseId };
        SendPacket(resp);
        return;
      }

      GameServerAuthenticateUserSuccess resp;
      resp.m_ResponseId = msg.m_ResponseId;
      resp.m_Name = player->m_Name;
      resp.m_Squad = player->m_Squad;
      resp.m_Team = player->m_Team;
      resp.m_AdminLevel = player->m_AdminLevel;
      resp.m_Celebration = player->m_Celebration;
      resp.m_NewPlayer = player->m_NewPlayer;
      resp.m_UserId = player->m_UserRandomId;
      resp.m_AccountId = player->m_UserId;
      resp.m_GameId = game->m_GameRandomKey;
      resp.m_GameData = game->m_InstanceData;
      resp.m_Creator = game->m_Creator;
      resp.m_RequiredPlayers = (int)game_private->m_Reservations.size();

      SendPacket(resp);
    }
    else if (cmd == GameServerMessageType::kRequestTeamSwitch)
    {
      GameServerRequestTeamSwitch msg;
      if (StormReflParseJson(msg, data.data()) == false)
      {
        ForceDisconnect();
        return;
      }

      GameLobby * game;
      int game_id;

      GameLobbyPlayer * player;
      int player_index;

      if (FindPlayer(msg.m_GameId, msg.m_UserId, game, game_id, player, player_index) == false)
      {
        return;
      }

      UserSetTeam(game_id, player->m_UserId, msg.m_Team, msg.m_Force);
    }
    else if (cmd == GameServerMessageType::kRandomizeTeams)
    {
      GameServerRandomizeTeams msg;
      if (StormReflParseJson(msg, data.data()) == false)
      {
        ForceDisconnect();
        return;
      }

      for (auto game : m_GameList)
      {
        if (game.second.m_GameRandomKey == msg.m_GameId)
        {
          RandomizeTeams(game.first);
        }
      }
    }
    else if (cmd == GameServerMessageType::kUserDisconnected)
    {
      GameServerUserDisconnected msg;
      if (StormReflParseJson(msg, data.data()) == false)
      {
        ForceDisconnect();
        return;
      }

      GameLobby * game;
      int game_id;

      GameLobbyPlayer * player;
      int player_index;

      if (FindPlayer(msg.m_GameId, msg.m_UserId, game, game_id, player, player_index) == false)
      {
        return;
      }

      bool is_creator = game->m_Players[player_index].m_Name == game->m_Creator.ToString();
      m_Interface.Call(&User::NotifyLeftGame, player->m_UserId, game->m_GameRandomKey);

      game->m_Players.RemoveAt(player_index);

      if (game->m_Players.HighestIndex() == -1)
      {
        DestroyGame(game_id);
      }
      else
      {
        UpdateGamePlayerCount(game_id);

        if (is_creator)
        {
          PickNewCreator(game_id);
        }
      }
    }
    else if (cmd == GameServerMessageType::kGameScore)
    {
      GameServerScore msg;
      if (StormReflParseJson(msg, data.data()) == false)
      {
        ForceDisconnect();
        return;
      }

      for (auto game : m_GameList)
      {
        if (game.second.m_GameRandomKey == msg.m_GameId)
        {
          game.second.m_Score = msg.m_Score;
        }
      }
    }
    else if (cmd == GameServerMessageType::kUserStats)
    {
      GameServerStats msg;
      if (StormReflParseJson(msg, data.data()) == false)
      {
        ForceDisconnect();
        return;
      }

      m_Interface.Call(&User::UpdateStats, msg.m_AccountId, msg.m_Stats, msg.m_Settings);
    }
    else if (cmd == GameServerMessageType::kGameResult)
    {
      GameServerGameResult msg;
      if (StormReflParseJson(msg, data.data()) == false)
      {
        ForceDisconnect();
        return;
      }

      for (auto game : m_GameList)
      {
        if (game.second.m_GameRandomKey == msg.m_GameId)
        {
          auto & game_private = m_GamePrivateData[game.first];
          if (game_private.m_BotId != 0)
          {
            m_Interface.Call(&Bot::ProcessGameResult, game_private.m_BotId, msg, game_private.m_BotGameId);
          }

          break;
        }
      }
    }
    else
    {
      ForceDisconnect();
    }
  }
}

void GameServerConnection::RequestMapList(DDSKey endpoint_id)
{
  UserMapList map_list;
  map_list.c = "map_list";
  map_list.server_id = m_Interface.GetLocalKey();

  for (auto & map_info : m_Maps)
  {
    UserMapListMap map;
    map.map_name = map_info.m_Map;
    map.creator = map_info.m_Creator;
    map.game_type = map_info.m_GameMode;
    map.max_teams = map_info.m_MaxTeams;
    map.player_limit = map_info.m_MaxPlayers;
    map.time_limit = map_info.m_TimeLimit;
    map.score_limit = map_info.m_ScoreLimit;

    map_list.maps.emplace_back(map);
  }

  m_Interface.Call(&UserConnection::SendData, endpoint_id, StormReflEncodeJson(map_list));
}

void GameServerConnection::CreateGame(DDSKey creator_id, 
  DDSKey creator_endpoint_id, std::string creator_name, int creator_admin, int celebration, bool new_player, std::string squad,
  std::string password, GameInstanceData game_creation_data)
{
  GameServerMapData * map = nullptr;
  for (auto & map_data : m_Maps)
  {
    if (map_data.m_Map == game_creation_data.m_Map)
    {
      map = &map_data;
    }
  }

  if (map == nullptr)
  {
    return;
  }

  game_creation_data.m_PlayerLimit = std::min(game_creation_data.m_PlayerLimit, map->m_MaxPlayers);
  game_creation_data.m_PlayerLimit = std::max(game_creation_data.m_PlayerLimit, map->m_MaxTeams);
  game_creation_data.m_ScoreLimit = std::max(game_creation_data.m_ScoreLimit, 0);
  game_creation_data.m_TimeLimit = std::max(game_creation_data.m_TimeLimit, 0);

  GameLobby new_lobby;
  new_lobby.m_MaxTeams = map->m_MaxTeams;
  new_lobby.m_GameRandomKey = DDSGetRandomNumber64();
  new_lobby.m_Competive = false;
  StormReflCopy<GameInstanceData>(new_lobby.m_InstanceData, game_creation_data);
  auto & player = new_lobby.m_Players.EmplaceBack();

  player.m_Name = creator_name;
  player.m_Squad = squad;
  player.m_UserId = creator_id;
  player.m_UserRandomId = DDSGetRandomNumber64();
  player.m_Team = 0;
  player.m_EndpointId = creator_endpoint_id;
  player.m_AdminLevel = creator_admin;
  player.m_Celebration = celebration;
  player.m_NewPlayer = new_player;

  new_lobby.m_Creator = creator_name;
  new_lobby.m_Server = m_ServerName;

  m_GameList.EmplaceBack(new_lobby);
  int game_id = (int)m_GameList.HighestIndex();

  GameLobbyPrivateData private_data;
  private_data.m_Password = password;
  m_GamePrivateData.EmplaceAt(game_id, private_data);

  m_Interface.Call(&User::HandleGameJoinResponse, creator_id, m_Interface.GetLocalKey(), creator_endpoint_id, game_id, new_lobby.m_GameRandomKey, "", true);
  m_Interface.CallShared(&ServerList::AddGame, m_Interface.GetLocalKey(), game_id, game_creation_data.m_Name, 
    game_creation_data.m_Map, 1, game_creation_data.m_PlayerLimit, password.length() > 0);
}

void GameServerConnection::JoinUserToGame(int game_id, DDSKey user_key, DDSKey user_endpoint_id, 
  std::string user_name, int admin_level, int celebration, bool new_player, std::string squad, std::string password, bool observer, bool force)
{
  if (m_GameList.HasAt(game_id) == false)
  {
    m_Interface.Call(&User::HandleGameJoinResponse, user_key, m_Interface.GetLocalKey(), user_endpoint_id, game_id, 0, "", false);
    return;
  }

  auto & game = m_GameList[game_id];
  auto & game_private_data = m_GamePrivateData[game_id];

  if (password != game_private_data.m_Password && force == false)
  {
    m_Interface.Call(&UserConnection::SendRuntimeError, user_endpoint_id, "Invalid password");
    return;
  }

  for (auto player_info : game.m_Players)
  {
    if (player_info.second.m_UserId == user_key)
    {
      return;
    }
  }
  
  GameLobbyPlayer player;
  player.m_UserId = user_key;
  player.m_UserRandomId = DDSGetRandomNumber64();
  player.m_EndpointId = user_endpoint_id;
  player.m_Name = user_name;
  player.m_Squad = squad;
  player.m_AdminLevel = admin_level;
  player.m_Celebration = celebration;
  player.m_NewPlayer = new_player;

  int selected_team = 4;

  int in_game_count = {};
  int observer_count = {};
  int team_size[4] = {};
  int player_count = {};

  for (auto player : game.m_Players)
  {
    player_count++;

    auto player_team = player.second.m_Team;
    if (player_team < 4)
    {
      team_size[player_team]++;
      in_game_count++;
    }
    else
    {
      observer_count++;
    }
  }

  if (game_private_data.m_Reservations.size() == 0)
  {
    if (in_game_count < game.m_InstanceData.m_PlayerLimit && observer == false)
    {
      auto team_val = std::min_element(&team_size[0], &team_size[game.m_MaxTeams]);
      player.m_Team = (int)(team_val - &team_size[0]);
    }
    else
    {
      player.m_Team = 4;
    }
  }
  else
  {
    player.m_Team = 4;
    for (auto & reservation : game_private_data.m_Reservations)
    {
      if (reservation.first == user_key)
      {
        player.m_Team = reservation.second;
      }
    }
  }

  if (player.m_Team < 4)
  {
    in_game_count++;
  }
  else
  {
    observer_count++;
  }

  m_Interface.CallShared(&ServerList::UpdateGame, m_Interface.GetLocalKey(), game_id, in_game_count, observer_count);

  SendMessageToGame(game_id, user_name + " has joined the game");

  game.m_Players.EmplaceBack(player);
  m_Interface.Call(&User::HandleGameJoinResponse, user_key, m_Interface.GetLocalKey(), user_endpoint_id, game_id, game.m_GameRandomKey, "", true);

  if (game.m_Started)
  {
    SendLaunchGame(game_id, user_key, user_endpoint_id);
  }
}

void GameServerConnection::UserSwitchTeams(int game_id, DDSKey user_key)
{
  if (m_GameList.HasAt(game_id) == false)
  {
    return;
  }

  auto & game = m_GameList[game_id];
  if (game.m_Competive)
  {
    return;
  }

  GameLobbyPlayer * player = nullptr;
  for (auto player_info : game.m_Players)
  {
    if (player_info.second.m_UserId == user_key)
    {
      player = &player_info.second;
      break;
    }
  }

  if (player == nullptr)
  {
    return;
  }

  int new_team;

  if (player->m_Team == 4)
  {
    new_team = 0;
  }
  else if (player->m_Team + 1 == game.m_MaxTeams)
  {
    new_team = 4;
  }
  else
  {
    new_team = player->m_Team + 1;
  }

  UserSetTeam(game_id, user_key, new_team, false);
}

void GameServerConnection::UserSetTeam(int game_id, DDSKey user_key, int team, bool force)
{
  if (m_GameList.HasAt(game_id) == false)
  {
    return;
  }

  auto & game = m_GameList[game_id];
  if (game.m_Competive)
  {
    return;
  }

  GameLobbyPlayer * player = nullptr;
  for (auto player_info : game.m_Players)
  {
    if (player_info.second.m_UserId == user_key)
    {
      player = &player_info.second;
      break;
    }
  }

  if (player == nullptr)
  {
    return;
  }

  if (player->m_Team == team)
  {
    return;
  }

  int team_size[4] = {};
  int in_game_count = {};
  int observer_count = {};

  for (auto player : game.m_Players)
  {
    auto player_team = player.second.m_Team;
    if (player_team < 4)
    {
      team_size[player_team]++;
      in_game_count++;
    }
    else
    {
      observer_count++;
    }
  }

  if (player->m_Team == 4)
  {
    if (in_game_count >= game.m_InstanceData.m_PlayerLimit && force == false)
    {
      if (game.m_Started == false)
      {
        m_Interface.Call(&UserConnection::SendRuntimeError, player->m_EndpointId, "Too many players in game");
      }

      return;
    }

    in_game_count++;
  }
  else if (team == 4)
  {
    in_game_count--;
    observer_count++;
  }

  if (player->m_Team == 4)
  {
    observer_count--;
  }

  player->m_Team = team;
  if (game.m_Started)
  { 
    GameServerTeamSwitch msg{ player->m_UserRandomId, game.m_GameRandomKey, team };
    SendPacket(msg);
  }

  m_Interface.CallShared(&ServerList::UpdateGame, m_Interface.GetLocalKey(), game_id, in_game_count, observer_count);
}

void GameServerConnection::UserLeaveGame(int game_id, DDSKey user_key)
{
  if (m_GameList.HasAt(game_id) == false)
  {
    return;
  }

  auto & game = m_GameList[game_id];
  for (auto player : game.m_Players)
  {
    if (player.second.m_UserId == user_key)
    {
      bool is_creator = game.m_Players[player.first].m_Name == game.m_Creator.ToString();
      SendMessageToGame(game_id, game.m_Players[player.first].m_Name + " has left the game");

      game.m_Players.RemoveAt(player.first);

      if (game.m_Started)
      {
        GameServerForceUserDisconnect rem_user;
        rem_user.m_UserId = player.second.m_UserRandomId;
        rem_user.m_GameId = game.m_GameRandomKey;

        SendPacket(rem_user);
      }

      if (game.m_Players.HighestIndex() == -1)
      {
        DestroyGame(game_id);
      }
      else
      {
        UpdateGamePlayerCount(game_id);

        if (is_creator)
        {
          PickNewCreator(game_id);
        }
      }

      return;
    }
  }
}

void GameServerConnection::RandomizeTeams(int game_id)
{
  if (m_GameList.HasAt(game_id) == false)
  {
    return;
  }

  auto & game = m_GameList[game_id];
  if (game.m_Competive)
  {
    return;
  }

  std::vector<int> player_indices;
  for (auto elem : game.m_Players)
  {
    if (elem.second.m_Team != 4)
    {
      player_indices.push_back(elem.first);
    }
  }

  std::random_shuffle(player_indices.begin(), player_indices.end());
  for (std::size_t index = 0, size = player_indices.size(); index < size; index++)
  {
    auto team = (index % game.m_MaxTeams);
    auto & player = game.m_Players[player_indices[index]];

    player.m_Team = team;

    if (game.m_Started)
    {
      GameServerTeamSwitch msg{ player.m_UserRandomId, game.m_GameRandomKey, (int)team };
      SendPacket(msg);
    }
  }

  SendPacket(GameServerResetGame{ game.m_GameRandomKey });
}

void GameServerConnection::KillGame(int game_id)
{
  if (m_GameList.HasAt(game_id) == false)
  {
    return;
  }

  auto & game = m_GameList[game_id];
  if (game.m_Started)
  {
    GameServerKillGame msg{ game.m_GameRandomKey };
    SendPacket(msg);
  }

  for (auto player : game.m_Players)
  {
    m_Interface.Call(&User::LeaveGame, player.second.m_UserId);
  }

  DestroyGame(game_id);
}

void GameServerConnection::CreateBotGame(DDSKey bot_id, DDSKey bot_game_id, GameInstanceData game_creation_data, std::vector<std::tuple<DDSKey, DDSKey, int>> player_info)
{
  GameServerMapData * map = nullptr;
  for (auto & map_data : m_Maps)
  {
    if (map_data.m_Map == game_creation_data.m_Map)
    {
      map = &map_data;
    }
  }

  if (map == nullptr)
  {
    return;
  }

  game_creation_data.m_PlayerLimit = std::max(game_creation_data.m_PlayerLimit, map->m_MaxTeams);
  game_creation_data.m_ScoreLimit = std::max(game_creation_data.m_ScoreLimit, 0);
  game_creation_data.m_TimeLimit = std::max(game_creation_data.m_TimeLimit, 0);

  GameLobby new_lobby;
  new_lobby.m_MaxTeams = map->m_MaxTeams;
  new_lobby.m_GameRandomKey = DDSGetRandomNumber64();
  new_lobby.m_Started = true;
  new_lobby.m_Competive = true;
  StormReflCopy<GameInstanceData>(new_lobby.m_InstanceData, game_creation_data);

  new_lobby.m_Server = m_ServerName;

  m_GameList.EmplaceBack(new_lobby);
  int game_id = (int)m_GameList.HighestIndex();

  GameLobbyPrivateData private_data;
  private_data.m_BotId = bot_id;
  private_data.m_BotGameId = bot_game_id;

  for (auto & player : player_info)
  {
    DDSKey user_id = std::get<0>(player);
    int team = std::get<2>(player);
    private_data.m_Reservations.push_back(std::make_pair(user_id, team));
  }

  m_GamePrivateData.EmplaceAt(game_id, private_data);

  m_Interface.CallShared(&ServerList::AddGame, m_Interface.GetLocalKey(), game_id, game_creation_data.m_Name,
    game_creation_data.m_Map, 1, game_creation_data.m_PlayerLimit, false);

  m_Interface.CallShared(&ServerList::StartGame, m_Interface.GetLocalKey(), game_id);

  for (auto & player : player_info)
  {
    DDSKey user_id = std::get<0>(player);
    DDSKey endpoint_id = std::get<1>(player);
    int team = std::get<2>(player);

    m_Interface.Call(&User::JoinGame, user_id, m_Interface.GetLocalKey(), endpoint_id, game_id, "", false);
  }

  m_Interface.CreateTimer(std::chrono::seconds(10), m_Interface.GetLocalKey(), &GameServerConnection::ExpireGame, game_id);
}

void GameServerConnection::SendChatToGame(int game_id, DDSKey user_id, std::string chat)
{
  if (chat.length() == 0)
  {
    return;
  }

  if (m_GameList.HasAt(game_id) == false)
  {
    return;
  }

  auto & game = m_GameList[game_id];
  if (game.m_Started)
  {
    return;
  }

  GameLobbyPlayer * player = nullptr;
  for (auto player_info : game.m_Players)
  {
    if (player_info.second.m_UserId == user_id)
    {
      player = &player_info.second;
      break;
    }
  }

  if (player == nullptr)
  {
    return;
  }

  if (chat[0] == '/')
  {
    if (chat.substr(0, 6) == "/boot ")
    {
      auto name = chat.substr(6);
      std::transform(name.begin(), name.end(), name.begin(), tolower);

      for (auto player_info : game.m_Players)
      {
        auto player_name = player_info.second.m_Name;
        std::transform(player_name.begin(), player_name.end(), player_name.begin(), tolower);

        if (player_name == name)
        {
          if (player_info.second.m_AdminLevel == 0)
          {
            m_Interface.Call(&User::LeaveGame, player_info.second.m_UserId);
            SendMessageToGame(game_id, player_info.second.m_Name + " has been removed from the game");
          }
          else
          {
            m_Interface.Call(&User::SendNotification, user_id, "You cannot boot an admin from the game");
          }
          break;
        }
      }
    }

    return;
  }

  std::string message = StormReflEncodeJson(UserChatMessageGame{ "game_chat", player->m_Name, chat });

  for (auto player_info : game.m_Players)
  {
    m_Interface.Call(&UserConnection::SendData, player_info.second.m_EndpointId, message);
  }
}

void GameServerConnection::SendMessageToGame(int game_id, std::string chat)
{
  if (m_GameList.HasAt(game_id) == false)
  {
    return;
  }

  auto & game = m_GameList[game_id];
  if (game.m_Started)
  {
    return;
  }

  std::string message = StormReflEncodeJson(UserServerMessageGame{ "game_msg", chat });

  for (auto player_info : game.m_Players)
  {
    m_Interface.Call(&UserConnection::SendData, player_info.second.m_EndpointId, message);
  }
}

void GameServerConnection::StartGame(int game_id, DDSKey game_random_id, std::string creator_name)
{
  if (m_GameList.HasAt(game_id) == false)
  {
    return;
  }

  auto & game = m_GameList[game_id];
  if (game.m_GameRandomKey != game_random_id || game.m_Started)
  {
    return;
  }

  if (game.m_Creator.ToString() != creator_name)
  {
    return;
  }

  game.m_Started = true;
  
  for (auto player : game.m_Players)
  {
    SendLaunchGame(game_id, player.second.m_UserId, player.second.m_EndpointId);
  }

  m_Interface.CallShared(&ServerList::StartGame, m_Interface.GetLocalKey(), game_id);
}

void GameServerConnection::SendLaunchGame(int game_id, DDSKey user_id, DDSKey endpoint_id)
{
  if (m_GameList.HasAt(game_id) == false)
  {
    return;
  }

  DDSKey token = DDSGetRandomNumber();
  m_Interface.CreateTimer(std::chrono::seconds(15), m_Interface.GetLocalKey(), &GameServerConnection::ExpireToken, token);

  m_Interface.Call(&UserConnection::SendLaunchGame, endpoint_id, m_RemoteHost, m_GamePort, token);
  m_Tokens.emplace(std::make_pair(token, std::make_tuple(game_id, user_id, endpoint_id, m_GameList[game_id].m_GameRandomKey)));
}

void GameServerConnection::ExpireToken(DDSKey token)
{
  GameLobby * game;
  GameLobbyPrivateData * game_private;
  GameLobbyPlayer * player;

  if (RedeemToken(token, game, game_private, player) == false)
  {
    return;
  }

  m_Interface.Call(&User::LeaveGame, player->m_UserId);
}

void GameServerConnection::ExpireGame(int game_id)
{
  if (m_GameList.HasAt(game_id))
  {
    if (m_GameList[game_id].m_Players.HighestIndex() == -1)
    {
      DestroyGame(game_id);
    }
  }
}

void GameServerConnection::SendHangUp()
{
  SendPacket(GameServerRedownload{});
}

void GameServerConnection::ConnectToEndpoint(DDSConnectionId connection_id)
{
  m_ConnectionId = connection_id;

  if (m_State == GameServerConnectionState::kWaitingForConnection)
  {
    m_State = GameServerConnectionState::kAuthenticating;

    uint64_t challenge = DDSGetRandomNumber64();
    m_ExpectedChallengeResponse = DDSCalculateChallengeResponse(challenge) ^ kGameServerChallengePad;

    GameServerAuthenticateRequest req;
    req.m_Challenge = challenge;
    SendPacket(req);
  }

  for (auto & data : m_PendingMessages)
  {
    m_Interface.SendDataToLocalConnection(*m_ConnectionId, data);
  }

  m_PendingMessages.clear();
}

void GameServerConnection::PreDestroy()
{
  if (m_State == GameServerConnectionState::kConnected)
  {
    m_Interface.CallShared(&ServerList::RemoveServer, m_Interface.GetLocalKey());
  }
}

void GameServerConnection::PreMoveObject()
{
  DDSLog::LogVerbose("Moving server connection to new server %llu", m_Interface.GetLocalKey());

  auto node_info = m_Interface.GetNodeInfo(m_Interface.GetLocalKey());
  if (node_info)
  {
    std::string ip_addr = GetNodeAddrAsString(node_info->m_Addr);
    GameServerRelocate relocate{ ip_addr, node_info->m_EndpointPorts[1], m_Interface.GetLocalKey() };
    SendPacket(relocate);
    m_Relocating = true;
  }
  else
  {
    ForceDisconnect();
  }

  m_ConnectionId = {};
}

bool GameServerConnection::RedeemToken(DDSKey token, GameLobby *& game, GameLobbyPrivateData *& game_private, GameLobbyPlayer *& player)
{
  auto token_itr = m_Tokens.find(token);
  if (token_itr == m_Tokens.end())
  {
    return false;
  }

  auto game_id = std::get<0>(token_itr->second);
  auto user_id = std::get<1>(token_itr->second);
  auto endpoint_id = std::get<2>(token_itr->second);
  auto game_key = std::get<3>(token_itr->second);

  m_Tokens.erase(token_itr);

  if (m_GameList.HasAt(game_id) == false)
  {
    return false;
  }

  game = &m_GameList[game_id];
  game_private = &m_GamePrivateData[game_id];
  if (game->m_GameRandomKey != game_key)
  {
    return false;
  }

  auto player_itr = game->m_Players.end();
  for (auto itr = game->m_Players.begin(), end = player_itr; itr != end; ++itr)
  {
    if (itr->second.m_UserId == user_id && itr->second.m_EndpointId == endpoint_id)
    {
      player_itr = itr;
      break;
    }
  }

  if (player_itr == game->m_Players.end())
  {
    return false;
  }

  player = &player_itr->second;
  return true;
}

bool GameServerConnection::FindPlayer(DDSKey game_random_id, DDSKey user_random_id, GameLobby *& game, int & game_id, GameLobbyPlayer *& player, int & player_index)
{
  for (auto itr = m_GameList.begin(), end = m_GameList.end(); itr != end; ++itr)
  {
    if (itr->second.m_GameRandomKey == game_random_id)
    {
      auto & game_elem = itr->second;
      for (auto player_itr = game_elem.m_Players.begin(), end = game_elem.m_Players.end(); player_itr != end; ++player_itr)
      {
        if (player_itr->second.m_UserRandomId == user_random_id)
        {
          game = &itr->second;
          game_id = itr->first;

          player = &player_itr->second;
          player_index = player_itr->first;
          return true;
        }
      }
    }
  }

  return false;
}

void GameServerConnection::UpdateGamePlayerCount(int game_id)
{
  auto & game = m_GameList[game_id];
  int in_game_count = 0;
  int observer_count = 0;
  for (auto player : game.m_Players)
  {
    if (player.second.m_Team < 4)
    {
      in_game_count++;
    }
    else
    {
      observer_count++;
    }
  }

  m_Interface.CallShared(&ServerList::UpdateGame, m_Interface.GetLocalKey(), game_id, in_game_count, observer_count);
}

void GameServerConnection::PickNewCreator(int game_id)
{
  auto & game = m_GameList[game_id];
  game.m_Creator = game.m_Players.begin()->second.m_Name;

  SendMessageToGame(game_id, game.m_Players.begin()->second.m_Name + " has control of the game");

  if (game.m_Started)
  {
    GameServerChangeCreator msg;
    msg.m_GameId = game.m_GameRandomKey;
    msg.m_Creator = game.m_Creator;

    SendPacket(msg);
  }
}

void GameServerConnection::DestroyGame(int game_id)
{
  m_GameList.RemoveAt(game_id);
  m_GamePrivateData.RemoveAt(game_id);
  m_Interface.CallShared(&ServerList::RemoveGame, m_Interface.GetLocalKey(), game_id);
}

template <typename T>
void GameServerConnection::SendPacket(const T & t)
{
  if (m_Error)
  {
    return;
  }

  std::string packet_data = StormReflGetEnumAsString(T::Type);
  packet_data += ' ';
  StormReflEncodeJson(t, packet_data);

  if (m_ConnectionId)
  {
    m_Interface.SendDataToLocalConnection(*m_ConnectionId, packet_data);
  }
  else
  {
    m_PendingMessages.emplace_back(packet_data);
  }
}

void GameServerConnection::ForceDisconnect()
{
  if (m_ConnectionId)
  {
    m_Interface.DisconnectLocalConnection(*m_ConnectionId);
  }

  m_Error = true;
}
