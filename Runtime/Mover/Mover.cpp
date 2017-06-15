
#include "Runtime/RuntimeCommon.h"
#include "Runtime/Mover/Mover.h"
#include "Runtime/Mover/MoverState.h"

void Mover::UpdateMoverNoCollision(MoverState & mover_state)
{
  mover_state.m_SubPixel += mover_state.m_Velocity;

  while (mover_state.m_SubPixel.x < 0)
  {
    mover_state.m_SubPixel.x += 128;
    mover_state.m_Position.x--;
  }

  while (mover_state.m_SubPixel.x >= 128)
  {
    mover_state.m_SubPixel.x -= 128;
    mover_state.m_Position.x++;
  }

  while (mover_state.m_SubPixel.y < 0)
  {
    mover_state.m_SubPixel.y += 128;
    mover_state.m_Position.y--;
  }

  while (mover_state.m_SubPixel.y >= 128)
  {
    mover_state.m_SubPixel.y -= 128;
    mover_state.m_Position.y++;
  }
}

MoverResult Mover::UpdateMover(MoverState & mover_state, CollisionSystem & collision, const Vector2 & position, const Box & move_box, uint32_t collision_mask, bool check_initial)
{
  MoverResult result = {};

  auto coll_box = move_box;
  coll_box.m_Start += position;
  coll_box.m_End += position;

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

  mover_state.m_SubPixel += mover_state.m_Velocity;

  while (mover_state.m_SubPixel.x < 0)
  {
    coll_box.m_Start.x--;
    coll_box.m_End.x--;

    auto coll_result = collision.CheckCollision(coll_box, collision_mask);
    if (coll_result != 0)
    {
      mover_state.m_SubPixel.x = 0;
      mover_state.m_Velocity.x = 0;
      result.m_HitLeft = coll_result;
      break;
    }
    else
    {
      mover_state.m_SubPixel.x += 128;
      mover_state.m_Position.x--;
    }
  }

  while (mover_state.m_SubPixel.x >= 128)
  {
    coll_box.m_Start.x++;
    coll_box.m_End.x++;

    auto coll_result = collision.CheckCollision(coll_box, collision_mask);
    if (coll_result != 0)
    {
      mover_state.m_SubPixel.x = 127;
      mover_state.m_Velocity.x = 0;
      result.m_HitRight = coll_result;
      break;
    }
    else
    {
      mover_state.m_SubPixel.x -= 128;
      mover_state.m_Position.x++;
    }
  }

  while (mover_state.m_SubPixel.y < 0)
  {
    coll_box.m_Start.y--;
    coll_box.m_End.y--;

    auto coll_result = collision.CheckCollision(coll_box, collision_mask);
    if (coll_result != 0)
    {
      mover_state.m_SubPixel.y = 0;
      mover_state.m_Velocity.y = 0;
      result.m_HitBottom = coll_result;
      break;
    }
    else
    {
      mover_state.m_SubPixel.y += 128;
      mover_state.m_Position.y--;
    }
  }

  while (mover_state.m_SubPixel.y >= 128)
  {
    coll_box.m_Start.y++;
    coll_box.m_End.y++;

    auto coll_result = collision.CheckCollision(coll_box, collision_mask);
    if (coll_result != 0)
    {
      mover_state.m_SubPixel.y = 127;
      mover_state.m_Velocity.y = 0;
      result.m_HitTop = coll_result;
      break;
    }
    else
    {
      mover_state.m_SubPixel.y -= 128;
      mover_state.m_Position.y++;
    }
  }

  result.m_HitCombined = result.m_HitLeft | result.m_HitRight | result.m_HitTop | result.m_HitBottom;
  return result;
}

