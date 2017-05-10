
#include "Runtime/RuntimeCommon.h"
#include "Runtime/Collision/CollisionSystem.h"

#include <sb/vector.h>

CollisionSystem::CollisionSystem(NotNullPtr<RuntimeState> runtime_state, std::size_t num_collision_layers) :
  m_RuntimeState(runtime_state),
  m_CollisionLayers(num_collision_layers)
{
  for (auto & elem : m_CollisionLayers)
  {
    elem.SetAllowUnique(true);
  }
}

uint32_t CollisionSystem::CheckCollision(const Box & box, uint32_t collision_layer_mask)
{
  uint32_t result = 0;
  for (std::size_t index = 0; index < m_CollisionLayers.size(); index++)
  {
    if (((1 << index) & collision_layer_mask) == 0)
    {
      continue;
    }

    if (m_CollisionLayers[index].QueryAny(box))
    {
      result |= (1 << index);
    }
  }

  return result;
}

uint32_t CollisionSystem::CheckCollisionAny(const Box & box, uint32_t collision_layer_mask)
{
  uint32_t result = 0;
  for (std::size_t index = 0; index < m_CollisionLayers.size(); index++)
  {
    if (((1 << index) & collision_layer_mask) == 0)
    {
      continue;
    }

    if (m_CollisionLayers[index].QueryAny(box))
    {
      return (1 << index);
    }
  }

  return 0;
}

void CollisionSystem::PushMapCollision(std::size_t map_id, std::vector<std::vector<Box>> & collision_boxes)
{
  for(std::size_t index = 0, end = std::min(collision_boxes.size(), m_CollisionLayers.size()); index < end; ++index)
  {
    if (collision_boxes[index].size() == 0)
    {
      continue;
    }

    Box bounding_box = collision_boxes[index][0];
    std::vector<std::pair<std::size_t, Box>> box_list;

    for (auto & box : collision_boxes[index])
    {
      box_list.emplace_back(std::make_pair(map_id, box));
      BoxUnionInPlace(bounding_box, box);
    }

    m_CollisionLayers[index].InsertBatch(bounding_box, box_list);
  }
}

void CollisionSystem::RemoveMapCollision(std::size_t map_id)
{
  for (auto & elem : m_CollisionLayers)
  {
    elem.VisitAll([&](uint32_t grid_id, SpatialDatabaseNode & node)
    {
      std::size_t index = 0;
      while (index < node.m_Elements.size())
      {
        if (node.m_Elements[index].first == map_id)
        {
          vremove_index_quick(node.m_Elements, index);
        }
        else
        {
          index++;
        }
      }
    });
  }
}
