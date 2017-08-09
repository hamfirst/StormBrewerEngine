#pragma once

#include "Game/GameLevelList.h"

class GameSharedGlobalResources
{
public:

  bool IsLoaded() const;

private:

  GameLevelList m_LevelList;
};

