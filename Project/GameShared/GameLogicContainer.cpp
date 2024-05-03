#include "Game/NetworkEvents/GameNetworkData.refl.h"
#include "GameShared/GameSharedCommon.h"
#include "GameShared/GameLogicContainer.h"

GameLogicContainer::GameLogicContainer(
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

GameController & GameLogicContainer::GetGameController()
{
  return m_GameController;
}

const GameInitSettings & GameLogicContainer::GetGameInitSettings()
{
  return m_InitSettings;
}

GameInstanceData & GameLogicContainer::GetInstanceData()
{
  return m_InstanceData;
}

const GameInstanceLowFrequencyData & GameLogicContainer::GetLowFrequencyInstanceData() const
{
  return m_LowFrequencyData;
}

GameInstanceLowFrequencyData & GameLogicContainer::GetLowFrequencyInstanceDataForModify()
{
  ASSERT(m_AllowModifyLowFreqData, "Modifying low freq data when not allowed");

  m_ModifiedLowFreqData = true;
  return m_LowFrequencyData;
}

ServerObjectManager & GameLogicContainer::GetObjectManager()
{
  return m_ObjectManager;
}

ServerObjectEventSystem & GameLogicContainer::GetServerObjectEventSystem()
{
  return m_ObjectEventSystem;
}

GameServerEventSender & GameLogicContainer::GetEventSender()
{
  return m_ServerEventSender;
}

GameSimulationEventCallbacks & GameLogicContainer::GetSimEventCallbacks()
{
  return m_SimEventSender;
}

GameLogicSystems & GameLogicContainer::GetSystems()
{
  return m_Systems;
}

const GameStage & GameLogicContainer::GetStage()
{
  return m_Stage;
}

bool GameLogicContainer::IsAuthority()
{
  return m_IsAuthority;
}

void GameLogicContainer::TriggerImmediateSend()
{
  m_SendTimer = 0;
}

void GameLogicContainer::SetAllowModifyLowFrequencyData(bool allow)
{
  m_AllowModifyLowFreqData = allow;
}
