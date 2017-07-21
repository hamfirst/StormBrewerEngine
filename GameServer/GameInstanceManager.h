#pragma once

#include "GameServer/GameClientConnection.h"
#include "GameServer/GameInstance.h"

#include "Game/GameMessages.refl.h"

class GameServer;
class GameStageManager;

class GameInstanceManager
{
public:
  GameInstanceManager(GameServer & game_server, GameStageManager & stage_manager, GameSharedGlobalResources & shared_global_resources);

  void Update();

  bool JoinPlayer(GameClientConnection * client, const JoinGameMessage & message);
  void RemovePlayer(GameClientConnection * client);

  bool CanJoinGame(GameInstance * instance, const GameInitSettings & settings) const;
private:
  GameServer & m_Server;
  GameStageManager & m_StageManager;
  GameSharedGlobalResources & m_SharedGlobalResources;
  std::map<uint64_t, std::unique_ptr<GameInstance>> m_Games;
};
