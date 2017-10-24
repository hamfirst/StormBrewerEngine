
#include "Engine/EngineCommon.h"
#include "Engine/EngineState.h"

#include "Engine/Entity/EntitySystem.h"
#include "Engine/Component/ComponentSystem.h"
#include "Engine/Map/MapSystem.h"
#include "Engine/VisualEffect/VisualEffectManager.h"

#include "Runtime/Map/MapResource.h"

EngineState::EngineState(NotNullPtr<GameContainer> game) :
  m_EntitySystem(std::make_unique<EntitySystem>(this, game)),
  m_ComponentSystem(std::make_unique<ComponentSystem>()),
  m_MapSystem(std::make_unique<MapSystem>(this)),
  m_VisualEffectManager(std::make_unique<VisualEffectManager>())
{

}

EngineState::~EngineState()
{

}

NotNullPtr<Entity> EngineState::CreateEntity()
{
  return m_EntitySystem->CreateEntity(true);
}

NotNullPtr<Entity> EngineState::CreateEntity(NotNullPtr<EntityResource> resource, NullOptPtr<ServerObject> server_object, bool activate)
{
  return m_EntitySystem->CreateEntity(resource, server_object, activate);
}

void EngineState::DestroyAllEntities()
{
  return m_EntitySystem->DestroyAllEntities();
}

std::size_t EngineState::LoadMap(NotNullPtr<MapResource> map)
{
  return m_MapSystem->InstantiateMap(*map->GetData(), {});
}

NullOptPtr<MapInstance> EngineState::GetMapInstance(std::size_t map_id)
{
  return m_MapSystem->GetMapInstance(map_id);
}

void EngineState::UnloadMap(std::size_t map_id)
{
  m_MapSystem->UnloadMap(map_id);
}

NotNullPtr<EntitySystem> EngineState::GetEntitySystem()
{
  return m_EntitySystem.get();
}

NotNullPtr<ComponentSystem> EngineState::GetComponentSystem()
{
  return m_ComponentSystem.get();
}

NotNullPtr<MapSystem> EngineState::GetMapSystem()
{
  return m_MapSystem.get();
}

NotNullPtr<VisualEffectManager> EngineState::GetVisualEffectManager()
{
  return m_VisualEffectManager.get();
}
