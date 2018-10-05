#pragma once

#include "Game/GameCommon.h"

#include "Game/GameLogicContainer.h"
#include "Game/GameServerEventSender.h"
#include "Game/GameStage.h"
#include "Game/Systems/GameLogicSystems.h"
#include "Game/ServerObjects/GameServerObjectBase.refl.h"
#include "Game/Configs/ProjectileConfig.refl.h"

#include "Runtime/Sprite/SpriteResource.h"
#include "Runtime/Config/ConfigResource.h"

#include "Runtime/ServerObject/ServerObject.h"
#include "Runtime/ServerObject/ServerObjectInitData.refl.h"
#include "Runtime/ServerObject/ServerObjectRegistrationMacros.h"

struct ProjectileServerObjectInitData : public GameServerObjectBaseInitData
{
  STORM_DATA_DEFAULT_CONSTRUCTION_DERIVED(ProjectileServerObjectInitData);
};

class ProjectileServerObject : public GameServerObjectBase
{
public:
  DECLARE_SERVER_OBJECT;

  ProjectileServerObject() = default;
  ProjectileServerObject(const ProjectileServerObject & rhs) = default;
  ProjectileServerObject(ProjectileServerObject && rhs) = default;

  ProjectileServerObject & operator = (const ProjectileServerObject & rhs) = default;
  ProjectileServerObject & operator = (ProjectileServerObject && rhs) = default;

  void Init(const ProjectileServerObjectInitData & init_data, GameLogicContainer & game_container);
  void UpdateFirst(GameLogicContainer & game_container);
  void UpdateMiddle(GameLogicContainer & game_container);

  static void SpawnProjectile(const GameNetVec2 & pos, const GameNetVec2 & dir, int owner_index,
          const ConfigPtr<ProjectileConfig> & config);

  virtual czstr GetDefaultEntityBinding() const override;
public:
  // Serialized variables
};
