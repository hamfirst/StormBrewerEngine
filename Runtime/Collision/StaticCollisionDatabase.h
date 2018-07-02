#pragma once

#include "Foundation/SpatialDatabase/SpatialDatabase.h"

#include "Runtime/Collision/CollisionDatabaseResult.h"

class StaticCollisionDatabase
{
public:
  StaticCollisionDatabase(std::size_t num_collision_layers = 1);

  uint32_t CheckCollision(const Box & box, uint32_t collision_layer_mask) const;
  uint32_t CheckCollisionAny(const Box & box, uint32_t collision_layer_mask) const;
  uint32_t CheckLineOfSight(const Vector2 & start, const Vector2 & end, uint32_t collision_layer_mask) const;

  uint32_t CheckClearance(const Vector2 & pos, uint32_t maximum_clearance, uint32_t collision_layer_mask) const;

  Optional<Box> PushMapCollision(std::size_t map_id, std::vector<std::vector<Box>> && collision_boxes);
  void RemoveMapCollision(std::size_t map_id);

private:
  friend class Camera;

  std::vector<SpatialDatabase> m_CollisionLayers;
};
