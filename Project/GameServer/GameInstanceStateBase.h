#pragma once

#include "Foundation/Common.h"
#include "Foundation/Allocator/IdAllocator.h"

#include "ProjectSettings/ProjectNetworkSettings.h"

#include "GameShared/GameLogicContainer.h"
#include "GameShared/GameEventReconciler.h"

#include "GameServer/GameInstanceStateData.h"

#include "Game/NetworkEvents/GameMessages.refl.h"
#include "Game/NetworkEvents/GameNetworkData.refl.h"
#include "Game/SimulationEvents/GameSimulationEventCallbacks.h"
#include "Game/State/GameFullState.refl.h"
#include "Game/GameController/GameController.refl.h"
#include "Game/NetworkEvents/GameServerEventSender.h"

class GameClientConnection;
class GameServer;
class GameInstanceStateData;
struct GameInstanceStateDataPlayer;

class GameInstanceStateBase
{
public:

  GameInstanceStateBase(GameInstanceStateData & state_data) :
    m_StateData(state_data)
  {

  }

  virtual ~GameInstanceStateBase() {};

  virtual bool JoinPlayer(std::size_t client_index, const GameJoinInfo & join_game) { return false; }
  virtual void RemovePlayer(std::size_t client_index) {}

  virtual void Update() {}

  virtual void HandlePlayerLoaded(std::size_t client_index, const FinishLoadingMessage & msg) {}
  virtual void HandleTextChat(std::size_t client_index, const SendTextChatMessage & msg) {}

#ifdef NET_USE_LOADOUT
  virtual void HandleChangeLoadout(std::size_t client_index, const ChangeLoadoutMessage & msg) {};
#endif

#if NET_MODE == NET_MODE_GGPO

  virtual void UpdatePlayer(std::size_t client_index, GameGGPOClientUpdate & update_data) {};

#else

  virtual void UpdatePlayer(std::size_t client_index, ClientAuthData & update_data) {};
  virtual void HandleClientEvent(std::size_t client_index, std::size_t class_id, void * event_ptr) {};
#endif

protected:

  GameInstanceStateData & m_StateData;
};


