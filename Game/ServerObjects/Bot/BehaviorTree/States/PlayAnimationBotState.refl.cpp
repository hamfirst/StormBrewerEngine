
#include "Game/ServerObjects/Bot/BehaviorTree/States/PlayAnimationBotState.refl.meta.h"

PlayAnimationBotState::PlayAnimationBotState(uint32_t animation_hash) :
  m_AnimationHash(animation_hash)
{
  
}

bool PlayAnimationBotState::Update(BotServerObject & bot, GameLogicContainer & container)
{
  if(bot.FrameAdvance(m_AnimationHash, false))
  {
    return true;
  }

  return false;
}
