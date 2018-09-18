#pragma once

#include "Foundation/Math/Intersection.h"

#include "Runtime/RuntimeCommon.h"
#include "Runtime/Collision/CollisionDatabase.h"

class EngineState;
class Entity;

#define MOVER_STEP_HEIGHT
#define MOVER_ONE_WAY_COLLISION

struct MoverResult
{
  Optional<CollisionDatabaseCheckResult> m_HitInitial;
  Optional<CollisionDatabaseCheckResult> m_HitTop;
  Optional<CollisionDatabaseCheckResult> m_HitRight;
  Optional<CollisionDatabaseCheckResult> m_HitLeft;
  Optional<CollisionDatabaseCheckResult> m_HitBottom;
  uint32_t m_HitCombined = 0;
  Vector2 m_ResultPos = {};
};

struct MoveRequest
{
  Vector2 m_StartPosition;
  Vector2 m_EndPosition;

  Box m_MoveBox;

#ifdef MOVER_STEP_HEIGHT
  bool m_StepDown;
#endif
};

class Mover
{
public:
  
  template <typename VecType>
  static MoveRequest CreateMoveRequest(const VecType & position, const VecType & velocity, const Box & move_box, bool step_down = false)
  {
    using VecCompType = VecComp<VecType>;

    auto start = position;
    auto end = position + velocity;

    MoveRequest req;
    req.m_StartPosition = Vector2((int)IntersectionFuncs<VecCompType>::Floor(start.x), (int)IntersectionFuncs<VecCompType>::Floor(start.y));
    req.m_EndPosition = Vector2((int)IntersectionFuncs<VecCompType>::Floor(end.x), (int)IntersectionFuncs<VecCompType>::Floor(end.y));
    req.m_MoveBox = move_box;

#ifdef MOVER_STEP_HEIGHT
    req.m_StepDown = step_down;
#endif
    return req;
  }

#ifdef MOVER_ONE_WAY_COLLISION
  static MoverResult UpdateMover(const CollisionDatabase & collision, const MoveRequest & req, uint32_t collision_mask, uint32_t one_way_collision_mask, bool check_initial = false);
#else
  static MoverResult UpdateMover(const CollisionDatabase & collision, const MoveRequest & req, uint32_t collision_mask, bool check_initial = false);
#endif
};
