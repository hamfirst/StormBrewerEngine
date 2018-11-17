
#include "Game/GameCommon.h"

#include "Game/GameController.refl.h"
#include "Game/GameServerEventSender.h"

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

void ProjectileServerObject::Init(const ProjectileServerObjectInitData & init_data, GameLogicContainer & game_container)
{
  m_Position = init_data.m_SpawnData.m_Position;
  m_Direction = init_data.m_SpawnData.m_Direction;
  m_Team = init_data.m_SpawnData.m_TeamIndex;
  m_Owner = init_data.m_SpawnData.m_OwnerHandle;

  m_Config.SetTo(*init_data.m_SpawnData.m_Config);
}

void ProjectileServerObject::UpdateFirst(GameLogicContainer & game_container)
{
  GameServerObjectBase::UpdateFirst(game_container);
}

void ProjectileServerObject::UpdateMiddle(GameLogicContainer & game_container)
{
  if(m_Motion)
  {
    m_Motion->Update(*this, game_container);
  }
}

void ProjectileServerObject::HandleImpact(NullOptPtr<CollisionDatabaseTraceResult> collision_result, GameLogicContainer & game_container)
{
  if(m_Response)
  {
    m_Response->HandleImpact(collision_result, *this, game_container);
  }
  else
  {
    Destroy(game_container.GetObjectManager());
  }
}

void ProjectileServerObject::HandleRangeExpired(GameLogicContainer & game_container)
{
  if(m_Response)
  {
    m_Response->HandleRangeExpired(*this, game_container);
  }
  else
  {
    Destroy(game_container.GetObjectManager());
  }
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

  if(ptr->m_Motion)
  {
    ptr->m_Motion->Init(*ptr, game_container);
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

Optional<int> ProjectileServerObject::GetAssociatedPlayer(GameLogicContainer & game_container) const
{
  auto owner = m_Owner.Resolve(game_container.GetObjectManager());
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
