#pragma once

#include "Foundation/SpatialDatabase/SpatialDatabase.h"
#include "Foundation/Bitset/Bitset.h"

#include "Runtime/Collision/CollisionDatabaseResult.h"

using CollisionObjectMask = StaticBitset<256, uint64_t>;

class DynamicCollisionDatabase
{
public:
  DynamicCollisionDatabase();

  Optional<CollisionDatabaseCheckResult> CheckCollisionAny(const Box & box,
          uint32_t collision_layer_mask, NullOptPtr<CollisionObjectMask> obj_mask = nullptr) const;
  std::vector<CollisionDatabaseCheckResult> QueryAll(const Box & box,
          uint32_t collision_layer_mask, NullOptPtr<CollisionObjectMask> obj_mask = nullptr) const;

  void ResetCollision();
  void PushCollision(const Box & box, uint32_t collision_mask,
          CollisionDatabaseObjectInfo && obj_info, Optional<int> & collision_id);

private:
  friend class Camera;

  SpatialDatabase m_Collision;
  std::vector<CollisionDatabaseCheckResult> m_Objects;

  int m_NextCollisionId = 0;
};
