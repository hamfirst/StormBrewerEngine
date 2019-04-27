#pragma once

class Entity;
class EntityResource;
class EngineState;
class GameContainer;
class DrawList;
class ShaderProgram;

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
  void RemoveServerObjectManagerFromAllEntities();

  void BeginFrame();
  void FinalizeEvents();

  void DrawAllEntities(const Box & viewport_bounds, DrawList & draw_list);
  void DrawEntity(NullOptPtr<Entity> entity, const Box & viewport_bounds, const RenderVec2 & screen_center, RenderState & render_state);
  static void DefaultDrawEntity(NullOptPtr<Entity> entity, const Box & viewport_bounds, const RenderVec2 & screen_center, 
                                RenderState & render_state, ShaderProgram & shader);

  static void DefaultDrawEntity(SpritePtr & sprite, const Vector2f & pos, const EntityRenderState & entity_render_state, 
                                const Box & viewport_bounds, const RenderVec2 & screen_center, 
                                RenderState & render_state, ShaderProgram & shader);


private:

  friend class Entity;
  friend class EntityHandle;

  friend class EngineState;
  friend class MapInstance;

  NotNullPtr<Entity> CreateEntity(bool activate);
  NotNullPtr<Entity> CreateEntity(NotNullPtr<EntityDef> entity_def, bool activate);
  NotNullPtr<Entity> CreateEntity(NotNullPtr<EntityResource> entity_resource,
          NullOptPtr<const ServerObject> server_object, NullOptPtr<const ServerObjectManager> obj_manager, bool activate);
  void AddComponentsToEntity(NotNullPtr<EntityDef> entity_def, NotNullPtr<Entity> entity);

  void DestroyEntity(NotNullPtr<Entity> entity);

private:
  NotNullPtr<EngineState> m_EngineState;
  NotNullPtr<GameContainer> m_GameContainer;
  void * m_EntityAllocator;

  std::unique_ptr<EntityEventSystem> m_EventSystem;
};