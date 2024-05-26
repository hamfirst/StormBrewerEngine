#pragma once

#include ""StormNet/NetReflectionStruct.h""
#include ""StormNet/NetReflectionTypeDatabase.h""

#include ""Game/ServerObjects/Player/States/PlayerStateBase.refl.h""

class {class_name} : public PlayerStateBase, public PlayerStateEventHandler<{class_name}>
{{
public:
  DECLARE_PLAYER_STATE;

  virtual void Move(PlayerServerObject & player, GameLogicContainer & world) override;
  virtual void Transition(PlayerServerObject & player, GameLogicContainer & world) override;
  virtual void Animate(PlayerServerObject & player, GameLogicContainer & world) override;

public:
  // Serialized variables
}};
