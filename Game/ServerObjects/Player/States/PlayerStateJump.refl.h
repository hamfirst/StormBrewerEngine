
#pragma once

#define PLAYER_ENABLE_JUMP

#ifdef PLAYER_ENABLE_JUMP

#include "StormNet/NetReflectionStruct.h"
#include "StormNet/NetReflectionTypeDatabase.h"

#include "Game/ServerObjects/Player/States/PlayerStateBase.refl.h"

class PlayerStateJump : public PlayerStateBase, public PlayerStateEventHandler<PlayerStateJump>
{
public:
  NET_REFL;

  virtual void Move(PlayerServerObject & player, GameLogicContainer & game_container) override;
  virtual void Transition(PlayerServerObject & player, GameLogicContainer & game_container) override;
  virtual void Animate(PlayerServerObject & player, GameLogicContainer & game_container) override;

public:
  // Serialized variables
};

#endif