#pragma once

#include "Foundation/Common.h"
#include "Foundation/Any/Any.h"

using CollisionDatabaseObjectInfo = StaticAny<64>;

struct CollisionDatabaseTraceResult
{
  uint32_t m_Mask;
  Vector2 m_ImpactPos;
  float m_T;

  CollisionDatabaseObjectInfo m_HitObject;
};

struct CollisionDatabaseCheckResult
{
  CollisionDatabaseObjectInfo m_HitObject;
  uint32_t m_Mask;
};
