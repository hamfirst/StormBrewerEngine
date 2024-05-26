
#include "Game/GameCommon.h"

#include "GameShared/GameWorld.h"
#include "Game/NetworkEvents/GameServerEventSender.h"
#include "Game/Stage/GameStage.h"

#include "Game/ServerObjects/Player/PlayerServerObject.refl.h"

#include "Game/ServerObjects/Player/States/PlayerStateJump.refl.h"
#include "Game/ServerObjects/Player/States/PlayerStateJump.refl.meta.h"

#include "Game/ServerObjects/Player/States/PlayerStateIdle.refl.h"

#include "StormNet/NetReflectionTypeDatabase.h"


#ifdef PLAYER_ENABLE_JUMP

NET_REGISTER_TYPE(PlayerStateJump, PlayerStateBase);

void PlayerStateJump::AllowGraceJump()
{
  m_JumpGraceFrames = 5;
}

bool PlayerStateJump::CanGraceJump() const
{
  return m_JumpGraceFrames > 0;
}


void PlayerStateJump::Move(PlayerServerObject & player, GameWorld & world)
{
  auto target_velocity = player.m_Input.m_XInput * player.GetConfig()->m_MoveSpeed;
  if (player.m_Velocity.x < target_velocity)
  {
    player.m_Velocity.x += player.GetConfig()->m_AirControlAccel;
    if (player.m_Velocity.x > target_velocity)
    {
      player.m_Velocity.x = target_velocity;
    }
  }
  else
  {
    player.m_Velocity.x -= player.GetConfig()->m_AirControlAccel;
    if (player.m_Velocity.x < target_velocity)
    {
      player.m_Velocity.x = target_velocity;
    }
  }

  player.m_Velocity.y -= player.GetConfig()->m_Gravity;

  player.MoveCheckCollisionDatabase(world);

  if (player.m_Velocity.y > GameNetVal(0) && player.m_Input.m_JumpHeld == false)
  {
    player.m_Velocity.y -= player.GetConfig()->m_GravityJumpReduce;
  }
}

void PlayerStateJump::Transition(PlayerServerObject & player, GameWorld & world)
{
  if (player.m_OnGround)
  {
    player.TransitionToState<PlayerStateIdle>(world);
  }
}

void PlayerStateJump::Animate(PlayerServerObject & player, GameWorld & world)
{
  if (player.m_Velocity.y >= GameNetVal(0))
  {
    player.FrameAdvance(COMPILE_TIME_CRC32_STR("Jump"), false);
  }
  else
  {
    player.FrameAdvance(COMPILE_TIME_CRC32_STR("Fall"), false);
  }

  if (player.m_Input.m_XInput < GameNetVal(0))
  {
    player.m_Facing = CharacterFacing::kLeft;
  }
  else if (player.m_Input.m_XInput > GameNetVal(0))
  {
    player.m_Facing = CharacterFacing::kRight;
  }

  player.TriggerAnimationEvents(world, *this);
}

#endif
