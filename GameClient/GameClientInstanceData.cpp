
#include "GameClient/GameClientInstanceData.h"

GameClientInstanceData::GameClientInstanceData(GameFullState & net_state, ClientLocalData & local_data, GameStage & stage,
                                               GameSharedInstanceResources & shared_resources, GameClientInstanceResources & client_resources, GameClientEventSender & event_sender) :
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
