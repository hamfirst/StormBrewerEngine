
#include "GameServer/GameInstanceStateData.h"
#include "GameServer/GameInstance.h"

#include "Game/GameStageManager.h"

GameInstanceStateData::GameInstanceStateData(NotNullPtr<GameInstance> instance, const GameInitSettings & init_settings, 
                                             GameSharedGlobalResources & shared_resources, GameStageManager & stage_manager) :
  m_Instance(instance),
  m_SharedGlobalResources(shared_resources),
  m_StageManager(stage_manager),
  m_InitSettings(init_settings)
{

}

GameInstanceStatePlayer & GameInstanceStateData::GetClient(std::size_t index)
{
  auto ptr = m_Players.TryGet(index);
  if (ptr)
  {
    return *ptr;
  }

  throw false;
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

GameSharedGlobalResources & GameInstanceStateData::GetSharedResources()
{
  return m_SharedGlobalResources;
}

void GameInstanceStateData::SetNewState(std::unique_ptr<GameInstanceStateBase> && state)
{
  m_Instance->SetNewState(std::move(state));
}
