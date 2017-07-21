#pragma once

#include "Game/GameSharedInstanceResources.h"
#include "Game/GameFullState.refl.h"

#include "GameClient/GameClientInstanceResources.h"
#include "GameClient/GameClientEventSender.h"

class GameClientInstanceData
{
public:
  GameClientInstanceData(GameFullState & net_state, ClientLocalData & local_data, GameStage & stage,
    GameSharedInstanceResources & shared_resources, GameClientInstanceResources & client_resources, GameClientEventSender & event_sender);

  GameClientInstanceData(const GameClientInstanceData & rhs) = default;
  GameClientInstanceData(GameClientInstanceData && rhs) = default;

  GameClientInstanceData & operator =(const GameClientInstanceData & rhs) = default;
  GameClientInstanceData & operator =(GameClientInstanceData && rhs) = default;

  GameFullState & GetFullState();
  GameInstanceData & GetGameState();
  ServerObjectManager & GetServerObjectManager();

  ClientLocalData & GetLocalData();

  GameStage & GetStage();

  GameSharedInstanceResources & GetSharedInstanceResources();
  GameClientInstanceResources & GetClientInstanceResources();

  GameClientEventSender & GetEventSender();
private:

  GameFullState & m_NetState;
  ClientLocalData & m_LocalData;

  GameStage & m_Stage;

  GameSharedInstanceResources & m_SharedInstanceResources;
  GameClientInstanceResources & m_ClientInstanceResources;

  GameClientEventSender & m_EventSender;
};
