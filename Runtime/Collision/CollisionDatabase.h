#pragma once

#include "Runtime/Collision/StaticCollisionDatabase.h"
#include "Runtime/Collision/DynamicCollisionDatabase.h"

class CollisionDatabase
{
public:
  explicit CollisionDatabase(const StaticCollisionDatabase & static_collision);

  Optional<CollisionDatabaseCheckResult> CheckCollisionAny(const Box & box, uint32_t collision_layer_mask) const;
  std::vector<CollisionDatabaseCheckResult> QueryAllDynamic(const Box & box, uint32_t collision_layer_mask) const;
  uint32_t CheckLineOfSight(const Vector2 & start, const Vector2 & end, uint32_t collision_layer_mask) const;

  Optional<CollisionDatabaseTraceResult> TracePath(const Vector2 & start, const Vector2 & end, uint32_t collision_layer_mask) const;
  Optional<CollisionDatabaseTraceResult> TracePath(const Box & box, const Vector2 & start, const Vector2 & end, uint32_t collision_layer_mask) const;

  uint32_t CheckClearance(const Vector2 & pos, uint32_t maximum_clearance, uint32_t collision_layer_mask) const;

  void ResetDynamicCollision();
  void PushDynamicCollision(const Box & box, uint32_t collision_mask, CollisionDatabaseObjectInfo && obj_info);

private:
  friend class Camera;

  const StaticCollisionDatabase & m_StaticCollision;
  DynamicCollisionDatabase m_DynamicCollision;
};
