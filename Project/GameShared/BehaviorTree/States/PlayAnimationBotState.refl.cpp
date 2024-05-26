
#include "GameShared/BehaviorTree/States/PlayAnimationBotState.refl.meta.h"

PlayAnimationBotState::PlayAnimationBotState(uint32_t animation_hash) :
  m_AnimationHash(animation_hash)
{
  
}

void PlayAnimationBotState::Activate(BotServerObject & bot, GameWorld & container)
{
  bot.ResetAnimState();
}

bool PlayAnimationBotState::Update(BotServerObject & bot, GameWorld & container)
{
  if(bot.FrameAdvance(m_AnimationHash, false))
  {
    return true;
  }

  return false;
}
