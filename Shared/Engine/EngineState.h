#pragma once

#include <memory>

#include "Foundation/Optional/NullOpt.h"
#include "Foundation/Any/Any.h"

#include "Runtime/ServerObject/ServerObjectHandle.h"

class CollisionSystem;
class EntitySystem;
class Entity;
class EntityResource;
class ComponentSystem;
class Component;
class MapSystem;
class MapResource;
class MapInstance;
class VisualEffectManager;

class ComponentUpdateBucketList;
class ServerObject;
class GameContainer;
class UIManager;
class Window;

class EngineState
{
public:

  EngineState(NotNullPtr<GameContainer> game, Window & window);
  ~EngineState();

  NotNullPtr<Entity> CreateEntity();
  NotNullPtr<Entity> CreateEntity(NotNullPtr<EntityResource> resource,
          NullOptPtr<const ServerObject> server_object = nullptr,
          NullOptPtr<const ServerObjectManager> obj_manager = nullptr, bool activate = true);
  void DestroyAllEntities();

  std::size_t LoadMap(NotNullPtr<MapResource> map);
  NullOptPtr<MapInstance> GetMapInstance(std::size_t map_id);
  void UnloadMap(std::size_t map_id);

  template <typename T>
  void VisitComponents(Delegate<void, NotNullPtr<T>> & cb);

  NotNullPtr<EntitySystem> GetEntitySystem();
  NotNullPtr<ComponentSystem> GetComponentSystem();
  NotNullPtr<MapSystem> GetMapSystem();
  NotNullPtr<VisualEffectManager> GetVisualEffectManager();
  NotNullPtr<UIManager> GetUIManager();

private:

  friend class Entity;
  friend class EntitySystem;
  friend class EntityRenderer;
  friend class MapRenderer;
  friend class MapInstance;
  friend class Camera;

  std::unique_ptr<EntitySystem> m_EntitySystem;
  std::unique_ptr<ComponentSystem> m_ComponentSystem;
  std::unique_ptr<MapSystem> m_MapSystem;
  std::unique_ptr<VisualEffectManager> m_VisualEffectManager;
  std::unique_ptr<UIManager> m_UIManager;
};

