#pragma once

class Entity;
class EntityResource;
class EventSystem;
class RuntimeState;
struct EntityDef;

#include "Runtime/Entity/EntityHandle.h"

class RUNTIME_EXPORT EntitySystem
{
public:

  EntitySystem(NotNullPtr<RuntimeState> runtime_state);
  ~EntitySystem();

  NullOptPtr<Entity> ResolveHandle(const EntityHandle & handle);

  void FindAllEntitiesWithName(czstr name, std::vector<NotNullPtr<Entity>> & outp_entities);
  void DestroyAllEntities();

  void FinalizeEvents();

private:

  friend class Entity;
  friend class EntityHandle;
  friend class EntityRenderer;

  friend class RuntimeState;
  friend class MapInstance;

  NotNullPtr<Entity> CreateEntity(bool activate);
  NotNullPtr<Entity> CreateEntity(NotNullPtr<EntityDef> entity_def, bool activate);
  NotNullPtr<Entity> CreateEntity(NotNullPtr<EntityResource> entity_resource, bool activate);
  void AddComponentsToEntity(NotNullPtr<EntityDef> entity_def, NotNullPtr<Entity> entity);

  void DestroyEntity(NotNullPtr<Entity> entity);

private:
  NotNullPtr<RuntimeState> m_RuntimeState;
  void * m_EntityAllocator;

  std::unique_ptr<EventSystem> m_EventSystem;
};