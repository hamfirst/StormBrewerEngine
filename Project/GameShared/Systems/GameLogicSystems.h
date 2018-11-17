#pragma once

#include "Runtime/Collision/CollisionDatabase.h"

#include "GameShared/Systems/CVCPushSystem.h"

class GameLogicSystems
{
public:
  GameLogicSystems(const StaticCollisionDatabase & static_collision);

  CollisionDatabase & GetCollisionDatabase();
  CVCPushSystem & GetCVCPushSystem();

private:
  CollisionDatabase m_CollisionDatabase;
  CVCPushSystem m_CVCPushSystem;
};
