#pragma once

#include "Game/GameSharedInstanceResources.h"
#include "Game/GameFullState.refl.h"
#include "Game/GameLogicContainer.h"

#include "GameClient/GameClientInstanceResources.h"
#include "GameClient/GameClientEventSender.h"
#include "GameClient/GameClientController.refl.h"
#include "GameClient/GameServerEventResponder.h"

class GameClientInstanceData
{
public:
  GameClientInstanceData(GameContainer & game_container, GameController & game_controller, GameClientController & client_controller, 
    GameFullState & net_state, NotNullPtr<ClientLocalData> local_data, std::size_t num_local_clients, GameStage & stage,
    GameSharedInstanceResources & shared_resources, GameClientInstanceResources & client_resources, GameClientEventSender & event_sender, 
    GameServerEventResponder & server_event_responder, ServerObjectEventSystem & server_object_event_system);

  GameClientInstanceData(const GameClientInstanceData & rhs) = default;
  GameClientInstanceData(GameClientInstanceData && rhs) = default;

  GameClientInstanceData & operator =(const GameClientInstanceData & rhs) = default;
  GameClientInstanceData & operator =(GameClientInstanceData && rhs) = default;

  GameController & GetGameController();
  GameFullState & GetFullState();
  GameInstanceData & GetGameState();
  ServerObjectManager & GetServerObjectManager();

  ClientLocalData & GetLocalData(std::size_t player_index);
  std::size_t GetLocalDataCount();

  GameStage & GetStage();

  GameSharedInstanceResources & GetSharedInstanceResources();
  GameClientInstanceResources & GetClientInstanceResources();

  GameClientEventSender & GetEventSender();
  ServerObjectEventSystem & GetServerObjectEventSystem();

  GameLogicContainer GetLogicContainer();
private:

  GameContainer & m_GameContainer;
  GameController & m_GameController;
  GameClientController & m_ClientController;

  GameFullState & m_NetState;
  NotNullPtr<ClientLocalData> m_LocalData;
  std::size_t m_LocalDataCount;

  GameStage & m_Stage;

  GameSharedInstanceResources & m_SharedInstanceResources;
  GameClientInstanceResources & m_ClientInstanceResources;

  GameClientEventSender & m_EventSender;
  GameServerEventResponder & m_EventResponder;
  ServerObjectEventSystem & m_ServerObjectEventSystem;
  int m_SendTimer;
};
