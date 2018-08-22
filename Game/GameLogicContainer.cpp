#include "Game/GameCommon.h"
#include "Game/GameLogicContainer.h"

GameLogicContainer::GameLogicContainer(
  GameController & game_controller,
  GameInstanceData & global_data,
  ServerObjectManager & object_manager,
  ServerObjectEventSystem & server_object_event_system,
  GameServerEventSender & server_event_sender,
  GameSimulationEventCallbacks & sim_event_sender,
  GameSharedGlobalResources & shared_global_resources,
  GameSharedInstanceResources & shared_instance_resources,
  GameLogicSystems & systems,
  const GameStage & stage,
  bool is_authority,
  int & send_timer) :
  m_GameController(game_controller),
  m_InstanceData(global_data),
  m_ObjectManager(object_manager),
  m_ObjectEventSystem(server_object_event_system),
  m_ServerEventSender(server_event_sender),
  m_SimEventSender(sim_event_sender),
  m_SharedGlobalResources(shared_global_resources),
  m_SharedInstanceResources(shared_instance_resources),
  m_Systems(systems),
  m_Stage(stage),
  m_IsAuthority(is_authority),
  m_SendTimer(send_timer)
{

}

GameController & GameLogicContainer::GetGameController() const
{
  return m_GameController;
}

GameInstanceData & GameLogicContainer::GetInstanceData() const
{
  return m_InstanceData;
}

ServerObjectManager & GameLogicContainer::GetObjectManager() const
{
  return m_ObjectManager;
}

ServerObjectEventSystem & GameLogicContainer::GetServerObjectEventSystem() const
{
  return m_ObjectEventSystem;
}

GameServerEventSender & GameLogicContainer::GetEventSender() const
{
  return m_ServerEventSender;
}

GameSimulationEventCallbacks & GameLogicContainer::GetSimEventCallbacks() const
{
  return m_SimEventSender;
}

GameSharedGlobalResources & GameLogicContainer::GetSharedGlobalResources() const
{
  return m_SharedGlobalResources;
}

GameSharedInstanceResources & GameLogicContainer::GetSharedInstanceResources() const
{
  return m_SharedInstanceResources;
}

GameLogicSystems & GameLogicContainer::GetSystems() const
{
  return m_Systems;
}

const GameStage & GameLogicContainer::GetStage() const
{
  return m_Stage;
}

bool GameLogicContainer::IsAuthority() const
{
  return m_IsAuthority;
}

void GameLogicContainer::TriggerImmediateSend() const
{
  m_SendTimer = 0;
}
