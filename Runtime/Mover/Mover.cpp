
#include "Runtime/RuntimeCommon.h"
#include "Runtime/Mover/Mover.h"


MoverResult Mover::UpdateMover(const CollisionDatabase & collision, const MoveRequest & req, uint32_t collision_mask, bool check_initial)
{
  MoverResult result = {};

  auto coll_box = req.m_MoveBox;
  coll_box.m_Start += req.m_StartPosition;
  coll_box.m_End += req.m_StartPosition;

  auto cur_pos = req.m_StartPosition;
  auto end_pos = req.m_EndPosition;

  if (check_initial)
  {
    auto coll_result = collision.CheckCollision(coll_box, collision_mask);
    if (coll_result != 0)
    {
      result.m_HitInitial = coll_result;
      result.m_HitCombined = coll_result;
      return result;
    }
  }

  while(cur_pos.x > end_pos.x)
  {
    coll_box.m_Start.x--;
    coll_box.m_End.x--;

    auto coll_result = collision.CheckCollision(coll_box, collision_mask);
    if (coll_result != 0)
    {
      coll_box.m_Start.x++;
      coll_box.m_End.x++;
      result.m_HitLeft = coll_result;
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

    auto coll_result = collision.CheckCollision(coll_box, collision_mask);
    if (coll_result != 0)
    {
      coll_box.m_Start.x--;
      coll_box.m_End.x--;
      result.m_HitRight = coll_result;
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

    auto coll_result = collision.CheckCollision(coll_box, collision_mask);
    if (coll_result != 0)
    {
      coll_box.m_Start.y++;
      coll_box.m_End.y++;
      result.m_HitBottom = coll_result;
      break;
    }
    else
    {
      cur_pos.y--;
    }
  }

  while (cur_pos.y < end_pos.y)
  {
    coll_box.m_Start.y++;
    coll_box.m_End.y++;

    auto coll_result = collision.CheckCollision(coll_box, collision_mask);
    if (coll_result != 0)
    {
      coll_box.m_Start.y--;
      coll_box.m_End.y--;
      result.m_HitTop = coll_result;
      break;
    }
    else
    {
      cur_pos.y++;
    }
  }

  result.m_HitCombined = result.m_HitLeft | result.m_HitRight | result.m_HitTop | result.m_HitBottom;
  result.m_ResultPos = cur_pos;
  return result;
}

