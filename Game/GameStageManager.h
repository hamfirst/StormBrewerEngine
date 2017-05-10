#pragma once

#include "Foundation/Common.h"

#include "Game/GameSimulation.refl.h"

class GameStage;

class GameStageManager
{
public:

  NullOptPtr<GameStage> GetStage(const GameInitSettings & init_settings);

private:
};

