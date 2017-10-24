
#include "Game/GameCommon.h"

#include "Game/GameLogicContainer.h"
#include "Game/GameServerEventSender.h"
#include "Game/GameStage.h"

#include "Game/ServerObjects/Player/PlayerServerObject.refl.h"

#include "Game/ServerObjects/Player/States/PlayerStateDefault.refl.h"
#include "Game/ServerObjects/Player/States/PlayerStateDefault.refl.meta.h"

NET_REGISTER_BASE_TYPE(PlayerStateDefault);

static GameNetVal kGravity = GameNetVal("0.1");
static GameNetVal kGravityJumpReduce = GameNetVal("0.2");

void PlayerStateDefault::Update(PlayerServerObject & player, GameLogicContainer & game_container)
{
  player.m_Velocity.x = player.m_Input.m_XInput;
  player.m_Velocity.y -= kGravity;

  auto result = player.MoveCheckCollisionDatabase(game_container);

  if (result.m_HitBottom)
  {
  }
  else
  {
    if (player.m_Velocity.y > GameNetVal(0) && player.m_Input.m_JumpHeld == false)
    {
      player.m_Velocity.y -= kGravityJumpReduce;
    }
  }
}
