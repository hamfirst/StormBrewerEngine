#include "Game/NetworkEvents/GameNetworkData.refl.h"
#include "GameShared/GameSharedCommon.h"
#include "GameShared/GameWorld.h"

GameWorld::GameWorld(
  GameController & game_controller,
  const GameInitSettings & init_settings,
  GameInstanceData & global_data,
  GameInstanceLowFrequencyData & low_freq_data,
  ServerObjectManager & object_manager,
  ServerObjectEventSystem & server_object_event_system,
  GameServerEventSender & server_event_sender,
  GameSimulationEventCallbacks & sim_event_sender,
  GameLogicSystems & systems,
  const GameStage & stage,
  bool is_authority,
  int & send_timer,
  bool & modified_low_freq_data) :
  m_GameController(game_controller),
  m_InitSettings(init_settings),
  m_InstanceData(global_data),
  m_LowFrequencyData(low_freq_data),
  m_ObjectManager(object_manager),
  m_ObjectEventSystem(server_object_event_system),
  m_ServerEventSender(server_event_sender),
  m_SimEventSender(sim_event_sender),
  m_Systems(systems),
  m_Stage(stage),
  m_IsAuthority(is_authority),
  m_SendTimer(send_timer),
  m_ModifiedLowFreqData(modified_low_freq_data),
  m_AllowModifyLowFreqData(false)
{

}

GameController & GameWorld::GetGameController()
{
  return m_GameController;
}

const GameInitSettings & GameWorld::GetGameInitSettings()
{
  return m_InitSettings;
}

GameInstanceData & GameWorld::GetInstanceData()
{
  return m_InstanceData;
}

const GameInstanceLowFrequencyData & GameWorld::GetLowFrequencyInstanceData() const
{
  return m_LowFrequencyData;
}

GameInstanceLowFrequencyData & GameWorld::GetLowFrequencyInstanceDataForModify()
{
  ASSERT(m_AllowModifyLowFreqData, "Modifying low freq data when not allowed");

  m_ModifiedLowFreqData = true;
  return m_LowFrequencyData;
}

ServerObjectManager & GameWorld::GetObjectManager()
{
  return m_ObjectManager;
}

ServerObjectEventSystem & GameWorld::GetServerObjectEventSystem()
{
  return m_ObjectEventSystem;
}

GameServerEventSender & GameWorld::GetEventSender()
{
  return m_ServerEventSender;
}

GameSimulationEventCallbacks & GameWorld::GetSimEventCallbacks()
{
  return m_SimEventSender;
}

GameLogicSystems & GameWorld::GetSystems()
{
  return m_Systems;
}

const GameStage & GameWorld::GetStage()
{
  return m_Stage;
}

bool GameWorld::IsAuthority()
{
  return m_IsAuthority;
}

void GameWorld::TriggerImmediateSend()
{
  m_SendTimer = 0;
}

void GameWorld::SetAllowModifyLowFrequencyData(bool allow)
{
  m_AllowModifyLowFreqData = allow;
}
