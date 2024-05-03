#pragma once

#include "Foundation/Common.h"

#include "GameShared/GameLevelList.h"

#include "Game/NetworkEvents/GameNetworkData.refl.h"
#include "Game/Stage/GameStage.h"

#include "Runtime/Map/MapResource.h"

class GameStageManager
{
public:

  GameStageManager(GameLevelList & level_list);

  const GameStage * GetStage(const GameInitSettings & settings) const;
  std::size_t GetNumStages() const;

private:
  std::vector<std::unique_ptr<GameStage>> m_Stages;
};

