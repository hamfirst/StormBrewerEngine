
#include "Game/GameCommon.h"

#include "Game/GameLogicContainer.h"
#include "Game/GameServerEventSender.h"
#include "Game/GameStage.h"

#include "Game/ServerObjects/Player/PlayerServerObject.refl.h"
#include "Game/ServerObjects/Player/PlayerSettings.h"

#include "Game/ServerObjects/Player/States/PlayerStateMoving.refl.h"
#include "Game/ServerObjects/Player/States/PlayerStateMoving.refl.meta.h"

#include "Game/ServerObjects/Player/States/PlayerStateIdle.refl.h"
#include "Game/ServerObjects/Player/States/PlayerStateJump.refl.h"

#include "StormNet/NetReflectionTypeDatabase.h"

NET_REGISTER_TYPE(PlayerStateMoving, PlayerStateBase);

void PlayerStateMoving::Move(PlayerServerObject & player, GameLogicContainer & game_container)
{
#ifndef PLATFORMER_MOVEMENT

  auto move_str = player.m_Input.m_InputStr * kMoveSpeed;
  player.m_Velocity.x = GameNetLUT::Cos(player.m_Input.m_InputAngle) * move_str;
  player.m_Velocity.y = GameNetLUT::Sin(player.m_Input.m_InputAngle) * move_str;

  auto result = player.MoveCheckCollisionDatabase(game_container);

#else

  player.m_Velocity.x = player.m_Input.m_XInput * kMoveSpeed;
  player.m_Velocity.y -= kGravity;

  player.MoveCheckCollisionDatabase(game_container);

#endif
}

void PlayerStateMoving::Transition(PlayerServerObject & player, GameLogicContainer & game_container)
{
#ifndef PLATFORMER_MOVEMENT

  if (player.m_Input.m_InputStr == GameNetVal(0))
  {
    player.TransitionToState<PlayerStateIdle>(game_container);
  }

#else

#ifdef  PLAYER_ENABLE_JUMP

  if (player.m_OnGround == false)
  {
    player.TransitionToState<PlayerStateIdle>(game_container);
    return;
  }

#endif

  if (player.m_Input.m_XInput == GameNetVal(0))
  {
    player.TransitionToState<PlayerStateIdle>(game_container);
  }

#endif
}


void PlayerStateMoving::Animate(PlayerServerObject & player, GameLogicContainer & game_container)
{
#ifndef PLATFORMER_MOVEMENT

  auto abs_x = player.m_Velocity.x.Abs();
  auto abs_y = player.m_Velocity.y.Abs();

  if (abs_x < abs_y)
  {
    if (player.m_Velocity.y > GameNetVal(0))
    {
      player.m_Facing = PlayerFacing::kUp;
    }
    else
    {
      player.m_Facing = PlayerFacing::kDown;
    }
  }
  else if (abs_x > abs_y)
  {
    if (player.m_Velocity.x > GameNetVal(0))
    {
      player.m_Facing = PlayerFacing::kRight;
    }
    else
    {
      player.m_Facing = PlayerFacing::kLeft;
    }
  }

  switch ((PlayerFacing)player.m_Facing)
  {
  case PlayerFacing::kLeft:
  case PlayerFacing::kRight:
    player.FrameAdvance(COMPILE_TIME_CRC32_STR("Side_Move"));
    break;
  case PlayerFacing::kUp:
    player.FrameAdvance(COMPILE_TIME_CRC32_STR("Up_Move"));
    break;
  case PlayerFacing::kDown:
    player.FrameAdvance(COMPILE_TIME_CRC32_STR("Down_Move"));
    break;
  }

#else

  if (player.m_Input.m_XInput < GameNetVal(0))
  {
    player.m_Facing = PlayerFacing::kLeft;
  }
  else
  {
    player.m_Facing = PlayerFacing::kRight;
  }

  player.FrameAdvance(COMPILE_TIME_CRC32_STR("Run"));

#endif

  player.TriggerAnimationEvents(game_container, *this);
}
