#pragma once

#include "Game/GameCommon.h"
#include "Game/GameServerTypes.h"
#include "Game/ServerObjects/Projectile/Motion/ProjectileMotionBase.refl.h"

struct ProjectileConfig
{
public:
  STORM_DATA_DEFAULT_CONSTRUCTION(ProjectileConfig);

  RUInt m_MaxDistance = 200;
  RPolymorphic<ProjectileMotionBaseConfig, ProjectileMotionBase> m_MotionConfig;

  RBool m_Unsynced;
};
