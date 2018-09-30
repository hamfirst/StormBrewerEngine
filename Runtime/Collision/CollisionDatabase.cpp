
#include "Runtime/RuntimeCommon.h"
#include "Runtime/Collision/CollisionDatabase.h"

#include "Foundation/Math/Intersection.h"
#include "Foundation/Math/LineDrawing.h"
#include "Foundation/Math/Util.h"

#include <sb/vector.h>

CollisionDatabase::CollisionDatabase(const StaticCollisionDatabase & static_collision) :
  m_StaticCollision(static_collision)
{

}

Optional<CollisionDatabaseCheckResult> CollisionDatabase::CheckCollisionAny(const Box & box, uint32_t collision_layer_mask) const
{
  auto result_mask = m_StaticCollision.CheckCollision(box, collision_layer_mask);
  auto result = m_DynamicCollision.CheckCollisionAny(box, collision_layer_mask);
  if (result)
  {
    result->m_Mask |= result_mask;
    return result;
  }

  if (result_mask == 0)
  {
    return {};
  }

  CollisionDatabaseCheckResult out;
  out.m_Mask = result_mask;
  return out;
}

std::vector<CollisionDatabaseCheckResult> CollisionDatabase::QueryAllDynamic(const Box & box, uint32_t collision_layer_mask) const
{
  return m_DynamicCollision.QueryAll(box, collision_layer_mask);
}

uint32_t CollisionDatabase::CheckLineOfSight(const Vector2 & start, const Vector2 & end, uint32_t collision_layer_mask) const
{
  return m_StaticCollision.CheckLineOfSight(start, end, collision_layer_mask);
}

Optional<CollisionDatabaseTraceResult> CollisionDatabase::TracePath(const Vector2 & start, const Vector2 & end, uint32_t collision_layer_mask) const
{
  Box b = {};
  return TracePath(b, start, end, collision_layer_mask);
}

Optional<CollisionDatabaseTraceResult> CollisionDatabase::TracePath(const Box & box, const Vector2 & start, const Vector2 & end, uint32_t collision_layer_mask) const
{
  Optional<CollisionDatabaseTraceResult> out;
  VisitPointsAlongLine(start, end, [&](const Vector2 & p) 
  {
    Box b = box;
    b.m_Start += p;
    b.m_End += p;

    auto result = CheckCollisionAny(b, collision_layer_mask);
    if (result)
    {
      out.Emplace();
      out->m_ImpactPos = p;
      out->m_Mask = result->m_Mask;
      out->m_HitObject = result->m_HitObject;

      auto base_offset = end - start;
      auto hit_offset = p - start;

      out->m_T = IntersectionVecFuncs<Vector2f>::Mag(hit_offset) / IntersectionVecFuncs<Vector2f>::Mag(base_offset);
      return false;
    }

    return true;
  });

  return out;
}

uint32_t CollisionDatabase::CheckClearance(const Vector2 & pos, uint32_t maximum_clearance, uint32_t collision_layer_mask) const
{
  return m_StaticCollision.CheckClearance(pos, maximum_clearance, collision_layer_mask);
}

void CollisionDatabase::ResetDynamicCollision()
{
  m_DynamicCollision.ResetCollision();
}

void CollisionDatabase::PushDynamicCollision(const Box & box, uint32_t collision_mask, CollisionDatabaseObjectInfo && obj_info)
{
  m_DynamicCollision.PushCollision(box, collision_mask, std::move(obj_info));
}
