
#include "Game/GameCommon.h"

#include "Game/GameController/GameController.refl.h"
#include "Game/NetworkEvents/GameServerEventSender.h"

#include "Game/ServerObjects/Bot/BotServerObject.refl.h"
#include "Game/ServerObjects/Bot/BotServerObject.refl.meta.h"

#include "Runtime/Animation/AnimationState.h"

void BotServerObject::Init(const BotServerObjectInitData & init_data, GameWorld & world)
{

}

void BotServerObject::UpdateFirst(GameWorld & world)
{
  GameServerObjectBase::UpdateFirst(world);
}

void BotServerObject::UpdateMiddle(GameWorld & world)
{
  auto behavior_tree = GetBehaviorTree();

  if (behavior_tree)
  {
    while (true)
    {
      m_Retransition = false;
      behavior_tree->Update(*this, world, world.GetInstanceData().m_Random);

      if (m_Retransition == false)
      {
        break;
      }
    }
  }

  auto & sprite = GetSprite();

  if (sprite)
  {
    auto box = sprite->GetSingleBoxDefault(COMPILE_TIME_CRC32_STR("MoveBox")).Offset(m_Position);
    world.GetSystems().GetCVCPushSystem().SetCharacterCVCPosition(box, this);
  }
}

Optional<AnimationState> BotServerObject::GetAnimationState() const
{
  auto & sprite = GetSprite();

  if(sprite.GetResource())
  {
    AnimationState state;
    sprite->SyncFrameData(m_AnimIndex, m_AnimFrame, m_AnimDelay, state);
    return state;
  }

  return {};
}

void BotServerObject::SetAnimationState(const AnimationState & anim_state)
{
  m_AnimIndex = anim_state.m_AnimIndex;
  m_AnimFrame = anim_state.m_AnimFrame;
  m_AnimDelay = anim_state.m_AnimDelay;
}

void BotServerObject::RetransitionBT()
{
  m_Retransition = true;
}

NullOptPtr<BotBehaviorTree> BotServerObject::GetBehaviorTree()
{
  return nullptr;
}

Optional<CharacterFacing> BotServerObject::GetFacing() const
{
  return m_Facing.ToEnum();
}
