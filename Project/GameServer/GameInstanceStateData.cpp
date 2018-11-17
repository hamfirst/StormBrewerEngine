
#include "GameServer/GameInstanceStateData.h"
#include "GameServer/GameInstance.h"

#include "GameShared/GameStageManager.h"

GameInstanceStateData::GameInstanceStateData(NotNullPtr<GameInstance> instance, const GameInitSettings & init_settings, 
                                             GameStageManager & stage_manager) :
  m_Instance(instance),
  m_StageManager(stage_manager),
  m_InitSettings(init_settings)
{

}

GameInstanceStatePlayer & GameInstanceStateData::GetClient(std::size_t index)
{
  auto ptr = m_Players.TryGet(index);
  ASSERT(ptr, "Fetching invalid client");
  return *ptr;
}

const GameInitSettings & GameInstanceStateData::GetInitSettings() const
{
  return m_InitSettings;
}

void GameInstanceStateData::ChangeInitSettings(const GameInitSettings & init_settings)
{
  m_InitSettings = init_settings;
}

const GameStage & GameInstanceStateData::GetStage() const
{
  return *m_StageManager.GetStage(m_InitSettings);
}

uint32_t GameInstanceStateData::GetPrivateRoomId() const
{
  return m_Instance->m_PrivateRoomId;
}

void GameInstanceStateData::SetNewState(std::unique_ptr<GameInstanceStateBase> && state)
{
  m_Instance->SetNewState(std::move(state));
}
