#pragma once

#include "Game/ServerObjects/Player/States/PlayerStateBase.refl.h"

class PlayerStateMoving : public PlayerStateBase, public PlayerStateEventHandler<PlayerStateMoving>
{
public:
  NET_REFL;

  virtual void Move(PlayerServerObject & player, GameLogicContainer & game_container) override;
  virtual void Transition(PlayerServerObject & player, GameLogicContainer & game_container) override;
  virtual void Animate(PlayerServerObject & player, GameLogicContainer & game_container) override;

public:
};
