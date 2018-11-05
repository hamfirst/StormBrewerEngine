
#include "Game/GameCommon.h"

#include "Game/GameController.refl.h"
#include "Game/GameServerEventSender.h"

#include "Game/ServerObjects/Projectile/ProjectileServerObject.refl.h"
#include "Game/ServerObjects/Projectile/ProjectileServerObject.refl.meta.h"

#include "Runtime/Entity/EntityResource.h"
#include "Runtime/Sprite/SpriteResource.h"

czstr g_ProjectileServerObjectEntityFile = "./Entities/Entity.entity";
GLOBAL_ASSET(EntityResourcePtr, g_ProjectileServerObjectEntityFile, g_ProjectileServerObjectEntity);

void ProjectileConfigResourcesLoad(const ConfigPtr<ProjectileConfig> & config, EmptyGlobalAssetInfo & resources)
{
  auto type_info = TypeDatabase<ProjectileMotionBaseConfig, ProjectileMotionBase>::Get().GetTypeInfo(
          config->m_MotionConfig.GetTypeNameHash());

  ServerObjectComponent<ProjectileMotionBase, ProjectileMotionBaseConfig>::RegisterConfigType(
          config.GetResource()->GetFileName(), config->m_MotionConfig.GetValue(), type_info->m_LogicTypeInfo);
}

GLOBAL_ASSET_DIRECTORY(ConfigPtr<ProjectileConfig>, g_ProjectileConfigs, "./Configs", ".projectileconfig");
GLOBAL_DEPENDENT_ASSET_ARRAY(EmptyGlobalAssetInfo, g_ProjectileConfigInfo, g_ProjectileConfigs, ProjectileConfigResourcesLoad);

void ProjectileServerObject::Init(const ProjectileServerObjectInitData & init_data, GameLogicContainer & game_container)
{
  m_Position = init_data.m_SpawnData.m_Position;
  m_Direction = init_data.m_SpawnData.m_Direction;
  m_Team = init_data.m_SpawnData.m_TeamIndex;
  m_Owner = init_data.m_SpawnData.m_OwnerHandle;
  m_Config = *init_data.m_SpawnData.m_Config;
}

void ProjectileServerObject::UpdateFirst(GameLogicContainer & game_container)
{
  GameServerObjectBase::UpdateFirst(game_container);
}

void ProjectileServerObject::UpdateMiddle(GameLogicContainer & game_container)
{
  m_Motion->Update(*this, game_container);
}

void ProjectileServerObject::HandleImpact(NullOptPtr<CollisionDatabaseTraceResult> collision_result)
{

}

void ProjectileServerObject::HandleRangeExpired()
{

}


NotNullPtr<ProjectileServerObject> ProjectileServerObject::SpawnProjectile(const GameNetVec2 & pos,
        const GameNetVec2 & dir, int team_index, const ServerObjectHandle & owner_handle,
        const ConfigPtr<ProjectileConfig> & config, GameLogicContainer & game_container)
{
  ProjectileServerObjectInitData init_data;
  init_data.m_SpawnData.m_Position = pos;
  init_data.m_SpawnData.m_Direction = dir;
  init_data.m_SpawnData.m_TeamIndex = team_index;
  init_data.m_SpawnData.m_OwnerHandle = owner_handle;
  init_data.m_SpawnData.m_Config = &config;

  NotNullPtr<ProjectileServerObject> ptr;
  if(config->m_Unsynced)
  {
    ptr = game_container.GetObjectManager().CreateUnsyncedDynamicObject<ProjectileServerObject>(game_container, &init_data);
  }
  else
  {
    ptr = game_container.GetObjectManager().CreateDynamicObject<ProjectileServerObject>(game_container, &init_data);
  }

  ptr->m_Motion->Init(*ptr, game_container);
  return ptr;
}

czstr ProjectileServerObject::GetDefaultEntityBinding() const
{
  return g_ProjectileServerObjectEntityFile;
}

void ProjectileServerObject::InitStaticComponents()
{
  m_Motion.SetFromConfig(m_Config->m_MotionConfig.GetValue());
}