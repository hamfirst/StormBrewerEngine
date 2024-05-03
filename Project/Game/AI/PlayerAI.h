#pragma once

#include "Game/NetworkEvents/GameNetworkData.refl.h"
#include "GameShared/GameLogicContainer.h"

class PlayerAI
{
public:
  static void InitAI(GameLogicContainer & game, std::size_t player_index);
  static void UpdateAI(GameLogicContainer & game, std::size_t player_index);

};
