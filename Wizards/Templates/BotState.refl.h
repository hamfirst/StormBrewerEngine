#pragma once

#include ""StormNet/NetReflectionStruct.h""
#include ""StormNet/NetReflectionTypeDatabase.h""

#include ""Game/ServerObjects/Bot/States/BotStateBase.refl.h""

class {class_name} : public BotStateBase, public BotStateEventHandler<{class_name}>
{{
public:
  NET_REFL;

  virtual void Move(BotServerObject & Bot, GameLogicContainer & game_container) override;
  virtual void Transition(BotServerObject & Bot, GameLogicContainer & game_container) override;
  virtual void Animate(BotServerObject & Bot, GameLogicContainer & game_container) override;

public:
  // Serialized variables
}};
