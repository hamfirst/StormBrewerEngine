#pragma once

#include "Game/GameNetworkData.refl.h"
#include "Game/GameLogicContainer.h"

class PlayerAI
{
public:
  static void UpdateAI(GameLogicContainer & game, std::size_t player_index);
};
