
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
  for (auto & game : m_Games)
  {
    game.second->Update();
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
        client->m_GameId = game.first;
        client->m_GameInstance = game.second.get();
        game.second->JoinPlayer(client, message);
        return true;
      }
    }

    auto stage = m_StageManager.GetStage(message.m_Settings);
    if (stage == nullptr)
    {
      return false;
    }

    auto game_id = GetRandomNumber64();
    auto result = m_Games.emplace(std::make_pair(game_id, std::make_unique<GameInstance>(m_Server, game_id, message.m_Settings, *stage, m_SharedGlobalResources)));

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

    if (client->GetGameInstance()->GetNumPlayers() == 0)
    {
      auto game_itr = m_Games.find(client->GetGameId());
      m_Games.erase(game_itr);
    }
  }
}

bool GameInstanceManager::CanJoinGame(GameInstance * instance, const GameInitSettings & settings) const
{
  return instance->GetNumPlayers() < kMaxPlayers;
}
