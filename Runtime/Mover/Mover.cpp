
#include "Runtime/RuntimeCommon.h"
#include "Runtime/Mover/Mover.h"

#ifdef MOVER_ONE_WAY_COLLISION
MoverResult Mover::UpdateMover(const CollisionDatabase & collision, const MoveRequest & req, uint32_t collision_mask, uint32_t one_way_collision_mask, bool check_initial)
#else
MoverResult Mover::UpdateMover(const CollisionDatabase & collision, const MoveRequest & req, uint32_t collision_mask, bool check_initial)
#endif
{
  MoverResult result = {};

  auto coll_box = req.m_MoveBox;
  coll_box.m_Start += req.m_StartPosition;
  coll_box.m_End += req.m_StartPosition;

  auto cur_pos = req.m_StartPosition;
  auto end_pos = req.m_EndPosition;

  if (check_initial)
  {
    auto coll_result = collision.CheckCollisionAny(coll_box, collision_mask);
    if (coll_result)
    {
      result.m_HitInitial = coll_result;
      result.m_HitCombined = coll_result->m_Mask;
      return result;
    }
  }

  while(cur_pos.x > end_pos.x)
  {
    coll_box.m_Start.x--;
    coll_box.m_End.x--;

    auto coll_result = collision.CheckCollisionAny(coll_box, collision_mask);
    if (coll_result)
    {
#ifdef MOVER_STEP_HEIGHT
      coll_box.m_Start.y++;
      coll_box.m_End.y++;
      auto new_coll_result = collision.CheckCollisionAny(coll_box, collision_mask);
      if (new_coll_result == 0)
      {
        cur_pos.x--;
        cur_pos.y++;
        continue;
      }

      coll_box.m_Start.y--;
      coll_box.m_End.y--;
#endif

      coll_box.m_Start.x++;
      coll_box.m_End.x++;
      result.m_HitLeft = coll_result;
      result.m_HitCombined |= coll_result->m_Mask;
      break;
    }
    else
    {
      cur_pos.x--;
    }
  }

  while (cur_pos.x < end_pos.x)
  {
    coll_box.m_Start.x++;
    coll_box.m_End.x++;

    auto coll_result = collision.CheckCollisionAny(coll_box, collision_mask);
    if (coll_result)
    {
#ifdef MOVER_STEP_HEIGHT
      coll_box.m_Start.y++;
      coll_box.m_End.y++;
      auto new_coll_result = collision.CheckCollisionAny(coll_box, collision_mask);
      if (new_coll_result == 0)
      {
        cur_pos.x--;
        cur_pos.y++;
        continue;
      }

      coll_box.m_Start.y--;
      coll_box.m_End.y--;
#endif

      coll_box.m_Start.x--;
      coll_box.m_End.x--;
      result.m_HitRight = coll_result;
      result.m_HitCombined |= coll_result->m_Mask;
      break;
    }
    else
    {
      cur_pos.x++;
    }
  }

  while(cur_pos.y > end_pos.y)
  {
    coll_box.m_Start.y--;
    coll_box.m_End.y--;

    auto coll_result = collision.CheckCollisionAny(coll_box, collision_mask);
    if (coll_result)
    {
      coll_box.m_Start.y++;
      coll_box.m_End.y++;
      result.m_HitBottom = coll_result;
      result.m_HitCombined |= coll_result->m_Mask;
      break;
    }
    else
    {
#ifdef MOVER_ONE_WAY_COLLISION
      Box foot_box = Box::FromPoints(coll_box.m_Start, Vector2(coll_box.m_End.x, coll_box.m_Start.y));
      auto fool_coll_result = collision.CheckCollisionAny(foot_box, one_way_collision_mask);
      if (fool_coll_result)
      {
        coll_box.m_Start.y++;
        coll_box.m_End.y++;
        result.m_HitBottom = fool_coll_result;
        result.m_HitCombined |= fool_coll_result->m_Mask;
        break;
      }
#endif

      cur_pos.y--;
    }
  }

  while (cur_pos.y < end_pos.y)
  {
    coll_box.m_Start.y++;
    coll_box.m_End.y++;

    auto coll_result = collision.CheckCollisionAny(coll_box, collision_mask);
    if (coll_result)
    {
      coll_box.m_Start.y--;
      coll_box.m_End.y--;
      result.m_HitTop = coll_result;
      result.m_HitCombined |= coll_result->m_Mask;
      break;
    }
    else
    {
      cur_pos.y++;
    }
  }

#ifdef MOVER_STEP_HEIGHT

  if (req.m_StepDown)
  {
#ifdef MOVER_ONE_WAY_COLLISION
    auto foot_mask = collision_mask | one_way_collision_mask;
#else
    auto foot_mask = collision_mask;
#endif

    auto coll_result = collision.CheckCollisionAny(coll_box, collision_mask);
    if (coll_result.IsValid() == false)
    {
      Box foot_box = Box::FromPoints(Vector2(coll_box.m_Start.x, coll_box.m_Start.y - 1), Vector2(coll_box.m_End.x, coll_box.m_Start.y - 1));

      auto foot_result_result = collision.CheckCollisionAny(foot_box, foot_mask);
      if (foot_result_result.IsValid())
      {
        result.m_HitBottom = foot_result_result;
        result.m_HitCombined |= foot_result_result->m_Mask;
      }
    }
  }

#endif

  result.m_ResultPos = cur_pos;
  return result;
}

