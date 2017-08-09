
#include "Engine/EngineCommon.h"
#include "Engine/EngineState.h"

#include "Engine/Entity/EntitySystem.h"
#include "Engine/Component/ComponentSystem.h"
#include "Engine/Map/MapSystem.h"

#include "Runtime/Collision/CollisionSystem.h"
#include "Runtime/Map/MapResource.h"

EngineState::EngineState(NotNullPtr<GameContainer> game) :
  m_CollisionSystem(std::make_unique<CollisionSystem>()),
  m_EntitySystem(std::make_unique<EntitySystem>(this, game)),
  m_ComponentSystem(std::make_unique<ComponentSystem>()),
  m_MapSystem(std::make_unique<MapSystem>(this))
{

}

EngineState::~EngineState()
{

}

NotNullPtr<Entity> EngineState::CreateEntity()
{
  return m_EntitySystem->CreateEntity(true);
}

NotNullPtr<Entity> EngineState::CreateEntity(NotNullPtr<EntityResource> resource, NullOptPtr<ServerObject> server_object)
{
  return m_EntitySystem->CreateEntity(resource, server_object, true);
}

void EngineState::DestroyAllEntities()
{
  return m_EntitySystem->DestroyAllEntities();
}

std::size_t EngineState::LoadMap(NotNullPtr<MapResource> map)
{
  return m_MapSystem->InstantiateMap(*map->GetData());
}

NullOptPtr<MapInstance> EngineState::GetMapInstance(std::size_t map_id)
{
  return m_MapSystem->GetMapInstance(map_id);
}

void EngineState::UnloadMap(std::size_t map_id)
{
  m_MapSystem->UnloadMap(map_id);
}

uint32_t EngineState::CheckCollision(const Box & box, uint32_t collision_layer_mask)
{
  return m_CollisionSystem->CheckCollision(box, collision_layer_mask);
}

uint32_t EngineState::CheckCollisionAny(const Box & box, uint32_t collision_layer_mask)
{
  return m_CollisionSystem->CheckCollisionAny(box, collision_layer_mask);
}

NotNullPtr<CollisionSystem> EngineState::GetCollisionSystem()
{
  return m_CollisionSystem.get();
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
