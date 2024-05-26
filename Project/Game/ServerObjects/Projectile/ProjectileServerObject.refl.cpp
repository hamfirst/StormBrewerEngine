
#include "Game/GameCommon.h"

#include "Game/GameController/GameController.refl.h"
#include "Game/NetworkEvents/GameServerEventSender.h"

#include "Game/ServerObjects/Projectile/ProjectileServerObject.refl.h"
#include "Game/ServerObjects/Projectile/ProjectileServerObject.refl.meta.h"

#include "Runtime/Entity/EntityResource.h"
#include "Runtime/Sprite/SpriteResource.h"

struct ProjectileServerObjectConfigResources
{
  EntityResourcePtr m_ProjectileEntity;
};

void ProjectileConfigResourcesLoad(const ConfigPtr<ProjectileConfig> & config, ProjectileServerObjectConfigResources & resources)
{
  ServerObjectComponent<ProjectileMotionBase, ProjectileMotionBaseConfig>::RegisterConfigType(
          config.GetResource()->GetFileName(), config->m_MotionConfig);
  ServerObjectComponent<ProjectileResponseBase, ProjectileResponseBaseConfig>::RegisterConfigType(
          config.GetResource()->GetFileName(), config->m_ResponseConfig);

  resources.m_ProjectileEntity = g_GlobalAssetList.CreateDependentAsset<EntityResource>(config->m_EntityFile.c_str());
}

GLOBAL_ASSET_DIRECTORY(ConfigPtr<ProjectileConfig>, g_ProjectileConfigs, "./Configs", "projectileconfig");
GLOBAL_DEPENDENT_ASSET_ARRAY(ProjectileServerObjectConfigResources, g_ProjectileConfigInfo, g_ProjectileConfigs, ProjectileConfigResourcesLoad);

void ProjectileServerObject::Init(const ProjectileServerObjectInitData & init_data, GameWorld & world)
{
  m_Position = init_data.m_SpawnData.m_Position;
  m_Direction = init_data.m_SpawnData.m_Direction;
  m_Team = init_data.m_SpawnData.m_TeamIndex;
  m_Owner = init_data.m_SpawnData.m_OwnerHandle;

  m_Config.SetTo(*init_data.m_SpawnData.m_Config);
}

void ProjectileServerObject::UpdateFirst(GameWorld & world)
{
  GameServerObjectBase::UpdateFirst(world);
}

void ProjectileServerObject::UpdateMiddle(GameWorld & world)
{
  if(m_Motion)
  {
    m_Motion->Update(*this, world);
  }
}

void ProjectileServerObject::HandleImpact(NullOptPtr<CollisionDatabaseTraceResult> collision_result, GameWorld & world)
{
  if(m_Response)
  {
    m_Response->HandleImpact(collision_result, *this, world);
  }
  else
  {
    Destroy(world.GetObjectManager());
  }
}

void ProjectileServerObject::HandleRangeExpired(GameWorld & world)
{
  if(m_Response)
  {
    m_Response->HandleRangeExpired(*this, world);
  }
  else
  {
    Destroy(world.GetObjectManager());
  }
}

NotNullPtr<ProjectileServerObject> ProjectileServerObject::SpawnProjectile(const GameNetVec2 & pos,
                                                                           const GameNetVec2 & dir, int team_index, const ServerObjectHandle & owner_handle,
                                                                           const ConfigPtr<ProjectileConfig> & config, GameWorld & world)
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
    ptr = world.GetObjectManager().CreateUnsyncedDynamicObject<ProjectileServerObject>(world, &init_data);
  }
  else
  {
    ptr = world.GetObjectManager().CreateDynamicObject<ProjectileServerObject>(world, &init_data);
  }

  if(ptr->m_Motion)
  {
    ptr->m_Motion->Init(*ptr, world);
  }

  return ptr;
}

czstr ProjectileServerObject::GetEntityBinding() const
{
  return m_Config->m_EntityFile.c_str();
}

czstr ProjectileServerObject::GetDefaultEntityBinding() const
{
  static ProjectileConfig config;
  return config.m_EntityFile.c_str();
}

Optional<int> ProjectileServerObject::GetAssociatedPlayer(GameWorld & world) const
{
  auto owner = m_Owner.Resolve(world.GetObjectManager());
  if(owner)
  {
    return owner->GetSlotIndex();
  }

  return {};
}

void ProjectileServerObject::InitStaticComponents()
{
  m_Motion.SetFromConfig(m_Config->m_MotionConfig.GetValue());
  m_Response.SetFromConfig(m_Config->m_ResponseConfig.GetValue());
}
