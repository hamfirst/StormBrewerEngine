

#include "Game/GameCommon.h"

#include "Game/GameLogicContainer.h"
#include "Game/GameServerEventSender.h"
#include "Game/GameStage.h"
#include "Game/Systems/GameLogicSystems.h"

#include "Game/ServerObjects/GameServerObjectBase.refl.h"
#include "Game/ServerObjects/GameServerObjectBase.refl.meta.h"

CLIENT_ASSET(ClientAssetType::kEntity, "./Entities/DefaultServerObject.entity", g_DefaultServerObjectEntity);

void GameServerObjectBase::Init(const GameServerObjectBaseInitData & init_data)
{
  
}

void GameServerObjectBase::InitPosition(const Vector2 & pos)
{
  m_Position = GameNetVec2(pos.x, pos.y);
}

GameNetVec2 GameServerObjectBase::GetPosition() const
{
  return m_Position;
}

void GameServerObjectBase::SetPosition(const GameNetVec2 & pos)
{
  m_Position = pos;
}

Optional<AnimationState> GameServerObjectBase::GetAnimationState() const
{
  return {};
}

void GameServerObjectBase::SetAnimationState(const AnimationState & anim_state)
{

}

Optional<int> GameServerObjectBase::GetAssociatedPlayer() const
{
  return {};
}

void GameServerObjectBase::SetAssociatedPlayer(int associated_player) const
{

}

bool GameServerObjectBase::FrameAdvance(uint32_t anim_name_hash, bool loop, int frames)
{
  auto anim_state = GetAnimationState();
  auto sprite = GetSprite();
  if (anim_state && sprite.IsLoaded())
  {
    bool result = sprite->FrameAdvance(anim_name_hash, anim_state.Value(), loop, frames);
    SetAnimationState(anim_state.Value());

    return result;
  }

  return false;
}

void GameServerObjectBase::ResetAnimState()
{
  SetAnimationState(AnimationState{});
}

void GameServerObjectBase::PushDealDamageBox(const Box & b, const DamageEvent & damage_event, GameLogicContainer & game_container)
{
  EventMetaData new_meta(this, &game_container);

  auto facing = GetFacing();

  Box box = b;
  if (facing && facing.Value() == CharacterFacing ::kLeft)
  {
    box = box.MirrorX();
  }

  box = box.Offset(m_Position);

  auto dmg = game_container.GetServerObjectEventSystem().PushEventSource(box, new_meta, EventDef<DamageEvent>{});
  *dmg = damage_event;
}

void GameServerObjectBase::PushReceiveDamageBox(const Box & b, GameLogicContainer & game_container)
{
  auto facing = GetFacing();

  Box box = b;
  if (facing && facing.Value() == CharacterFacing::kLeft)
  {
    box = box.MirrorX();
  }

  box = box.Offset(m_Position);
  game_container.GetServerObjectEventSystem().PushEventReceiver<DamageEvent>(GetObjectHandle(), box);
}

SpritePtr GameServerObjectBase::GetSprite() const
{
  return {};
}

Optional<CharacterFacing> GameServerObjectBase::GetFacing() const
{
  return {};
}

#ifdef MOVER_ONE_WAY_COLLISION
MoverResult GameServerObjectBase::MoveCheckCollisionDatabase(GameLogicContainer & game_container, const GameNetVec2 & velocity, bool fallthrough)
#else
MoverResult GameServerObjectBase::MoveCheckCollisionDatabase(GameLogicContainer & game_container, const GameNetVec2 & velocity)
#endif
{
  auto & stage = game_container.GetStage();
  auto & collision = game_container.GetSystems().GetCollisionDatabase();

  auto sprite = GetSprite();
  auto move_box = sprite->GetSingleBox(COMPILE_TIME_CRC32_STR("MoveBox"));

  MoveRequest req = Mover::CreateMoveRequest(m_Position, velocity, move_box);

#ifdef MOVER_ONE_WAY_COLLISION
  auto result = Mover::UpdateMover(collision, req, COLLISION_LAYER_SOLID, fallthrough ? 0 : COLLISION_LAYER_ONE_WAY);
#else
  auto result = Mover::UpdateMover(collision, req, 0xFFFFFFFF);
#endif

  if (result.m_HitRight)
  {
    m_Position.x = IntersectionFuncs<GameNetVal>::NextLowest(result.m_ResultPos.x + 1);
  }
  else if (result.m_HitLeft)
  {
    m_Position.x = result.m_ResultPos.x;
  }
  else
  {
    m_Position.x += velocity.x;
  }

  if (result.m_HitTop)
  {
    m_Position.y = IntersectionFuncs<GameNetVal>::NextLowest(result.m_ResultPos.y + 1);
  }
  else if (result.m_HitBottom)
  {
    m_Position.y = result.m_ResultPos.y;
  }
  else
  {
    m_Position.y += velocity.y;
  }

  return result;
}

GameNetVec2 GameServerObjectBase::MoveCheckIntersectionDatabase(GameLogicContainer & game_container, const GameNetVec2 & vel, GameNetVal player_radius, GameNetVal move_threshold)
{
  GameNetVal one = GameNetVal(1);
  GameNetVal two = GameNetVal(2);

  auto & stage = game_container.GetStage();
  auto & collision = stage.GetIntersectionDatabase();

  auto result_velocity = vel;
  auto velocity = vel;

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

    auto reflect_dp = IntersectionVecFuncs<GameNetVec2>::Dot(result.m_HitNormal, result_velocity);
    result_velocity -= result.m_HitNormal * reflect_dp * two;

    auto second_check_dp = IntersectionVecFuncs<GameNetVec2>::Dot(result.m_HitNormal, velocity);
    velocity -= result.m_HitNormal * second_check_dp * two;

    Intersection<GameNetVal>::CollisionLine new_movement(m_Position, m_Position + velocity);
    if (collision.SweptCircleTest(new_movement, player_radius, result, hit_line, 0x01) == false)
    {
      m_Position += velocity;
    }
  }

  return result_velocity;
}