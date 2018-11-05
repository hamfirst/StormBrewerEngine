
#pragma once

#include "Game/GameCommon.h"
#include "Game/GameServerTypes.h"
#include "Game/GameLogicContainer.h"

#include "Runtime/Sprite/SpriteResource.h"
#include "Runtime/Config/ConfigResource.h"
#include "Runtime/ServerObject/ServerObjectComponent.h"

#include "StormNet/NetReflection.h"

class ProjectileServerObject;

struct ProjectileMotionBaseConfig
{
  STORM_DATA_DEFAULT_CONSTRUCTION(ProjectileMotionBaseConfig);
};

class ProjectileMotionBase : public ServerObjectComponentBase<ProjectileMotionBaseConfig>
{
public:
  NET_DECLARE_BASE_TYPE;
  NET_REFL;

  virtual void Init(ProjectileServerObject & proj, GameLogicContainer & game_container);
  virtual void Update(ProjectileServerObject & proj, GameLogicContainer & game_container);

};


