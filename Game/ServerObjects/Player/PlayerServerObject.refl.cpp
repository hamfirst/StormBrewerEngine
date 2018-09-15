

#include "Game/GameCommon.h"

#include "Game/GameLogicContainer.h"
#include "Game/GameServerEventSender.h"
#include "Game/GameStage.h"
#include "Game/Systems/GameLogicSystems.h"

#include "Game/ServerObjects/Player/PlayerServerObject.refl.h"
#include "Game/ServerObjects/Player/PlayerServerObject.refl.meta.h"

#include "Game/ServerObjects/Player/States/PlayerStateIdle.refl.h"
#include "Game/ServerObjects/Player/States/PlayerStateJump.refl.h"

#include "Game/Configs/PlayerConfig.refl.meta.h"

#include "Runtime/Sprite/SpriteResource.h"
#include "Runtime/Animation/AnimationState.h"
#include "Runtime/Config/ConfigResource.h"

GLOBAL_ASSET(SpritePtr, "./Sprites/Player.sprite", g_PlayerSprite);
GLOBAL_ASSET(ConfigPtr<PlayerConfig>, "./Configs/PlayerConfig.playerconfig", g_PlayerConfig);

void PlayerServerObject::Init(const PlayerServerObjectInitData & init_data)
{
  m_State.SetType<PlayerStateIdle>();

  if (GetSlotIndex() == 0)
  {
    m_Facing = CharacterFacing::kRight;
  }
  else
  {
    m_Facing = CharacterFacing::kLeft;
  }
}

void PlayerServerObject::UpdateFirst(GameLogicContainer & game_container)
{
  m_State->PreUpdate(*this, game_container);
  m_State->Move(*this, game_container);

  m_Retransition = true;
  m_State->Transition(*this, game_container);
  m_Retransition = false;

  m_State->Animate(*this, game_container);
  m_State->PostUpdate(*this, game_container);
}

#if defined(PLATFORMER_MOVEMENT)
void PlayerServerObject::Jump(GameLogicContainer & game_container)
{
#if defined(PLAYER_ENABLE_JUMP)
  if (m_OnGround)
  {
    game_container.GetEventSender().BroadcastServerAuthEvent(PlaceholderServerAuthEvent{});

    m_Velocity.y += g_PlayerConfig->m_JumpSpeed;
    m_OnGround = false;

    TransitionToState<PlayerStateJump>(game_container);
  }
  else if (m_State.Is<PlayerStateJump>())
  {
    auto jump_state = m_State.Get<PlayerStateJump>();

    if (jump_state->CanGraceJump())
    {
      m_Velocity.y += g_PlayerConfig->m_JumpSpeed;
      TransitionToState<PlayerStateJump>(game_container);
    }
  }

#endif
}
#endif

MoverResult PlayerServerObject::MoveCheckCollisionDatabase(GameLogicContainer & game_container)
{
  auto & stage = game_container.GetStage();
  auto & collision = game_container.GetSystems().GetCollisionDatabase();

  auto move_box = g_PlayerSprite->GetSingleBox(COMPILE_TIME_CRC32_STR("MoveBox"));
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

void PlayerServerObject::MoveCheckIntersectionDatabase(GameLogicContainer & game_container, GameNetVal player_radius, GameNetVal move_threshold)
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

bool PlayerServerObject::FrameAdvance(uint32_t anim_name_hash, bool loop, int frames)
{
  AnimationState state;
  state.m_AnimIndex = m_AnimIndex;
  state.m_AnimFrame = m_AnimFrame;
  state.m_AnimDelay = m_AnimDelay;

  auto result = g_PlayerSprite->FrameAdvance(anim_name_hash, state, loop, frames);
  m_AnimIndex = state.m_AnimIndex;
  m_AnimFrame = state.m_AnimFrame;
  m_AnimDelay = state.m_AnimDelay;

  return result;
}

bool PlayerServerObject::HandlePlaceholderEvent(PlaceholderEvent & ev, const EventMetaData & meta)
{
  return true;
}

czstr PlayerServerObject::GetDefaultEntityBinding()
{
  return "./Entities/Player.entity";
}

SpriteResource & PlayerServerObject::GetSprite()
{
  return *g_PlayerSprite.GetResource();
}
