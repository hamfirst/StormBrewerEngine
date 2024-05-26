
#include "Game/GameCommon.h"

#include "GameShared/GameWorld.h"
#include "Game/NetworkEvents/GameServerEventSender.h"
#include "Game/Stage/GameStage.h"

#include "Game/ServerObjects/Player/PlayerServerObject.refl.h"

#include "Game/ServerObjects/Player/States/PlayerStateIdle.refl.h"
#include "Game/ServerObjects/Player/States/PlayerStateIdle.refl.meta.h"

#include "Game/ServerObjects/Player/States/PlayerStateMoving.refl.h"
#include "Game/ServerObjects/Player/States/PlayerStateJump.refl.h"
#include "Game/ServerObjects/Player/States/PlayerStateBasicAttack.refl.h"

#include "Runtime/Entity/EntityResource.h"

#include "StormNet/NetReflectionTypeDatabase.h"

NET_REGISTER_TYPE(PlayerStateIdle, PlayerStateBase);

void PlayerStateIdle::Move(PlayerServerObject & player, GameWorld & world)
{
#ifndef PLATFORMER_MOVEMENT

  player.m_Velocity.x = 0;
  player.m_Velocity.y = 0;

#else

  player.m_Velocity.x = 0;
  player.m_Velocity.y -= player.GetConfig()->m_Gravity;

  player.MoveCheckCollisionDatabase(world);

#endif

}

void PlayerStateIdle::Transition(PlayerServerObject & player, GameWorld & world)
{
#ifdef NET_USE_ROUND_TIMER
  if (world.GetInstanceData().m_RoundState == RoundState::kPreRound)
  {
    return;
  }
#endif

#ifndef PLATFORMER_MOVEMENT

  if (player.m_Input.m_InputStr > GameNetVal(0))
  {
    player.TransitionToState<PlayerStateMoving>(world);
  }

#else

#ifdef PLAYER_ENABLE_JUMP

  if (player.m_OnGround == false)
  {
    auto jump_state = player.TransitionToState<PlayerStateJump>(world);
    if (jump_state)
    {
      jump_state->AllowGraceJump();
    }

    return;
  }

#endif

  if (player.m_Input.m_XInput != GameNetVal(0))
  {
    player.TransitionToState<PlayerStateMoving>(world);
    return;
  }

#endif
}

void PlayerStateIdle::Animate(PlayerServerObject & player, GameWorld & world)
{
#ifndef PLATFORMER_MOVEMENT
  switch ((CharacterFacing)player.m_Facing)
  {
  case CharacterFacing::kLeft:
  case CharacterFacing::kRight:
    player.FrameAdvance(COMPILE_TIME_CRC32_STR("Side_Idle"));
    break;
  case CharacterFacing::kUp:
    player.FrameAdvance(COMPILE_TIME_CRC32_STR("Up_Idle"));
    break;
  case CharacterFacing::kDown:
    player.FrameAdvance(COMPILE_TIME_CRC32_STR("Down_Idle"));
    break;
  }
#else

  player.FrameAdvance(COMPILE_TIME_CRC32_STR("Idle"));

#endif

  player.TriggerAnimationEvents(world, *this);
}

