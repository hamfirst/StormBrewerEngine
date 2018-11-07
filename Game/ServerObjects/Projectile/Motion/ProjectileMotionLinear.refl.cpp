
#include <ServerObjects/Projectile/ProjectileServerObject.refl.h>
#include "Game/ServerObjects/Projectile/Motion/ProjectileMotionLinear.refl.meta.h"

STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(ProjectileMotionLinearConfig);
REGISTER_LOGIC_TYPE(ProjectileMotionLinearConfig, ProjectileMotionBaseConfig, ProjectileMotionLinear, ProjectileMotionBase);

NET_REGISTER_TYPE(ProjectileMotionLinear, ProjectileMotionBase);


void ProjectileMotionLinear::Init(ProjectileServerObject & proj, GameLogicContainer & game_container)
{
  m_RangeRemaining = GameNetVal((int)proj.m_Config->m_MaxDistance);
}

void ProjectileMotionLinear::Update(ProjectileServerObject & proj, GameLogicContainer & game_container)
{
  auto config = GetConfigAs<ProjectileMotionLinearConfig>();
  if(config == nullptr)
  {
    ASSERT(false, "Could not cast config");
    return;
  }

  auto new_pos = proj.m_Position + proj.m_Direction * (GameNetVal) config->m_Speed;

  auto owner = proj.m_Owner.ResolveTo<GameServerObjectBase>(game_container.GetObjectManager());
  if(owner && owner->GetCollisionId())
  {
    CollisionObjectMask coll_mask;
    coll_mask.Set(owner->GetCollisionId().Value());

    auto result = game_container.GetSystems().GetCollisionDatabase().TracePath(
            proj.m_Position, new_pos, 0xFFFFFFFF, &coll_mask);

    if (result)
    {
      proj.HandleImpact(&result.Value(), game_container);
      return;
    }
  }
  else
  {
    auto result = game_container.GetSystems().GetCollisionDatabase().TracePath(proj.m_Position, new_pos, 0xFFFFFFFF);

    if (result)
    {
      proj.HandleImpact(&result.Value(), game_container);
      return;
    }
  }

  proj.m_Position = new_pos;

  m_RangeRemaining -= (GameNetVal)config->m_Speed;
  if(m_RangeRemaining < GameNetVal(0))
  {
    proj.HandleRangeExpired(game_container);
    return;
  }
}
