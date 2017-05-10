#pragma once

#include "Foundation/Common.h"
#include "Foundation/Allocator/IdAllocator.h"

#include "Game/GameMessages.refl.h"
#include "Game/GameSimulation.refl.h"

#include "GameServer/GameEventReconciler.h"

#include "Foundation/CircularBuffer/CircularBuffer.h"

class GameClient;
class GameServer;

using GameSimulationActionList = std::vector<Delegate<void, GameSimulation &, GameStage &>>;

class GameInstance : public SimEventHandler
{
public:

  GameInstance(GameServer & server, uint64_t game_id, GameStage & stage);

  void Update();
  void Reset();

  bool JoinPlayer(GameClient * client, const JoinGameMessage & join_game);
  void RemovePlayer(GameClient * client);

  void UpdatePlayer(GameClient * client, const ClientAuthData & auth_data);

  std::vector<int> GetTeamCounts();
  int GetRandomTeam();

  std::size_t GetNumPlayers();

  std::vector<GameClient *> GetConnectedPlayers() const;

protected:

  void Rewind(const ClientAuthData & auth_data, int player_index);

private:

  struct GamePlayer
  {
    GameClient * m_Client;
    int m_PlayerIndex;

    int m_LastInputFrame;
    std::vector<ClientAuthData> m_PendingInput;
  };

  GameServer & m_Server;
  uint64_t m_GameId;

  struct SimHistory
  {
    GameSimulation m_Sim;
    GameInputState m_Input;
    GameSimulationActionList m_Actions;
  };

  CircularBuffer<SimHistory, kMaxRewindFrames> m_SimHistory;

  GameStage & m_Stage;

  int m_ReconcileFrame;
  GameEventReconciler m_EventReconciler;

  std::vector<GamePlayer> m_Players;
  IdAllocator m_PlayerIdAllocator;

  bool m_Completed;

  NetMessageSenderList<SimEventBase> m_EventSenderList;
  int m_SendTimer;
};


