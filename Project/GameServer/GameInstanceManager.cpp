
#include "GameServer/GameInstanceManager.h"
#include "GameServer/GameInstance.h"
#include "GameServer/GameServer.h"

#include "Game/GameMessages.refl.meta.h"
#include "Game/GameFullState.refl.meta.h"

GameInstanceManager::GameInstanceManager(GameServer & game_server, GameStageManager & stage_manager) :
  m_Server(game_server),
  m_StageManager(stage_manager)
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

bool GameInstanceManager::CreatePrivateGame(GameClientConnection * client, const CreatePrivateGameMessage & message)
{
  auto stage = m_StageManager.GetStage(message.m_JoinInfo.m_Settings);
  if (stage == nullptr)
  {
    return false;
  }

  auto game_id = GetRandomNumber64();
  auto private_room_id = GetNewPrivateRoomId();

  auto game_ptr = std::make_unique<GameInstance>(m_Server, game_id, private_room_id,
          message.m_JoinInfo.m_Settings, m_StageManager);
  auto result = m_Games.emplace(std::make_pair(game_id, std::move(game_ptr)));

  auto game = result.first->second.get();

  client->m_GameId = game_id;
  client->m_GameInstance = game;

  game->JoinPlayer(client, message.m_JoinInfo, true);
  return true;
}

bool GameInstanceManager::JoinPlayer(GameClientConnection * client, const JoinGameMessage & message)
{
  if (message.m_PrivateRoomId == 0)
  {
    for (auto & game : m_Games)
    {
      if (CanJoinGame(game.second.get(), message.m_JoinInfo.m_Settings))
      {
        if (game.second->JoinPlayer(client, message.m_JoinInfo, false))
        {
          client->m_GameId = game.first;
          client->m_GameInstance = game.second.get();
          return true;
        }
      }
    }

    auto stage = m_StageManager.GetStage(message.m_JoinInfo.m_Settings);
    if (stage == nullptr)
    {
      return false;
    }

    auto game_id = GetRandomNumber64();

    auto game_ptr = std::make_unique<GameInstance>(m_Server, game_id, 0, message.m_JoinInfo.m_Settings, m_StageManager);
    auto result = m_Games.emplace(std::make_pair(game_id, std::move(game_ptr)));

    auto game = result.first->second.get();

    client->m_GameId = game_id;
    client->m_GameInstance = game;

    game->JoinPlayer(client, message.m_JoinInfo, false);
    return true;
  }
  else
  {
    auto lookup_itr = m_PrivateRoomLookup.find(message.m_PrivateRoomId);
    if(lookup_itr == m_PrivateRoomLookup.end())
    {
      return false;
    }

    auto game_id = lookup_itr->second;

    auto itr = m_Games.find(game_id);
    if (itr == m_Games.end())
    {
      return false;
    }

    if (CanJoinGame(itr->second.get(), message.m_JoinInfo.m_Settings) == false)
    {
      return false;
    }

    itr->second->JoinPlayer(client, message.m_JoinInfo, false);
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

uint32_t GameInstanceManager::GetNewPrivateRoomId()
{
  while(true)
  {
    uint32_t room_id = 0;
    for (int index = 0; index < 4; ++index)
    {
      room_id <<= 8;

      auto rand = GetRandomNumber() % 36;
      if (rand < 26)
      {
        room_id |= (rand + 'A');
      }
      else
      {
        room_id |= (rand - 26 + '0');
      }
    }

    if(m_PrivateRoomLookup.find(room_id) == m_PrivateRoomLookup.end())
    {
      return room_id;
    }
  }
}
