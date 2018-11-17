
#pragma once

#include "Game/GameCommon.h"
#include "Game/GameplayEvents/DamageType.refl.h"

#include "Game/ServerObjects/CharacterFacing.refl.h"

#include "Runtime/SpriteBase/SpriteAnimationEventDef.refl.h"

struct DealDamageAnimationEvent : public SpriteAnimationEventDataBase
{
public:
  STORM_DATA_DEFAULT_CONSTRUCTION_DERIVED(DealDamageAnimationEvent);

  static uint32_t TypeNameHash;

  RInt m_Amount = 20;

  REnum<CharacterFacing> m_Direction;
  REnum<DamageType> m_DamageType;
};
