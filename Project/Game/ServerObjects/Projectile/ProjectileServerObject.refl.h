#pragma once

#include "Game/GameCommon.h"

#include "GameShared/GameLogicContainer.h"
#include "GameShared/Systems/GameLogicSystems.h"

#include "Game/NetworkEvents/GameServerEventSender.h"
#include "Game/Stage/GameStage.h"
#include "Game/ServerObjects/GameServerObjectBase.refl.h"
#include "Game/ServerObjects/Projectile/Config/ProjectileConfig.refl.h"
#include "Game/ServerObjects/Projectile/Motion/ProjectileMotionBase.refl.h"

#include "Runtime/Asset/Asset.h"
#include "Runtime/Sprite/SpriteResource.h"
#include "Runtime/Config/ConfigResource.h"

#include "Runtime/ServerObject/ServerObject.h"
#include "Runtime/ServerObject/ServerObjectInitData.refl.h"
#include "Runtime/ServerObject/ServerObjectRegistrationMacros.h"
#include "Runtime/ServerObject/ServerObjectComponent.h"

EXTERN_GLOBAL_ASSET_ARRAY(ConfigPtr<ProjectileConfig>, g_ProjectileConfigs);
DECLARE_STATIC_LIST_TYPE(ProjectileConfigPtr, g_ProjectileConfigs);

struct ProjectileServerObjectSpawnData
{
  STORM_REFL;

  GameNetVec2 m_Position;
  GameNetVec2 m_Direction;
  int m_TeamIndex;
  ServerObjectHandle m_OwnerHandle;
  const ConfigPtr<ProjectileConfig> * m_Config;
};

struct ProjectileServerObjectInitData : public GameServerObjectBaseInitData
{
  STORM_DATA_DEFAULT_CONSTRUCTION_DERIVED(ProjectileServerObjectInitData);
  ProjectileServerObjectSpawnData STORM_REFL_IGNORE m_SpawnData;
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

  void HandleImpact(NullOptPtr<CollisionDatabaseTraceResult> collision_result, GameLogicContainer & game_container);
  void HandleRangeExpired(GameLogicContainer & game_container);

  static NotNullPtr<ProjectileServerObject> SpawnProjectile(const GameNetVec2 & pos, const GameNetVec2 & dir,
          int team_index, const ServerObjectHandle & handle,
          const ConfigPtr<ProjectileConfig> & config, GameLogicContainer & game_container);

  virtual czstr GetEntityBinding() const override;
  virtual czstr GetDefaultEntityBinding() const override;
  virtual Optional<int> GetAssociatedPlayer(GameLogicContainer & game_container) const override;
  virtual void InitStaticComponents() override;

public:

  GameNetVec2 m_Direction = {};
  NetRangedNumber<int, -1, kMaxTeams - 1> m_Team;
  ServerObjectHandle m_Owner;
  ProjectileConfigPtr m_Config;

  ServerObjectComponent<ProjectileMotionBase, ProjectileMotionBaseConfig> m_Motion;
  ServerObjectComponent<ProjectileResponseBase, ProjectileResponseBaseConfig> m_Response;
};
