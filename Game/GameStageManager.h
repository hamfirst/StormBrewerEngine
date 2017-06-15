#pragma once

#include "Foundation/Common.h"

#include "Game/GameNetworkData.refl.h"
#include "Game/GameLevelList.h"
#include "Game/GameStage.h"

#include "Runtime/Map/MapResource.h"

#include "Shared/AssetBundle/AssetBundle.h"

class GameStageManager
{
public:

  GameStageManager(GameLevelList & level_list);

  const GameStage * GetStage(const GameInitSettings & settings) const;
  std::size_t GetNumStages() const;

private:
  std::vector<GameStage> m_Stages;
};

