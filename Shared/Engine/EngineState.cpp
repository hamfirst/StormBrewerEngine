
#include "Engine/EngineCommon.h"
#include "Engine/EngineState.h"

#include "Engine/Entity/EntitySystem.h"
#include "Engine/Component/ComponentSystem.h"
#include "Engine/Map/MapSystem.h"
#include "Engine/VisualEffect/VisualEffectManager.h"
#include "Engine/UI/UIManager.h"

#include "Runtime/Map/MapResource.h"

EngineState::EngineState(NotNullPtr<GameContainer> game, Window & window) :
  m_EntitySystem(std::make_unique<EntitySystem>(this, game)),
  m_ComponentSystem(std::make_unique<ComponentSystem>()),
  m_MapSystem(std::make_unique<MapSystem>(this)),
  m_VisualEffectManager(std::make_unique<VisualEffectManager>()),
  m_UIManager(std::make_unique<UIManager>(window))
{

}

EngineState::~EngineState()
{
  m_MapSystem->UnloadAllMaps();
}

NotNullPtr<Entity> EngineState::CreateEntity()
{
  return m_EntitySystem->CreateEntity(true);
}

NotNullPtr<Entity> EngineState::CreateEntity(NotNullPtr<EntityResource> resource,
        NullOptPtr<const ServerObject> server_object, NullOptPtr<const ServerObjectManager> obj_manager, bool activate)
{
  return m_EntitySystem->CreateEntity(resource, server_object, obj_manager, activate);
}

void EngineState::DestroyAllEntities()
{
  return m_EntitySystem->DestroyAllEntities();
}

void EngineState::DestroyAllGameplayObjects()
{
  m_EntitySystem->DestroyAllEntities();
  m_VisualEffectManager->DestroyAllEffects();
  m_MapSystem->UnloadAllMaps();
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

NotNullPtr<UIManager> EngineState::GetUIManager()
{
  return m_UIManager.get();
}
