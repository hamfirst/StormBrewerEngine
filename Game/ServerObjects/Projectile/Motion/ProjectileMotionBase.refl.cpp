
#include "Game/GameCommon.h"
#include "Game/ServerObjects/Projectile/Motion/ProjectileMotionBase.refl.meta.h"

#include "Runtime/ServerObject/ServerObjectComponentSerialize.h"

STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(ProjectileMotionBaseConfig);
NET_REGISTER_BASE_TYPE(ProjectileMotionBase);


void ProjectileMotionBase::Init(ProjectileServerObject & proj, GameLogicContainer & game_container)
{

}

void ProjectileMotionBase::Update(ProjectileServerObject & proj, GameLogicContainer & game_container)
{

}


