#pragma once

#include "Runtime/RuntimeState.h"

#include "Game/GameSimulation.refl.h"

struct MapDef;

class GameState : public RuntimeState
{
public:
  GameState();

  void Update();
};

