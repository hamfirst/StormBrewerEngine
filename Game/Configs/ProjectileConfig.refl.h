#pragma once

#include "Game/GameCommon.h"
#include "Game/GameServerTypes.h"
#include "Game/ServerObjects/Projectile/Motion/ProjectileMotionBase.refl.h"
#include "Game/ServerObjects/Projectile/Response/ProjectileResponseBase.refl.h"

struct ProjectileConfig
{
public:
  STORM_DATA_DEFAULT_CONSTRUCTION(ProjectileConfig);

  RString STORM_REFL_ATTR_VAL(file, entity) m_EntityFile = "./Entities/DefaultProjectile.entity";

  RUInt m_MaxDistance = 200;
  RPolymorphic<ProjectileMotionBaseConfig, ProjectileMotionBase> m_MotionConfig;
  RPolymorphic<ProjectileResponseBaseConfig, ProjectileResponseBase> m_ResponseConfig;

  RBool m_Unsynced;
};
