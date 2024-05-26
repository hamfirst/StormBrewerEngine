#pragma once

#include "Game/ServerObjects/Player/States/PlayerStateBase.refl.h"

class PlayerStateMoving : public PlayerStateBase, public PlayerStateEventHandler<PlayerStateMoving>
{
public:
  DECLARE_PLAYER_STATE;

  virtual void Move(PlayerServerObject & player, GameWorld & world) override;
  virtual void Transition(PlayerServerObject & player, GameWorld & world) override;
  virtual void Animate(PlayerServerObject & player, GameWorld & world) override;

public:
};

