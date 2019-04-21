
#include "GameServer/GameInstanceManager.h"
#include "GameServer/GameInstance.h"
#include "GameServer/GameServer.h"

#include "Game/GameMessages.refl.meta.h"
#include "Game/GameFullState.refl.meta.h"

GameInstanceManager::GameInstanceManager(GameServer & game_server, GameStageManager & stage_manager, NullOptPtr<LobbyServerConnection> lobby_connection) :
  m_Server(game_server),
  m_StageManager(stage_manager),
  m_LobbyConnection(lobby_connection)
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

bool GameInstanceManager::JoinPlayer(NotNullPtr<GameClientConnection> client, const GameServerAuthenticateUserSuccess & auth)
{
  return false;
}

void GameInstanceManager::RemovePlayer(GameClientConnection * client)
{
  if (client->GetGameInstance() != nullptr)
  {
    client->GetGameInstance()->RemovePlayer(client);
  }
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
