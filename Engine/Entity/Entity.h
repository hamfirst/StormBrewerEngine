#pragma once

#include <memory>
#include <vector>

#include "Foundation/SkipField/SkipFieldIterator.h"
#include "Runtime/Event/Event.h"
#include "Runtime/Event/EventSystem.h"
#include "Runtime/Event/EventDispatcher.h"
#include "Runtime/Sprite/SpriteResource.h"
#include "Runtime/Animation/AnimationState.h"

#include "Engine/Entity/EntityHandle.h"
#include "Engine/Component/ComponentHandle.h"

#include "Runtime/ServerObject/ServerObjectHandle.h"

class EngineState;
class Component;
class Entity;
class ServerObject;
class GameContainer;
class RenderState;
class RenderUtil;

using EntityEventSystem = EventSystem<Entity, EntityHandle>;
extern template class EventSystem<Entity, EntityHandle>;

using EntityEventDispatch = EventDispatch<Entity, ComponentHandle>;
extern template class EventDispatch<Entity, ComponentHandle>;

using EntityCustomDraw = Delegate<void, const Box &, const RenderVec2 &, RenderState &, RenderUtil &>;

class ENGINE_EXPORT Entity
{
public:
  Entity(NotNullPtr<EngineState> engine_state, NotNullPtr<EntityEventSystem> event_system, const ServerObjectHandle & server_object, NotNullPtr<GameContainer> game);
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
    m_EventSystem->PushEventSource(box, EventDef<Event>{}, std::forward<InitArgs>(init_args)...);
  }

  template <typename Event>
  void PushEventReceiver(const Box & box)
  {
    m_EventSystem->PushEventReceiver(this, box, Event::TypeNameHash);
  }

  bool TriggerEventHandler(uint32_t event_type, void * ev, const EventMetaData & meta);

  NotNullPtr<EngineState> GetEngineState();
  NotNullPtr<GameContainer> GetGameContainer();

  SpritePtr & GetSprite();
  void SetSprite(const SpritePtr & sprite);
  Vector2f & GetPosition();
  void SetPosition(const Vector2f & position);
  int & GetLayer();
  void SetLayer(int layer);
  std::string & GetName();
  uint64_t GetAssetNameHash();
  AnimationState & GetAnimationState();
  EntityRenderState & GetRenderState();
  void SetSkinName(uint32_t skin_name_hash);

  void SetDefaultFrame();
  bool FrameAdvance(uint32_t anim_name_hash, bool loop = true);
  bool SyncToFrame(uint32_t anim_name_hash, int frame);
  Box GetDrawingFrame() const;
  void SetParent(NullOptPtr<Entity> entity);
  NullOptPtr<ServerObject> GetServerObject(int history_index = 0);

  template <typename ServerObjectType>
  NullOptPtr<ServerObjectType> GetServerObjectAs(int history_index = 0, bool require_exact_history = false)
  {
    auto obj_manager = GetServerObjectManager();
    auto obj = obj_manager ? m_ServerObject.ResolveTo<ServerObjectType>(*obj_manager) : nullptr;

    if (history_index == 0)
    {
      return obj;
    }

    if (obj == nullptr)
    {
      return nullptr;
    }

    if (history_index > obj->GetLifetime())
    {
      if (require_exact_history)
      {
        return nullptr;
      }

      history_index = obj->GetLifetime();
    }

    history_index = std::min(history_index, obj->GetLifetime());
    obj_manager = GetServerObjectManager(history_index);
    return m_ServerObject.ResolveTo<ServerObjectType>(*obj_manager);
  }


  void SetRotation(bool flip_x, bool flip_y, float rotation = 0);
  void SetCustomDrawingCallback(EntityCustomDraw && draw_callback);
  void ClearCustomDrawingCallback();

  void Destroy();

  EntityHandle GetHandle() const;

protected:

  friend class EntitySystem;
  friend class EntityRenderer;
  friend class MapInstance;
  friend class Component;
  friend class GameClientEntitySync;

  template <typename Type>
  friend class SkipField;

  void SetHandle(Handle & handle);
  void SetIterator(const SkipFieldIterator & itr);
  const SkipFieldIterator & GetIterator() const;

  void Activate();
  bool IsActivated() const;

  void ServerUpdate();
  void ServerDestroy();

  void AddToChildList(NotNullPtr<Entity> entity);
  void RemoveFromChildList(NotNullPtr<Entity> entity);
  void UpdateChildListBucket();
  void UpdateBucket(int bucket);

  void AddComponentInternal(NotNullPtr<Component> component);
  Component * AddComponentInternal(std::size_t type_index, void * init_data);
  void RemoveComponentInternal(NotNullPtr<Component> component);
  NullOptPtr<Component> FindComponentInternal(uint32_t component_type_name_hash);
  NullOptPtr<Component> FindComponentThatImplementsInternal(uint32_t component_type_name_hash);
  
  void RemoveEventHandler(uint32_t handler_key);

  NullOptPtr<ServerObjectManager> GetServerObjectManager();
  NullOptPtr<ServerObjectManager> GetServerObjectManager(int history_index);
  
private:
  NotNullPtr<EngineState> m_EngineState;
  NotNullPtr<EntityEventSystem> m_EventSystem;
  NotNullPtr<GameContainer> m_GameContainer;

  NullOptPtr<Entity> m_Parent;
  int m_Bucket;
  bool m_Activated;

  SpritePtr m_Sprite;
  EntityCustomDraw m_CustomDraw;

  Vector2f m_Position;
  Optional<Vector2f> m_PrevPosition;
  int m_Layer;
  EntityRenderState m_RenderState;
  std::string m_Name;
  uint64_t m_AssetHash;

  EntityHandle m_Handle;
  SkipFieldIterator m_Iterator;
  ServerObjectHandle m_ServerObject;

  std::vector<std::pair<uint32_t, NotNullPtr<Component>>> m_Components;
  std::vector<NotNullPtr<Entity>> m_ChildEntities;
  EntityEventDispatch m_EventDispatch;
};



