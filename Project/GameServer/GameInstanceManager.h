#pragma once

#include "GameServer/GameClientConnection.h"
#include "GameServer/GameInstance.h"

#include "Game/GameMessages.refl.h"

class GameServer;
class GameStageManager;
class LobbyServerConnection;

struct GameServerAuthenticateUserSuccess;

class GameInstanceManager
{
public:
  GameInstanceManager(GameServer & game_server, GameStageManager & stage_manager, NullOptPtr<LobbyServerConnection> lobby_connection);

  void Update();

  void CreateGame(uint64_t game_id, const GameInitSettings & settings);
  void DestroyGame(uint64_t game_id);

  bool JoinPlayer(NotNullPtr<GameClientConnection> client, const GameServerAuthenticateUserSuccess & auth);
  void RemovePlayer(NotNullPtr<GameClientConnection> client);

  uint32_t GetNewPrivateRoomId();
private:
  GameServer & m_Server;
  GameStageManager & m_StageManager;
  NullOptPtr<LobbyServerConnection> m_LobbyConnection;

  std::map<uint64_t, std::unique_ptr<GameInstance>> m_Games;
  std::unordered_map<uint32_t, uint64_t> m_PrivateRoomLookup;
};
