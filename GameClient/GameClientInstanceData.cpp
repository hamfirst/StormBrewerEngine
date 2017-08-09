
#include "GameClient/GameClientInstanceData.h"
#include "GameClient/GameClientInstanceContainer.h"
#include "GameClient/GameContainer.h"



GameClientInstanceData::GameClientInstanceData(GameContainer & game_container, GameController & game_controller, GameClientController & client_controller,
                                               GameFullState & net_state, ClientLocalData & local_data, GameStage & stage,
                                               GameSharedInstanceResources & shared_resources, GameClientInstanceResources & client_resources, GameClientEventSender & event_sender) :
  m_GameContainer(game_container),
  m_GameController(game_controller),
  m_ClientController(client_controller),
  m_NetState(net_state), 
  m_LocalData(local_data),
  m_Stage(stage),
  m_SharedInstanceResources(shared_resources), 
  m_ClientInstanceResources(client_resources),
  m_EventSender(event_sender)
{

}

GameFullState & GameClientInstanceData::GetFullState()
{
  return m_NetState;
}

GameInstanceData & GameClientInstanceData::GetGameState()
{
  return m_NetState.m_GlobalData;
}

ServerObjectManager & GameClientInstanceData::GetServerObjectManager()
{
  return m_NetState.m_ServerObjectManager;
}

ClientLocalData & GameClientInstanceData::GetLocalData()
{
  return m_LocalData;
}

GameStage & GameClientInstanceData::GetStage()
{
  return m_Stage;
}

GameSharedInstanceResources & GameClientInstanceData::GetSharedInstanceResources()
{
  return m_SharedInstanceResources;
}

GameClientInstanceResources & GameClientInstanceData::GetClientInstanceResources()
{
  return m_ClientInstanceResources;
}

GameClientEventSender & GameClientInstanceData::GetEventSender()
{
  return m_EventSender;
}

GameLogicContainer GameClientInstanceData::GetLogicContainer()
{
  return GameLogicContainer(
    m_GameController,
    m_NetState.m_GlobalData,
    m_NetState.m_ServerObjectManager,
    m_ClientController,
    m_ClientController,
    m_GameContainer.GetSharedGlobalResources(),
    m_GameContainer.GetInstanceData()->GetSharedInstanceResources(),
    m_Stage,
    false, m_SendTimer);
}
