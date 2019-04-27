
#include "GameServer/GameInstanceManager.h"
#include "GameServer/GameInstance.h"
#include "GameServer/GameServer.h"

#include "Game/GameMessages.refl.meta.h"
#include "Game/GameFullState.refl.meta.h"

#include "LobbyServerConnection/LobbyServerConnection.h"

GameInstanceManager::GameInstanceManager(GameServer & game_server, GameStageManager & stage_manager, NullOptPtr<LobbyServerConnection> lobby_connection) :
  m_Server(game_server),
  m_StageManager(stage_manager),
  m_LobbyConnection(lobby_connection)
{
  if(m_LobbyConnection)
  {
    m_LobbyConnection->SetCreateGameCallback([&](const GameServerCreateGame & msg)
    {
      CreateGame(msg.m_GameId, msg.m_Settings, msg.m_TeamInfo);
    });

    m_LobbyConnection->SetKillGameCallback([&](uint64_t game_id)
    {
      DestroyGame(game_id);
    });
  }
}

void GameInstanceManager::Update()
{
  std::vector<std::map<uint64_t, std::unique_ptr<GameInstance>>::iterator> dead_games;

  for (auto itr = m_Games.begin(), end = m_Games.end(); itr != end; ++itr)
  {
    itr->second->Update();
  }
}

void GameInstanceManager::CreateGame(uint64_t game_id, const GameInitSettings & settings, const GameInfoTeamSizes & team_info)
{
  auto game_instance = std::make_unique<GameInstance>(m_Server, game_id, settings, team_info, m_Server.m_StageManager);
  m_Games.emplace(std::make_pair(game_id, std::move(game_instance)));
}

void GameInstanceManager::DestroyGame(uint64_t game_id)
{
  auto itr = m_Games.find(game_id);
  if(itr == m_Games.end())
  {
    return;
  }

  auto players = itr->second->GetConnectedPlayers();
  for(auto & player : players)
  {
    player->ForceDisconnect();
  }

  m_Games.erase(itr);
}

bool GameInstanceManager::JoinPlayer(NotNullPtr<GameClientConnection> client, const GameServerAuthenticateUserSuccess & auth)
{
  auto itr = m_Games.find(auth.m_GameId);
  if(itr == m_Games.end())
  {
    return false;
  }

  GameJoinInfo join_info;
  join_info.m_UserName = auth.m_Name;
  join_info.m_UserId = auth.m_UserId;
  join_info.m_Team = auth.m_Team;
  if(itr->second->JoinPlayer(client, join_info, false))
  {
    client->m_GameInstance = itr->second.get();
    return true;
  }

  return false;
}

void GameInstanceManager::RemovePlayer(GameClientConnection * client)
{
  if (client->GetGameInstance() != nullptr)
  {
    client->GetGameInstance()->RemovePlayer(client);
  }
}

