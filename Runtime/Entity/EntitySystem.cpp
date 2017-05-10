
#include "Runtime/RuntimeCommon.h"

#include "Foundation/SkipField/SkipField.h"

#include "Runtime/Entity/EntitySystem.h"
#include "Runtime/Entity/Entity.h"
#include "Runtime/Entity/EntityResource.h"
#include "Runtime/Entity/EntityDef.refl.h"

#include "Runtime/RuntimeState.h"
#include "Runtime/Component/ComponentSystem.h"
#include "Runtime/Sprite/SpriteResource.h"
#include "Runtime/Event/EventSystem.h"



SkipField<Entity> s_EntityAllocator;

EntitySystem::EntitySystem(NotNullPtr<RuntimeState> runtime_state) :
  m_RuntimeState(runtime_state),
  m_EventSystem(std::make_unique<EventSystem>())
{
  m_EntityAllocator = new SkipField<Entity>();
}

EntitySystem::~EntitySystem()
{
  auto allocator = static_cast<SkipField<Entity> *>(m_EntityAllocator);
  delete allocator;
}

NotNullPtr<Entity> EntitySystem::CreateEntity(bool activate)
{
  auto allocator = static_cast<SkipField<Entity> *>(m_EntityAllocator);
  auto ptr = allocator->Allocate(m_RuntimeState, m_EventSystem.get());

  if (activate)
  {
    ptr->Activate();
  }

  return ptr;
}

NotNullPtr<Entity> EntitySystem::CreateEntity(NotNullPtr<EntityDef> entity_def, bool activate)
{
  auto allocator = static_cast<SkipField<Entity> *>(m_EntityAllocator);
  auto ptr = allocator->Allocate(m_RuntimeState, m_EventSystem.get());

  if (entity_def->m_Sprite.length() > 0)
  {
    ptr->m_Sprite = SpriteResource::Load(entity_def->m_Sprite.data());
  }

  AddComponentsToEntity(entity_def, ptr);

  if (activate)
  {
    ptr->Activate();
  }

  return ptr;
}

NotNullPtr<Entity> EntitySystem::CreateEntity(NotNullPtr<EntityResource> entity_resource, bool activate)
{
  auto allocator = static_cast<SkipField<Entity> *>(m_EntityAllocator);
  auto ptr = allocator->Allocate(m_RuntimeState, m_EventSystem.get());

  ptr->m_Sprite = entity_resource->m_Sprite;
  AddComponentsToEntity(entity_resource->GetData(), ptr);

  if (activate)
  {
    ptr->Activate();
  }

  return ptr;
}

void EntitySystem::AddComponentsToEntity(NotNullPtr<EntityDef> entity_def, NotNullPtr<Entity> entity)
{
  for (auto & elem : entity_def->m_Components)
  {
    auto & init_data = elem.second;
    if (init_data.GetValue() == nullptr)
    {
      continue;
    }

    auto comp = m_RuntimeState->m_ComponentSystem->CreateComponentFromTypeNameHash(init_data.GetTypeNameHash(), init_data.GetValue());
    if (comp == nullptr)
    {
      continue;
    }

    entity->AddComponentInternal(comp);
  }
}

void EntitySystem::DestroyEntity(NotNullPtr<Entity> entity)
{
  auto allocator = static_cast<SkipField<Entity> *>(m_EntityAllocator);
  allocator->Release(entity);
}

NullOptPtr<Entity> EntitySystem::ResolveHandle(const EntityHandle & handle)
{
  auto allocator = static_cast<SkipField<Entity> *>(m_EntityAllocator);
  return allocator->ResolveHandle(handle);
}

void EntitySystem::FindAllEntitiesWithName(czstr name, std::vector<NotNullPtr<Entity>> & outp_entities)
{
  auto allocator = static_cast<SkipField<Entity> *>(m_EntityAllocator);
  allocator->VisitAll([&](Entity & entity) {
    if (entity.GetName() == name)
    {
      outp_entities.push_back(&entity);
    }
  });
}

void EntitySystem::DestroyAllEntities()
{
  auto allocator = static_cast<SkipField<Entity> *>(m_EntityAllocator);
  allocator->VisitAll([](Entity & entity) {
    entity.Destroy();
  });
}


void EntitySystem::FinalizeEvents()
{
  m_EventSystem->FinalizeEvents();
}
