#pragma once

#include "Foundation/Common.h"
#include "Foundation/Allocator/IdAllocator.h"

#include "Game/GameNetworkSettings.h"
#include "Game/GameMessages.refl.h"
#include "Game/GameNetworkData.refl.h"
#include "Game/GameSimulationEventCallbacks.h"
#include "Game/GameFullState.refl.h"
#include "Game/GameLogicContainer.h"
#include "Game/GameController.h"
#include "Game/GameServerEventSender.h"

#include "GameServer/GameEventReconciler.h"

#include "Foundation/CircularBuffer/CircularBuffer.h"

class GameClientConnection;
class GameServer;

using GameSimulationActionList = std::vector<Delegate<void, GameFullState &, const GameStage &>>;

class GameInstance : public GameSimulationEventCallbacks, public GameServerEventSender
{
public:

  GameInstance(GameServer & server, uint64_t game_id, const GameInitSettings & settings, const GameStage & stage);

  void Update();
  void Reset();

  bool JoinPlayer(GameClientConnection * client, const JoinGameMessage & join_game);
  void RemovePlayer(GameClientConnection * client);

  void HandlePlayerLoaded(GameClientConnection * client, const FinishLoadingMessage & finish_loading);

  void UpdatePlayer(GameClientConnection * client, const ClientAuthData & auth_data);
  void HandleClientEvent(GameClientConnection * client, std::size_t class_id, void * event_ptr);

  std::vector<int> GetTeamCounts();
  int GetRandomTeam();

  std::size_t GetNumPlayers();

  std::vector<GameClientConnection *> GetConnectedPlayers() const;

protected:

#ifdef NETWORK_ALLOW_REWINDING
  void Rewind(const ClientAuthData & auth_data, int player_index);
#endif

  virtual void SendGlobalEvent(std::size_t class_id, void * event_ptr) override;
  virtual void SendGlobalEvent(std::size_t class_id, void * event_ptr, std::size_t connection_id) override;
  virtual void SendEntityEvent(std::size_t class_id, void * event_ptr, ServerObjectHandle object_handle) override;
  virtual void SendEntityEvent(std::size_t class_id, void * event_ptr, std::size_t connection_id, ServerObjectHandle object_handle) override;

private:

  struct GamePlayer
  {
    GameClientConnection * m_Client;
    int m_PlayerIndex;
    uint64_t m_LoadToken;

#ifdef NETWORK_ALLOW_REWINDING
    int m_LastInputFrame;
    std::vector<ClientAuthData> m_PendingInput;
#endif

    bool m_Loaded;
  };

  GameServer & m_Server;
  uint64_t m_GameId;

  GameInitSettings m_InitSettings;
  GameController m_Controller;

#ifdef NETWORK_ALLOW_REWINDING
  struct SimHistory
  {
    GameFullState m_Sim;
    GameInput m_Input;
    GameSimulationActionList m_Actions;
  };

  CircularBuffer<SimHistory, kMaxRewindFrames> m_SimHistory;

  int m_ReconcileFrame;
  GameEventReconciler m_EventReconciler;
#else
  GameFullState m_GameState;
  GameInput m_Input;
#endif

  const GameStage & m_Stage;

  std::vector<GamePlayer> m_Players;
  IdAllocator m_PlayerIdAllocator;

  bool m_Completed;
  int m_SendTimer;
};


