
#include "Runtime/RuntimeCommon.h"
#include "Runtime/Collision/DynamicCollisionDatabase.h"

#include "Foundation/Math/Intersection.h"
#include "Foundation/Math/LineDrawing.h"
#include "Foundation/Math/Util.h"

#include <sb/vector.h>

DynamicCollisionDatabase::DynamicCollisionDatabase()
{

}

Optional<CollisionDatabaseCheckResult> DynamicCollisionDatabase::CheckCollisionAny(const Box & box,
        uint32_t collision_layer_mask, NullOptPtr<CollisionObjectMask> obj_mask) const
{
  std::vector<std::size_t> elem_ids;
  m_Collision.Query(box, elem_ids);

  if(obj_mask)
  {
    for (auto &elem : elem_ids)
    {
      if (m_Objects[elem].m_Mask & collision_layer_mask)
      {
        if(m_Objects[elem].m_ObjectId == -1 || obj_mask->Get(m_Objects[elem].m_ObjectId) == false)
        {
          return Optional<CollisionDatabaseCheckResult>(m_Objects[elem]);
        }
      }
    }
  }
  else
  {
    for (auto &elem : elem_ids)
    {
      if (m_Objects[elem].m_Mask & collision_layer_mask)
      {
        return Optional<CollisionDatabaseCheckResult>(m_Objects[elem]);
      }
    }
  }

  return {};
}

std::vector<CollisionDatabaseCheckResult> DynamicCollisionDatabase::QueryAll(const Box & box,
        uint32_t collision_layer_mask, NullOptPtr<CollisionObjectMask> obj_mask) const
{
  std::vector<std::size_t> elem_ids;
  m_Collision.Query(box, elem_ids);

  std::vector<CollisionDatabaseCheckResult> hits;

  if(obj_mask)
  {
    for (auto &elem : elem_ids)
    {
      if (m_Objects[elem].m_Mask & collision_layer_mask)
      {
        if(m_Objects[elem].m_ObjectId == -1 || obj_mask->Get(m_Objects[elem].m_ObjectId) == false)
        {
          hits.emplace_back(m_Objects[elem]);
        }
      }
    }
  }
  else
  {
    for (auto &elem : elem_ids)
    {
      if (m_Objects[elem].m_Mask & collision_layer_mask)
      {
        hits.emplace_back(m_Objects[elem]);
      }
    }
  }

  return hits;
}

void DynamicCollisionDatabase::ResetCollision()
{
  m_Objects.clear();
  m_Collision.Clear();

  m_NextCollisionId = 0;
}

void DynamicCollisionDatabase::GetCollisionId(Optional<int> & collision_id)
{
  if(collision_id.IsValid() == false)
  {
    collision_id = m_NextCollisionId;
    m_NextCollisionId++;
  }
}

void DynamicCollisionDatabase::PushCollision(const Box & box, uint32_t collision_mask,
        CollisionDatabaseObjectInfo && obj_info, Optional<int> & collision_id)
{
  GetCollisionId(collision_id);

  auto index = m_Objects.size();

  m_Objects.emplace_back(CollisionDatabaseCheckResult{ std::move(obj_info), collision_mask, collision_id.Value() });
  m_Collision.Insert(box, (uint32_t)index);
}
