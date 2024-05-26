
#pragma once

#include "GameShared/GameSharedCommon.h"
#include "Game/State/GameFullState.refl.h"

#include "Game/ServerObjects/Bot/BotServerObject.refl.h"


class PlayAnimationBotState
{
public:
  NET_REFL;
  STORM_REFL_NODEFAULT;

  explicit PlayAnimationBotState(uint32_t animation_hash);

  void Activate(BotServerObject & bot, GameWorld & container);
  bool Update(BotServerObject & bot, GameWorld & container);

private:
  uint32_t m_AnimationHash;
};

