#pragma once

#include "Foundation/SpatialDatabase/SpatialDatabase.h"

#include "Runtime/Collision/CollisionDatabaseResult.h"



class DynamicCollisionDatabase
{
public:
  DynamicCollisionDatabase();

  Optional<CollisionDatabaseCheckResult> CheckCollisionAny(const Box & box, uint32_t collision_layer_mask) const;
  std::vector<CollisionDatabaseCheckResult> QueryAll(const Box & box, uint32_t collision_layer_mask) const;

  void ResetCollision();
  void PushCollision(const Box & box, uint32_t collision_mask, CollisionDatabaseObjectInfo && obj_info);

private:
  friend class Camera;

  SpatialDatabase m_Collision;
  std::vector<CollisionDatabaseCheckResult> m_Objects;
};
