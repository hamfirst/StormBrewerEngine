#pragma once

#include "Runtime/RuntimeCommon.h"

class RuntimeState;
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
  static void UpdateMoverNoCollision(Entity * entity);
  static MoverResult UpdateMover(Entity * entity, const Box & move_box, uint32_t collision_mask, bool check_initial = false);
};
