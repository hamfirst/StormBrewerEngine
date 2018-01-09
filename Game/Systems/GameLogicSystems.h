#pragma once

#include "Runtime/Collision/CollisionDatabase.h"

#define COLLISION_LAYER_SOLID    0x01
#define COLLISION_LAYER_ONE_WAY  0x02
#define COLLISION_LAYER_PLAYER   0x04

class GameLogicSystems
{
public:
  GameLogicSystems(const StaticCollisionDatabase & static_collision);

  CollisionDatabase & GetCollisionDatabase();

private:
  CollisionDatabase m_CollisionDatabase;
};
