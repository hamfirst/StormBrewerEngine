
#pragma once

#include "Game/GameCommon.h"
#include "Game/GameFullState.refl.h"

#include "Game/ServerObjects/Bot/BotServerObject.refl.h"

class PlayAnimationBotState
{
public:
  NET_REFL;
  STORM_REFL_NODEFAULT;

  explicit PlayAnimationBotState(uint32_t animation_hash);

  bool Update(BotServerObject & bot, GameLogicContainer & container);

private:
  uint32_t m_AnimationHash;
};

