#pragma once

#include "Foundation/SpatialDatabase/SpatialDatabase.h"

class RuntimeState;

class CollisionSystem
{
public:
  CollisionSystem(NotNullPtr<RuntimeState> runtime_state, std::size_t num_collision_layers = 1);

  uint32_t CheckCollision(const Box & box, uint32_t collision_layer_mask);
  uint32_t CheckCollisionAny(const Box & box, uint32_t collision_layer_mask);

  void PushMapCollision(std::size_t map_id, std::vector<std::vector<Box>> & collision_boxes);
  void RemoveMapCollision(std::size_t map_id);

private:
  friend class Camera;

  NotNullPtr<RuntimeState> m_RuntimeState;
  std::vector<SpatialDatabase> m_CollisionLayers;
};
