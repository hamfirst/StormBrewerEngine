
#include "Game/GameCommon.h"

#include "Game/GameLogicContainer.h"
#include "Game/GameServerEventSender.h"
#include "Game/GameStage.h"

#include "Game/ServerObjects/Player/PlayerServerObject.refl.h"
#include "Game/ServerObjects/Player/PlayerSettings.h"

#include "Game/ServerObjects/Player/States/PlayerStateJump.refl.h"
#include "Game/ServerObjects/Player/States/PlayerStateJump.refl.meta.h"

#include "Game/ServerObjects/Player/States/PlayerStateIdle.refl.h"

#include "StormNet/NetReflectionTypeDatabase.h"


#ifdef PLAYER_ENABLE_JUMP

NET_REGISTER_TYPE(PlayerStateJump, PlayerStateBase);

void PlayerStateJump::Move(PlayerServerObject & player, GameLogicContainer & game_container)
{
  player.m_Velocity.x = player.m_Input.m_XInput * kMoveSpeed;
  player.m_Velocity.y -= kGravity;

  player.MoveCheckCollisionDatabase(game_container);

  if (player.m_Velocity.y > GameNetVal(0) && player.m_Input.m_JumpHeld == false)
  {
    player.m_Velocity.y -= kGravityJumpReduce;
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
    player.FrameAdvance(COMPILE_TIME_CRC32_STR("Jump"));
  }
  else
  {
    player.FrameAdvance(COMPILE_TIME_CRC32_STR("Fall"));
  }

  player.TriggerAnimationEvents(game_container, *this);
}

#endif
