#pragma once

#include "Game/NetworkEvents/GameNetworkData.refl.h"
#include "GameShared/GameWorld.h"

class PlayerAI
{
public:
  static void InitAI(GameWorld & game, std::size_t player_index);
  static void UpdateAI(GameWorld & game, std::size_t player_index);

};
