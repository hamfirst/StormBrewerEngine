#pragma once

#include "Foundation/SpatialDatabase/SpatialDatabase.h"


class CollisionDatabase
{
public:
  CollisionDatabase(std::size_t num_collision_layers = 1);

  uint32_t CheckCollision(const Box & box, uint32_t collision_layer_mask) const;
  uint32_t CheckCollisionAny(const Box & box, uint32_t collision_layer_mask) const;

  void PushMapCollision(std::size_t map_id, std::vector<std::vector<Box>> && collision_boxes);
  void RemoveMapCollision(std::size_t map_id);

private:
  friend class Camera;

  std::vector<SpatialDatabase> m_CollisionLayers;
};
