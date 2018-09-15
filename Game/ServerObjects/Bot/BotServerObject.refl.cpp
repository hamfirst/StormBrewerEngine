
#include "Game/GameCommon.h"

#include "Game/GameController.refl.h"
#include "Game/GameServerEventSender.h"

#include "Game/ServerObjects/Bot/BotServerObject.refl.h"
#include "Game/ServerObjects/Bot/BotServerObject.refl.meta.h"

#include "Runtime/Animation/AnimationState.h"

void BotServerObject::Init(const BotServerObjectInitData & init_data)
{

}

void BotServerObject::UpdateFirst(GameLogicContainer & game_container)
{

}

void BotServerObject::UpdateMiddle(GameLogicContainer & game_container)
{
  auto behavior_tree = GetBehaviorTree();

  if(behavior_tree)
  {
    while(true)
    {
      m_Retransition = false;
      behavior_tree->Update(*this, game_container, game_container.GetInstanceData().m_Random);

      if(m_Retransition == false)
      {
        break;
      }
    }
  }
}

MoverResult BotServerObject::MoveCheckCollisionDatabase(GameLogicContainer & game_container)
{
  auto & stage = game_container.GetStage();
  auto & collision = game_container.GetSystems().GetCollisionDatabase();

  auto sprite = GetSprite();
  if(sprite == nullptr)
  {
    return {};
  }

  auto move_box = sprite->GetSingleBox(COMPILE_TIME_CRC32_STR("MoveBox"));
  MoveRequest req = Mover::CreateMoveRequest(m_Position, m_Velocity, move_box);

#ifdef MOVER_ONE_WAY_COLLISION
  auto result = Mover::UpdateMover(collision, req, COLLISION_LAYER_SOLID, COLLISION_LAYER_ONE_WAY);
#else
  auto result = Mover::UpdateMover(collision, req, 0xFFFFFFFF);
#endif

  if (result.m_HitRight)
  {
    m_Position.x = IntersectionFuncs<GameNetVal>::NextLowest(result.m_ResultPos.x + 1);
    m_Velocity.x = 0;
  }
  else if (result.m_HitLeft)
  {
    m_Position.x = result.m_ResultPos.x;
    m_Velocity.x = 0;
  }
  else
  {
    m_Position.x += m_Velocity.x;
  }

  if (result.m_HitTop)
  {
    m_Position.y = IntersectionFuncs<GameNetVal>::NextLowest(result.m_ResultPos.y + 1);
    m_Velocity.y = 0;
  }
  else if (result.m_HitBottom)
  {
    m_Position.y = result.m_ResultPos.y;
    m_Velocity.y = 0;
  }
  else
  {
    m_Position.y += m_Velocity.y;
  }

#ifdef PLATFORMER_MOVEMENT

  m_OnGround = result.m_HitBottom;

#endif

  return result;
}

void BotServerObject::MoveCheckIntersectionDatabase(GameLogicContainer & game_container, GameNetVal player_radius, GameNetVal move_threshold)
{
  GameNetVal one = GameNetVal(1);
  GameNetVal two = GameNetVal(2);

  auto velocity = m_Velocity;

  auto & stage = game_container.GetStage();
  auto & collision = stage.GetIntersectionDatabase();

  Intersection<GameNetVal>::CollisionLine movement(m_Position, m_Position + velocity);
  IntersectionResult<GameNetVal> result;
  CollisionDatabaseData<GameNetVal> hit_line;

  if (collision.SweptCircleTest(movement, player_radius, result, hit_line, 0x01) == false)
  {
    m_Position += velocity;
  }
  else
  {
    if (result.m_T > move_threshold)
    {
      result.m_T -= move_threshold;

      auto actual_movement = velocity * result.m_T;
      m_Position += actual_movement;

      velocity -= actual_movement;
    }

    auto reflect_dp = IntersectionVecFuncs<GameNetVec2>::Dot(result.m_HitNormal, m_Velocity);
    m_Velocity -= result.m_HitNormal * reflect_dp * two;

    auto second_check_dp = IntersectionVecFuncs<GameNetVec2>::Dot(result.m_HitNormal, velocity);
    velocity -= result.m_HitNormal * second_check_dp * two;

    Intersection<GameNetVal>::CollisionLine new_movement(m_Position, m_Position + velocity);
    if (collision.SweptCircleTest(new_movement, player_radius, result, hit_line, 0x01) == false)
    {
      m_Position += velocity;
    }
  }
}

bool BotServerObject::FrameAdvance(uint32_t anim_name_hash, bool loop, int frames)
{
  auto sprite = GetSprite();
  if(sprite == nullptr)
  {
    return false;
  }

  AnimationState state;
  state.m_AnimIndex = m_AnimIndex;
  state.m_AnimFrame = m_AnimFrame;
  state.m_AnimDelay = m_AnimDelay;

  auto result = sprite->FrameAdvance(anim_name_hash, state, loop, frames);
  m_AnimIndex = state.m_AnimIndex;
  m_AnimFrame = state.m_AnimFrame;
  m_AnimDelay = state.m_AnimDelay;

  return result;
}

void BotServerObject::RetransitionBT()
{
  m_Retransition = true;
}

SpriteResource * BotServerObject::GetSprite()
{
  return nullptr;
}

StormBehaviorTree<BotServerObject, GameLogicContainer> * BotServerObject::GetBehaviorTree()
{
  return nullptr;
}

void BotServerObject::InitPosition(const Vector2 & pos)
{
  m_Position = GameNetVec2(pos.x, pos.y);
}

Vector2 BotServerObject::GetPosition(GameLogicContainer & game_container) const
{
  return m_Position;
}

