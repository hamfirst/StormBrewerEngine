
#include "Game/GameCommon.h"

#include "Game/GameLogicContainer.h"
#include "Game/GameServerEventSender.h"
#include "Game/GameStage.h"

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


void PlayerStateJump::Move(PlayerServerObject & player, GameLogicContainer & game_container)
{
  auto target_velocity = player.m_Input.m_XInput * g_PlayerConfig->m_MoveSpeed;
  if (player.m_Velocity.x < target_velocity)
  {
    player.m_Velocity.x += g_PlayerConfig->m_AirControlAccel;
    if (player.m_Velocity.x > target_velocity)
    {
      player.m_Velocity.x = target_velocity;
    }
  }
  else
  {
    player.m_Velocity.x -= g_PlayerConfig->m_AirControlAccel;
    if (player.m_Velocity.x < target_velocity)
    {
      player.m_Velocity.x = target_velocity;
    }
  }

  player.m_Velocity.y -= g_PlayerConfig->m_Gravity;

  player.MoveCheckCollisionDatabase(game_container);

  if (player.m_Velocity.y > GameNetVal(0) && player.m_Input.m_JumpHeld == false)
  {
    player.m_Velocity.y -= g_PlayerConfig->m_GravityJumpReduce;
  }
}

void PlayerStateJump::Transition(PlayerServerObject & player, GameLogicContainer & game_container)
{
  if (player.m_OnGround)
  {
    player.TransitionToState<PlayerStateIdle>(game_container);
  }
}

void PlayerStateJump::Animate(PlayerServerObject & player, GameLogicContainer & game_container)
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
    player.m_Facing = PlayerFacing::kLeft;
  }
  else if (player.m_Input.m_XInput > GameNetVal(0))
  {
    player.m_Facing = PlayerFacing::kRight;
  }

  player.TriggerAnimationEvents(game_container, *this);
}

#endif
