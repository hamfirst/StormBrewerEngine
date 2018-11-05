
#pragma once

#include "Game/ServerObjects/Projectile/Motion/ProjectileMotionBase.refl.h"


struct ProjectileMotionLinearConfig : public ProjectileMotionBaseConfig
{
  STORM_DATA_DEFAULT_CONSTRUCTION_DERIVED(ProjectileMotionLinearConfig);

  RDeterministicFloat<GameNetVal> m_Speed;
};

class ProjectileMotionLinear : public ProjectileMotionBase
{
public:
  NET_REFL;

  void Init(ProjectileServerObject & proj, GameLogicContainer & game_container) override;
  void Update(ProjectileServerObject & proj, GameLogicContainer & game_container) override;

public:

  GameNetVal m_RangeRemaining;
};
