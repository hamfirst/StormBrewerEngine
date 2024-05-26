#pragma once

#include ""StormNet/NetReflectionStruct.h""
#include ""StormNet/NetReflectionTypeDatabase.h""

#include ""Game/ServerObjects/Bot/States/BotStateBase.refl.h""

class {class_name} : public BotStateBase, public BotStateEventHandler<{class_name}>
{{
public:
  NET_REFL;

  virtual void Move(BotServerObject & Bot, GameLogicContainer & world) override;
  virtual void Transition(BotServerObject & Bot, GameLogicContainer & world) override;
  virtual void Animate(BotServerObject & Bot, GameLogicContainer & world) override;

public:
  // Serialized variables
}};
