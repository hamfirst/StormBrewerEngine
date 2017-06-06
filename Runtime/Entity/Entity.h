#pragma once

#include <memory>
#include <vector>

#include "Foundation/SkipField/SkipFieldIterator.h"
#include "Runtime/Event/EventSystem.h"
#include "Runtime/Entity/EntityHandle.h"
#include "Runtime/Sprite/SpriteResource.h"
#include "Runtime/Animation/AnimationState.h"
#include "Runtime/Mover/MoverState.h"

class RuntimeState;
class EventSystem;
class Component;


struct EntityEventHandler
{
  uint32_t m_EventType;
  uint32_t m_HandlerKey;
  Component * m_Component;

  Delegate<void, void *> m_Handler;
};

struct EntityRenderState : public AnimationState
{
  RenderVec4 m_Matrix = RenderVec4(1, 0, 0, 1);
  RenderVec4 m_Color = RenderVec4(1, 1, 1, 1);
  bool m_Draw = true;
};

class RUNTIME_EXPORT Entity
{
public:
  Entity(NotNullPtr<RuntimeState> runtime_state, NotNullPtr<EventSystem> event_system);
  ~Entity();

  Entity(const Entity & rhs) = delete;
  Entity(Entity && rhs) = delete;

  Entity & operator = (const Entity & rhs) = delete;
  Entity & operator = (Entity && rhs) = delete;

  template <typename Component>
  NotNullPtr<Component> AddComponent()
  {
    return static_cast<Component *>(AddComponentInternal(Component::TypeIndex, nullptr));
  }

  template <typename Component, typename InitData>
  NotNullPtr<Component> AddComponent(InitData && init_data)
  {
    return static_cast<Component *>(AddComponentInternal(Component::TypeIndex, &init_data));
  }

  template <typename Component>
  NullOptPtr<Component> FindComponent()
  {
    return static_cast<Component *>(FindComponentInternal(Component::TypeNameHash));
  }

  template <typename Component>
  NullOptPtr<Component> FindComponentThatImplements()
  {
    return static_cast<Component *>(FindComponentThatImplementsInternal(Component::TypeNameHash));
  }

  template <typename Event, typename ... InitArgs>
  NotNullPtr<Event> PushEvent(const Box & box, InitArgs && ... init_args)
  {
    m_EventSystem->PushEvent(box, std::forward<InitArgs>(init_args)...);
  }

  template <typename Event>
  void PushEventReceiver(const Box & box)
  {
    m_EventSystem->PushEventReceiver(this, box, Event::TypeNameHash);
  }

  NotNullPtr<RuntimeState> GetRuntimeState();

  Sprite & GetSprite();
  Vector2 & GetPosition();
  MoverState & GetMoverState();
  int & GetLayer();
  std::string & GetName();
  AnimationState & GetAnimationState();
  EntityRenderState & GetRenderState();

  bool FrameAdvance(uint32_t anim_name_hash, bool loop = true);
  void SetParent(NullOptPtr<Entity> entity);

  void SetRotation(bool flip_x, bool flip_y, float rotation = 0);

  void Destroy();

  EntityHandle GetHandle() const;

protected:

  friend class EntitySystem;
  friend class EntityRenderer;
  friend class MapInstance;
  friend class Component;
  friend class EventSystem;

  template <typename Type>
  friend class SkipField;

  void SetHandle(Handle & handle);
  void SetIterator(const SkipFieldIterator & itr);

  const SkipFieldIterator & GetIterator() const;

  void Activate();
  bool IsActivated() const;

  void AddToChildList(NotNullPtr<Entity> entity);
  void RemoveFromChildList(NotNullPtr<Entity> entity);
  void UpdateChildListBucket();
  void UpdateBucket(int bucket);

  void AddComponentInternal(NotNullPtr<Component> component);
  Component * AddComponentInternal(std::size_t type_index, void * init_data);
  void RemoveComponentInternal(NotNullPtr<Component> component);
  NullOptPtr<Component> FindComponentInternal(uint32_t component_type_name_hash);
  NullOptPtr<Component> FindComponentThatImplementsInternal(uint32_t component_type_name_hash);
  
  uint32_t AddEventHandler(NotNullPtr<Component> component, uint32_t event_type, Delegate<void, void *> && func);
  void RemoveEventHandler(uint32_t handler_key);

  void TriggerEventHandler(uint32_t event_type, void * ev);
  
private:
  NotNullPtr<RuntimeState> m_RuntimeState;
  NotNullPtr<EventSystem> m_EventSystem;

  NullOptPtr<Entity> m_Parent;
  int m_Bucket;
  bool m_Activated;

  Sprite m_Sprite;

  MoverState m_MoverState;
  int m_Layer;
  EntityRenderState m_RenderState;
  std::string m_Name;

  EntityHandle m_Handle;
  SkipFieldIterator m_Iterator;

  std::vector<std::pair<uint32_t, NotNullPtr<Component>>> m_Components;
  std::vector<NotNullPtr<Entity>> m_ChildEntities;
  std::vector<EntityEventHandler> m_EventHandlers;
};



