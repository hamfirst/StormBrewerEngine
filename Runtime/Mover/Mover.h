#pragma once

#include "Foundation/Math/Intersection.h"

#include "Runtime/RuntimeCommon.h"
#include "Runtime/Collision/CollisionDatabase.h"

class EngineState;
class Entity;

struct MoverResult
{
  uint32_t m_HitInitial = 0;
  uint32_t m_HitTop = 0;
  uint32_t m_HitRight = 0;
  uint32_t m_HitLeft = 0;
  uint32_t m_HitBottom = 0;
  uint32_t m_HitCombined = 0;
  Vector2 m_ResultPos = {};
};

struct MoveRequest
{
  Vector2 m_StartPosition;
  Vector2 m_EndPosition;

  Box m_MoveBox;
};

class Mover
{
public:

  template <typename VecType>
  static MoveRequest CreateMoveRequest(const VecType & position, const VecType & velocity, const Box & move_box)
  {
    using VecCompType = VecComp<VecType>;

    auto start = position;
    auto end = position + velocity;

    MoveRequest req;
    req.m_StartPosition = Vector2((int)IntersectionFuncs<VecCompType>::Floor(start.x), (int)IntersectionFuncs<VecCompType>::Floor(start.y));
    req.m_EndPosition = Vector2((int)IntersectionFuncs<VecCompType>::Floor(end.x), (int)IntersectionFuncs<VecCompType>::Floor(end.y));
    req.m_MoveBox = move_box;
    return req;
  }

  static MoverResult UpdateMover(const CollisionDatabase & collision, const MoveRequest & req, uint32_t collision_mask, bool check_initial = false);
};
