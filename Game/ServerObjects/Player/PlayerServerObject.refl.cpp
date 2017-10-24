

#include "Game/GameCommon.h"

#include "Game/GameLogicContainer.h"
#include "Game/GameServerEventSender.h"
#include "Game/GameStage.h"

#include "Game/ServerObjects/Player/PlayerServerObject.refl.h"
#include "Game/ServerObjects/Player/PlayerServerObject.refl.meta.h"

#include "Runtime/Sprite/SpriteResource.h"

GLOBAL_ASSET(SpritePtr, "./Sprites/Player.sprite", g_PlayerSprite);

static GameNetVal kMoveSpeed = GameNetVal("0.5");
static GameNetVal kPlayerRadius = GameNetVal("10");
static GameNetVal kMoveThreshold = GameNetVal("0.1");
static GameNetVal kJumpSpeed = GameNetVal("5.0");


void PlayerServerObject::Init(const PlayerServerObjectInitData & init_data)
{
  m_MoveBox = g_PlayerSprite->GetSingleBox(COMPILE_TIME_CRC32_STR("MoveBox"));
  m_State.SetType<PlayerStateDefault>();
}

void PlayerServerObject::UpdateFirst(GameLogicContainer & game_container)
{
  m_State->Update(*this, game_container);
}

void PlayerServerObject::Jump(GameLogicContainer & game_container)
{
  if (m_OnGround)
  {
    game_container.GetEventSender().BroadcastServerAuthEvent(PlaceholderServerAuthEvent {});

    m_Velocity.y += kJumpSpeed;
    m_OnGround = false;
  }
}

MoverResult PlayerServerObject::MoveCheckCollisionDatabase(GameLogicContainer & game_container)
{
  auto & stage = game_container.GetStage();
  auto & collision = stage.GetCollisionDatabase();

  MoveRequest req = Mover::CreateMoveRequest(m_Position, m_Velocity, m_MoveBox);
  auto result = Mover::UpdateMover(collision, req, 0xFFFFFFFF);

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

  m_OnGround = result.m_HitBottom;
  return result;
}

void PlayerServerObject::MoveCheckIntersectionDatabase(GameLogicContainer & game_container)
{
  GameNetVal one = GameNetVal(1);
  GameNetVal two = GameNetVal(2);

  auto velocity = m_Velocity;

  auto & stage = game_container.GetStage();
  auto & collision = stage.GetIntersectionDatabase();

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

void PlayerServerObject::HandlePlaceholderEvent(const PlaceholderEvent & ev, GameLogicContainer & game_container)
{

}

czstr PlayerServerObject::GetEntityBinding()
{
  return "./Entities/Player.entity";
}
