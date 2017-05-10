#pragma once

#include <memory>

#include "Foundation/Optional/NullOpt.h"

class CollisionSystem;
class EntitySystem;
class Entity;
class EntityResource;
class ComponentSystem;
class Component;
class ComponentUpdateBucketList;
class MapSystem;
class MapResource;

class RuntimeState
{
public:

  RuntimeState();
  ~RuntimeState();

  NotNullPtr<Entity> CreateEntity();
  NotNullPtr<Entity> CreateEntity(NotNullPtr<EntityResource> resource);

  void LoadMap(NotNullPtr<MapResource> map);

  uint32_t CheckCollision(const Box & box, uint32_t collision_layer_mask);
  uint32_t CheckCollisionAny(const Box & box, uint32_t collision_layer_mask);

  template <typename T>
  void VisitComponents(Delegate<void, NotNullPtr<T>> & cb);

protected:

  void CreateUpdateList(ComponentUpdateBucketList & bucket_list);
  void FinalizeEvents();

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

