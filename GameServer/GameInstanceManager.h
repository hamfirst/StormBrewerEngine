#pragma once

#include "GameServer/GameClient.h"
#include "GameServer/GameInstance.h"

#include "Game/GameMessages.refl.h"

class GameServer;
class GameStageManager;

class GameInstanceManager
{
public:
  GameInstanceManager(GameServer & game_server, GameStageManager & stage_manager);

  void Update();

  bool JoinPlayer(GameClient * client, const JoinGameMessage & message);
  void RemovePlayer(GameClient * client);

  bool CanJoinGame(GameInstance * instance, const GameInitSettings & settings) const;
private:
  GameServer & m_Server;
  GameStageManager & m_StageManager;
  std::map<uint64_t, std::unique_ptr<GameInstance>> m_Games;
};
