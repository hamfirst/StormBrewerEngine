#pragma once

class Entity;
class EntityResource;
class EngineState;
class GameContainer;
class DrawList;

struct EntityDef;

#include "Engine/Entity/EntityHandle.h"
#include "Engine/Entity/Entity.h"

class ENGINE_EXPORT EntitySystem
{
public:

  EntitySystem(NotNullPtr<EngineState> engine_state, NotNullPtr<GameContainer> game);
  ~EntitySystem();

  NullOptPtr<Entity> ResolveHandle(const EntityHandle & handle);

  void FindAllEntitiesWithName(czstr name, std::vector<NotNullPtr<Entity>> & outp_entities);
  void DestroyAllEntities();

  void FinalizeEvents();

  void DrawAllEntities(const Box & viewport_bounds, DrawList & draw_list);
  static void DefaultDrawEntity(NullOptPtr<Entity> entity, const Box & viewport_bounds, const RenderVec2 & screen_center);

private:

  friend class Entity;
  friend class EntityHandle;

  friend class EngineState;
  friend class MapInstance;

  NotNullPtr<Entity> CreateEntity(bool activate);
  NotNullPtr<Entity> CreateEntity(NotNullPtr<EntityDef> entity_def, bool activate);
  NotNullPtr<Entity> CreateEntity(NotNullPtr<EntityResource> entity_resource, NullOptPtr<ServerObject> server_object, bool activate);
  void AddComponentsToEntity(NotNullPtr<EntityDef> entity_def, NotNullPtr<Entity> entity);

  void DestroyEntity(NotNullPtr<Entity> entity);

private:
  NotNullPtr<EngineState> m_EngineState;
  NotNullPtr<GameContainer> m_GameContainer;
  void * m_EntityAllocator;

  std::unique_ptr<EntityEventSystem> m_EventSystem;
};