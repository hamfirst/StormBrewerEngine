

#include "Foundation/Common.h"
#include "Foundation/Math/Util.h"

#include "Game/GameLogicContainer.h"
#include "Game/GameServerEventSender.h"
#include "Game/GameStage.h"

#include "Game/ServerObjects/PlayerServerObject.refl.h"
#include "Game/ServerObjects/PlayerServerObject.refl.meta.h"

static GameNetVal kMoveSpeed = GameNetVal("1.7");
static GameNetVal kDashSpeed = GameNetVal("2.7");
static GameNetVal kMoveSpeedAccel = GameNetVal("0.08");
static GameNetVal kMoveSpeedDrag = GameNetVal("0.12");
static GameNetVal kPlayerRadius = GameNetVal("10");
static GameNetVal kMoveThreshold = GameNetVal("0.1");

void PlayerServerObject::Init(const PlayerServerObjectInitData & init_data)
{
  
}

void PlayerServerObject::UpdateFirst(GameLogicContainer & game_container)
{
  auto controls = m_Controls;

  GameNetVal one = GameNetVal(1);
  GameNetVal two = GameNetVal(2);
  GameNetVec2 target_velocity;

  target_velocity.x = m_InputAngle.CosSlow();
  target_velocity.y = m_InputAngle.SinSlow();

  target_velocity *= (m_InputStrength * kMoveSpeed);
  
  IntersectionVecFuncs<GameNetVec2>::NormalizeInPlace(target_velocity, {});

  auto velocity = m_Velocity;

  auto & stage = game_container.GetStage();
  auto & collision = stage.GetCollision();

  Intersection<GameNetVal>::CollisionLine movement(m_Position, m_Position + velocity);
  IntersectionResult<GameNetVal> result;
  CollisionDatabaseData<GameNetVal> hit_line;

  if (collision.SweptCircleTest(movement, kPlayerRadius, result, hit_line, 0x01) == false)
  {
    m_Position += velocity;
  }
  else
  {
    if (result.m_T > kMoveThreshold)
    {
      result.m_T -= kMoveThreshold;

      auto actual_movement = velocity * result.m_T;
      m_Position += actual_movement;

      velocity -= actual_movement;
    }

    auto reflect_dp = IntersectionVecFuncs<GameNetVec2>::Dot(result.m_HitNormal, m_Velocity);
    m_Velocity -= result.m_HitNormal * reflect_dp * two;

    auto second_check_dp = IntersectionVecFuncs<GameNetVec2>::Dot(result.m_HitNormal, velocity);
    velocity -= result.m_HitNormal * second_check_dp * two;

    Intersection<GameNetVal>::CollisionLine new_movement(m_Position, m_Position + velocity);
    if (collision.SweptCircleTest(new_movement, kPlayerRadius, result, hit_line, 0x01) == false)
    {
      m_Position += velocity;
    }
  }
}

czstr PlayerServerObject::GetEntityBinding()
{
  return "./Entities/Player.entity";
}
