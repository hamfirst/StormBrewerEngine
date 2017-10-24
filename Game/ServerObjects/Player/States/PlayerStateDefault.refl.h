#pragma once

#include <StormNet/NetReflectionStruct.h>
#include <StormNet/NetReflectionTypeDatabase.h>

#include "Game/ServerObjects/Player/States/PlayerStateBase.h"

class PlayerStateDefault : public PlayerStateBase
{
public:
  NET_REFL;
  NET_DECLARE_BASE_TYPE;

  virtual void Update(PlayerServerObject & player, GameLogicContainer & game_container) override;

public:
};
