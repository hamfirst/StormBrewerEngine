
#include "Runtime/RuntimeCommon.h"
#include "Runtime/RuntimeState.h"

#include "Runtime/Collision/CollisionSystem.h"
#include "Runtime/Entity/EntitySystem.h"
#include "Runtime/Component/ComponentSystem.h"
#include "Runtime/Map/MapSystem.h"
#include "Runtime/Map/MapResource.h"

RuntimeState::RuntimeState() :
  m_CollisionSystem(std::make_unique<CollisionSystem>(this)),
  m_EntitySystem(std::make_unique<EntitySystem>(this)),
  m_ComponentSystem(std::make_unique<ComponentSystem>()),
  m_MapSystem(std::make_unique<MapSystem>(this))
{

}

RuntimeState::~RuntimeState()
{

}

NotNullPtr<Entity> RuntimeState::CreateEntity()
{
  return m_EntitySystem->CreateEntity(true);
}

NotNullPtr<Entity> RuntimeState::CreateEntity(NotNullPtr<EntityResource> resource)
{
  return m_EntitySystem->CreateEntity(resource, true);
}

void RuntimeState::LoadMap(NotNullPtr<MapResource> map)
{
  m_MapSystem->InstantiateMap(*map->GetData());
}

uint32_t RuntimeState::CheckCollision(const Box & box, uint32_t collision_layer_mask)
{
  return m_CollisionSystem->CheckCollision(box, collision_layer_mask);
}

uint32_t RuntimeState::CheckCollisionAny(const Box & box, uint32_t collision_layer_mask)
{
  return m_CollisionSystem->CheckCollisionAny(box, collision_layer_mask);
}

void RuntimeState::CreateUpdateList(ComponentUpdateBucketList & bucket_list)
{
  m_ComponentSystem->CreateUpdateBucketList(bucket_list);
}

void RuntimeState::FinalizeEvents()
{
  m_EntitySystem->FinalizeEvents();
}
