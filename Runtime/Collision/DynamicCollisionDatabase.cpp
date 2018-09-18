
#include "Runtime/RuntimeCommon.h"
#include "Runtime/Collision/DynamicCollisionDatabase.h"

#include "Foundation/Math/Intersection.h"
#include "Foundation/Math/LineDrawing.h"
#include "Foundation/Math/Util.h"

#include <sb/vector.h>

DynamicCollisionDatabase::DynamicCollisionDatabase()
{

}

Optional<CollisionDatabaseCheckResult> DynamicCollisionDatabase::CheckCollisionAny(const Box & box, uint32_t collision_layer_mask) const
{
  std::vector<std::size_t> elem_ids;
  m_Collision.Query(box, elem_ids);

  for (auto & elem : elem_ids)
  {
    if (m_Objects[elem].m_Mask & collision_layer_mask)
    {
      return Optional<CollisionDatabaseCheckResult>(m_Objects[elem]);
    }
  }

  return {};
}

std::vector<CollisionDatabaseCheckResult> DynamicCollisionDatabase::QueryAll(const Box & box, uint32_t collision_layer_mask) const
{
  std::vector<std::size_t> elem_ids;
  m_Collision.Query(box, elem_ids);

  std::vector<CollisionDatabaseCheckResult> hits;

  for (auto & elem : elem_ids)
  {
    if (m_Objects[elem].m_Mask & collision_layer_mask)
    {
      hits.emplace_back(m_Objects[elem]);
    }
  }

  return hits;
}

void DynamicCollisionDatabase::ResetCollision()
{
  m_Objects.clear();
  m_Collision.Clear();
}

void DynamicCollisionDatabase::PushCollision(const Box & box, uint32_t collision_mask, CollisionDatabaseObjectInfo && obj_info)
{
  auto index = m_Objects.size();

  m_Objects.emplace_back(CollisionDatabaseCheckResult{ std::move(obj_info), collision_mask });
  m_Collision.Insert(box, (uint32_t)index);
}
