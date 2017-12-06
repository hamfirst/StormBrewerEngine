
#include "Runtime/RuntimeCommon.h"
#include "Runtime/Collision/CollisionDatabase.h"

#include "Foundation/Math/Intersection.h"

#include <sb/vector.h>

CollisionDatabase::CollisionDatabase(std::size_t num_collision_layers) :
  m_CollisionLayers(num_collision_layers)
{
  for (auto & elem : m_CollisionLayers)
  {
    elem.SetAllowUnique(true);
  }
}

uint32_t CollisionDatabase::CheckCollision(const Box & box, uint32_t collision_layer_mask) const
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

uint32_t CollisionDatabase::CheckCollisionAny(const Box & box, uint32_t collision_layer_mask) const
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

uint32_t CollisionDatabase::CheckLineOfSight(const Vector2 & start, const Vector2 & end, uint32_t collision_layer_mask) const
{
  uint32_t result = 0;

  auto query_box = Box::FromPoints(start, end);
  std::vector<Box> box_list;

  for (std::size_t index = 0; index < m_CollisionLayers.size(); index++)
  {
    m_CollisionLayers[index].QueryBoxes(query_box, box_list);
    for (auto & elem : box_list)
    {
      if (LineBoxIntersection(start, end, elem.m_Start, elem.m_End))
      {
        result |= (1 << index);
      }
    }

    box_list.clear();
  }

  return result;
}

uint32_t CollisionDatabase::CheckClearance(const Vector2 & pos, uint32_t maximum_clearance, uint32_t collision_layer_mask) const
{
  Box box = { pos, pos };
  box.m_End.y += maximum_clearance;

  uint32_t clearance = maximum_clearance;

  std::vector<Box> query_boxes;

  for (std::size_t index = 0; index < m_CollisionLayers.size(); index++)
  {
    if (((1 << index) & collision_layer_mask) == 0)
    {
      continue;
    }

    m_CollisionLayers[index].QueryBoxes(box, query_boxes);
    for (auto & elem : query_boxes)
    {
      if (elem.m_Start.y <= pos.y)
      {
        return 0;
      }

      uint32_t box_clearance = (uint32_t)(elem.m_Start.y - pos.y);
      clearance = std::min(box_clearance, clearance);
    }

    query_boxes.clear();
  }

  return clearance;
}

Optional<Box> CollisionDatabase::PushMapCollision(std::size_t map_id, std::vector<std::vector<Box>> && collision_boxes)
{
  Optional<Box> bounds;

  for(std::size_t index = 0, end = std::min(collision_boxes.size(), m_CollisionLayers.size()); index < end; ++index)
  {
    if (collision_boxes[index].size() == 0)
    {
      continue;
    }

    Box bounding_box = collision_boxes[index][0];
    std::vector<std::pair<std::size_t, Box>> box_list;

    if (bounds.IsValid())
    {
      BoxUnionInPlace(bounds.Value(), bounding_box);
    }
    else
    {
      bounds = bounding_box;
    }

    for (auto & box : collision_boxes[index])
    {
      box_list.emplace_back(std::make_pair(map_id, box));
      BoxUnionInPlace(bounding_box, box);
      BoxUnionInPlace(bounds.Value(), box);
    }

    m_CollisionLayers[index].InsertBatch(bounding_box, box_list);
  }

  return bounds;
}

void CollisionDatabase::RemoveMapCollision(std::size_t map_id)
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
