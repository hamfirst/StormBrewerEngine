#pragma once

#include "Runtime/Event/Event.h"

#include "Game/GameplayEvents/DamageType.refl.h"
#include "Game/ServerObjects/CharacterFacing.refl.h"

struct DamageEvent
{
  DECLARE_EVENT(DamageEvent);

  int m_Amount;
  CharacterFacing m_Direction;
  int m_Source;
  uint32_t m_AttackId;

  DamageType m_DamageType;
};

