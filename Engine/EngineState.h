#pragma once

#include <memory>

#include "Foundation/Optional/NullOpt.h"
#include "Foundation/Any/Any.h"

class CollisionSystem;
class EntitySystem;
class Entity;
class EntityResource;
class ComponentSystem;
class Component;
class MapSystem;
class MapResource;

class ComponentUpdateBucketList;
class ServerObject;
class GameContainer;

class EngineState
{
public:

  EngineState(NotNullPtr<GameContainer> game);
  ~EngineState();

  NotNullPtr<Entity> CreateEntity();
  NotNullPtr<Entity> CreateEntity(NotNullPtr<EntityResource> resource, NullOptPtr<ServerObject> server_object = nullptr);
  void DestroyAllEntities();

  std::size_t LoadMap(NotNullPtr<MapResource> map);
  void UnloadMap(std::size_t map_id);

  uint32_t CheckCollision(const Box & box, uint32_t collision_layer_mask);
  uint32_t CheckCollisionAny(const Box & box, uint32_t collision_layer_mask);

  template <typename T>
  void VisitComponents(Delegate<void, NotNullPtr<T>> & cb);

  NotNullPtr<CollisionSystem> GetCollisionSystem();
  NotNullPtr<EntitySystem> GetEntitySystem();
  NotNullPtr<ComponentSystem> GetComponentSystem();
  NotNullPtr<MapSystem> GetMapSystem();


private:

  friend class Entity;
  friend class EntitySystem;
  friend class EntityRenderer;
  friend class MapRenderer;
  friend class MapInstance;
  friend class Camera;

  std::unique_ptr<CollisionSystem> m_CollisionSystem;
  std::unique_ptr<EntitySystem> m_EntitySystem;
  std::unique_ptr<ComponentSystem> m_ComponentSystem;
  std::unique_ptr<MapSystem> m_MapSystem;
};

