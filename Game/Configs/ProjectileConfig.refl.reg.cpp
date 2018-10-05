#include "Game/GameCommon.h"
#include "Foundation/SkipField/SkipField.h"

#include "StormRefl/StormReflMetaFuncs.h"
#include "StormRefl/StormReflJsonStd.h"

#include "StormData/StormData.h"
#include "StormData/StormDataJson.h"

#include "Runtime/Config/ConfigRegistrationMacros.h"

#include "Game/Configs/ProjectileConfig.refl.h"
#include "Game/Configs/ProjectileConfig.refl.meta.h"

REGISTER_CONFIG_TYPE(ProjectileConfig, "Projectile Config", "projectileconfig", "Configs");
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(ProjectileConfig);
