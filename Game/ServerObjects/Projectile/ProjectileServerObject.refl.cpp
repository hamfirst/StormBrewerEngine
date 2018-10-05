
#include "Game/GameCommon.h"

#include "Game/GameController.refl.h"
#include "Game/GameServerEventSender.h"

#include "Game/ServerObjects/Projectile/ProjectileServerObject.refl.h"
#include "Game/ServerObjects/Projectile/ProjectileServerObject.refl.meta.h"

#include "Runtime/Entity/EntityResource.h"
#include "Runtime/Sprite/SpriteResource.h"

czstr g_ProjectileServerObjectEntityFile = "./Entities/Entity.entity";
GLOBAL_ASSET(EntityResourcePtr, g_ProjectileServerObjectEntityFile, g_ProjectileServerObjectEntity);

void ProjectileServerObject::Init(const ProjectileServerObjectInitData & init_data, GameLogicContainer & game_container)
{

}

void ProjectileServerObject::UpdateFirst(GameLogicContainer & game_container)
{

}

void ProjectileServerObject::UpdateMiddle(GameLogicContainer & game_container)
{

}

czstr ProjectileServerObject::GetDefaultEntityBinding() const
{
  return g_ProjectileServerObjectEntityFile;
}
