
#include "Game/GameStageManager.h"
#include "Game/GameLevelList.h"


GameStageManager::GameStageManager(GameLevelList & level_list)
{
  auto level_count = level_list.GetNumLevels();
  for (std::size_t index = 0; index < level_count; ++index)
  {
    auto map = level_list.LoadLevel(index);
    m_Stages.emplace_back(map);
  }
}

const GameStage * GameStageManager::GetStage(const GameInitSettings & settings) const
{
  if (settings.m_StageIndex >= m_Stages.size())
  {
    return nullptr;
  }
  
  return &m_Stages[settings.m_StageIndex];
}

std::size_t GameStageManager::GetNumStages() const
{
  return m_Stages.size();
}
