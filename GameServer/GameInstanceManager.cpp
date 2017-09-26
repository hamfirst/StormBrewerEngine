
#include "GameServer/GameInstanceManager.h"
#include "GameServer/GameInstance.h"
#include "GameServer/GameServer.h"

#include "Game/GameMessages.refl.meta.h"
#include "Game/GameFullState.refl.meta.h"

GameInstanceManager::GameInstanceManager(GameServer & game_server, GameStageManager & stage_manager, GameSharedGlobalResources & shared_global_resources) :
  m_Server(game_server),
  m_StageManager(stage_manager),
  m_SharedGlobalResources(shared_global_resources)
{

}

void GameInstanceManager::Update()
{
  std::vector<std::map<uint64_t, std::unique_ptr<GameInstance>>::iterator> dead_games;

  for (auto itr = m_Games.begin(), end = m_Games.end(); itr != end; ++itr)
  {
    itr->second->Update();

    if (itr->second->GetNumPlayers() == 0)
    {
      dead_games.emplace_back(itr);
    }
  }

  for (auto & elem : dead_games)
  {
    m_Games.erase(elem);
  }
}

bool GameInstanceManager::JoinPlayer(GameClientConnection * client, const JoinGameMessage & message)
{
  if (message.m_GameId == 0)
  {
    for (auto & game : m_Games)
    {
      if (CanJoinGame(game.second.get(), message.m_Settings))
      {
        if (game.second->JoinPlayer(client, message))
        {
          client->m_GameId = game.first;
          client->m_GameInstance = game.second.get();
          return true;
        }
      }
    }

    auto stage = m_StageManager.GetStage(message.m_Settings);
    if (stage == nullptr)
    {
      return false;
    }

    auto game_id = GetRandomNumber64();
    auto result = m_Games.emplace(std::make_pair(game_id, std::make_unique<GameInstance>(m_Server, game_id, message.m_Settings, m_SharedGlobalResources, m_StageManager)));

    auto game = result.first->second.get();

    client->m_GameId = game_id;
    client->m_GameInstance = game;

    game->JoinPlayer(client, message);
    return true;
  }
  else
  {
    auto itr = m_Games.find(message.m_GameId);
    if (itr == m_Games.end())
    {
      return false;
    }

    if (CanJoinGame(itr->second.get(), message.m_Settings) == false)
    {
      return false;
    }

    itr->second->JoinPlayer(client, message);
    return true;
  }
}

void GameInstanceManager::RemovePlayer(GameClientConnection * client)
{
  if (client->GetGameInstance() != nullptr)
  {
    client->GetGameInstance()->RemovePlayer(client);
  }
}

bool GameInstanceManager::CanJoinGame(GameInstance * instance, const GameInitSettings & settings) const
{
  return instance->GetNumPlayers() < kMaxPlayers;
}
