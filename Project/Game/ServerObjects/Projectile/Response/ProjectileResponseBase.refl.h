
#pragma once

#include "Game/GameCommon.h"
#include "Game/GameServerTypes.h"
#include "GameShared/GameLogicContainer.h"

#include "Runtime/Sprite/SpriteResource.h"
#include "Runtime/Config/ConfigResource.h"
#include "Runtime/ServerObject/ServerObjectComponent.h"

#include "StormNet/NetReflection.h"

class ProjectileServerObject;

struct ProjectileResponseBaseConfig
{
  STORM_DATA_DEFAULT_CONSTRUCTION(ProjectileResponseBaseConfig);
};

class ProjectileResponseBase : public ServerObjectComponentBase<ProjectileResponseBaseConfig>
{
public:
  NET_DECLARE_BASE_TYPE;
  NET_REFL;

  virtual void HandleImpact(NullOptPtr<CollisionDatabaseTraceResult> collision_result,
                            ProjectileServerObject & proj, GameLogicContainer & game_container);
  virtual void HandleRangeExpired(ProjectileServerObject & proj, GameLogicContainer & game_container);
};


