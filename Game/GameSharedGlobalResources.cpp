
#include "Game/GameSharedGlobalResources.h"

bool GameSharedGlobalResources::IsLoaded() const
{
  return m_LevelList.IsLevelListLoaded();
}

