#pragma once

#include "Foundation/Common.h"
#include "Foundation/CircularBuffer/CircularBuffer.h"

#include "Game/GameNetworkSettings.h"
#include "Game/GameMessages.refl.h"
#include "Game/GameNetworkData.refl.h"
#include "Game/GameSimulationEventCallbacks.h"
#include "Game/GameFullState.refl.h"
#include "Game/GameController.refl.h"
#include "Game/GameLogicContainer.h"
#include "Game/GameSharedGlobalResources.h"
#include "Game/GameSharedInstanceResources.h"
#include "Game/GameEventReconciler.h"
#include "GameServer/GameInstanceStateData.h"

class GameClientConnection;
class GameServer;
class GameInstanceStateBase;

using GameSimulationActionList = std::vector<Delegate<void, GameLogicContainer &>>;

enum class GameInstanceState
{
  kWaitingForPlayers,
  kWaitingForLoad,
  kPlaying,
  kVictory,
};

class GameInstance
{
public:

  GameInstance(GameServer & server, uint64_t game_id, const GameInitSettings & settings, 
    GameSharedGlobalResources & global_resources, GameStageManager & stage_manager);

  ~GameInstance();

  void Update();
  void Reset();

  bool JoinPlayer(GameClientConnection * client, const JoinGameMessage & join_game);
  void RemovePlayer(GameClientConnection * client);

  void HandlePlayerReady(GameClientConnection * client, const ReadyMessage & ready);
  void HandlePlayerLoaded(GameClientConnection * client, const FinishLoadingMessage & finish_loading);

#if NET_MODE == NET_MODE_GGPO

  void UpdatePlayer(GameClientConnection * client, GameGGPOClientUpdate & update_data);

#else

  void UpdatePlayer(GameClientConnection * client, const ClientAuthData & auth_data);
  void HandleClientEvent(GameClientConnection * client, std::size_t class_id, void * event_ptr);

#endif

  std::size_t GetNumPlayers();
  std::vector<GameClientConnection *> GetConnectedPlayers() const;

protected:
  friend class GameInstanceStateData;

  std::size_t GetPlayerIndex(NotNullPtr<GameClientConnection> client);
  void SetNewState(std::unique_ptr<GameInstanceStateBase> && state);

private:

  GameServer & m_Server;
  uint64_t m_GameId;

  GameInstanceStateData m_StateData;
  std::unique_ptr<GameInstanceStateBase> m_State;
  std::unique_ptr<GameInstanceStateBase> m_NewState;

};


