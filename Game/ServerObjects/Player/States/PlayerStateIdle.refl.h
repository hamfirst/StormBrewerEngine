#pragma once

#include "Game/ServerObjects/Player/States/PlayerStateBase.refl.h"

class PlayerStateIdle : public PlayerStateBase, public PlayerStateEventHandler<PlayerStateIdle>
{
public:
  NET_REFL;


  virtual void Move(PlayerServerObject & player, GameLogicContainer & game_container) override;
  virtual void Transition(PlayerServerObject & player, GameLogicContainer & game_container) override;
  virtual void Animate(PlayerServerObject & player, GameLogicContainer & game_container) override;

public:
};
