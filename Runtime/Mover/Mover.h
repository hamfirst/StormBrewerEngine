#pragma once

#include "Runtime/RuntimeCommon.h"
#include "Runtime/Mover/MoverState.h"
#include "Runtime/Collision/CollisionSystem.h"

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
};

class Mover
{
public:
  static void UpdateMoverNoCollision(MoverState & mover_state);
  static MoverResult UpdateMover(MoverState & mover_state, CollisionSystem & collision, 
    const Vector2 & position, const Box & move_box, uint32_t collision_mask, bool check_initial = false);
};
