#pragma once

#include "Game/GameCommon.h"

#include "Game/GameLogicContainer.h"
#include "Game/GameServerEventSender.h"
#include "Game/GameStage.h"
#include "Game/Systems/GameLogicSystems.h"
#include "Game/BehaviorTree/BehaviorTree.h"
#include "Game/ServerObjects/CharacterFacing.refl.h"
#include "Game/ServerObjects/GameServerObjectBase.refl.h"

#include "Runtime/Sprite/SpriteResource.h"
#include "Runtime/ServerObject/ServerObject.h"
#include "Runtime/ServerObject/ServerObjectInitData.refl.h"
#include "Runtime/ServerObject/ServerObjectRegistrationMacros.h"

struct BotServerObjectInitData : public GameServerObjectBaseInitData
{
  STORM_DATA_DEFAULT_CONSTRUCTION_DERIVED(BotServerObjectInitData);
};

class BotServerObject : public GameServerObjectBase
{
public:
  DECLARE_SERVER_OBJECT;

  BotServerObject() = default;
  BotServerObject(const BotServerObject & rhs) = default;
  BotServerObject(BotServerObject && rhs) = default;

  BotServerObject & operator = (const BotServerObject & rhs) = default;
  BotServerObject & operator = (BotServerObject && rhs) = default;

  void Init(const BotServerObjectInitData & init_data, GameLogicContainer & game_container);
  void UpdateFirst(GameLogicContainer & game_container);
  void UpdateMiddle(GameLogicContainer & game_container);

  virtual Optional<AnimationState> GetAnimationState() const override;
  virtual void SetAnimationState(const AnimationState & anim_state) override;

  virtual NullOptPtr<BotBehaviorTree> GetBehaviorTree();
  virtual Optional<CharacterFacing> GetFacing() const override;
  void RetransitionBT();

public:

  GameNetVec2 m_Velocity = {};

#ifdef PLATFORMER_MOVEMENT
  bool m_OnGround;
#endif

  NetRangedNumber<int, -1, 30> m_AnimIndex = -1;
  NetRangedNumber<int, 0, 31> m_AnimFrame = 0;
  NetRangedNumber<int, 0, 63> m_AnimDelay = 0;
  NetEnum<CharacterFacing> m_Facing = CharacterFacing::kRight;

private:
  bool m_Retransition = false;
};
