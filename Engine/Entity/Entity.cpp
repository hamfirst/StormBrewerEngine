
#include "Engine/EngineCommon.h"

#include "Engine/EngineState.h"
#include "Engine/Entity/Entity.h"
#include "Engine/Entity/EntitySystem.h"
#include "Engine/Component/Component.h"
#include "Engine/Component/ComponentSystem.h"

#include "Foundation/Random/Random.h"

#include "Runtime/Event/EventSystem.h"
#include "Runtime/ServerObject/ServerObjectManager.h"

#include <sb/vector.h>

template class EventSystem<Entity, EntityHandle>;
template class EventDispatch<Entity, ComponentHandle>;

NullOptPtr<ServerObjectManager> GetServerObjectManager(NotNullPtr<GameContainer> game);
NullOptPtr<ServerObjectManager> GetServerObjectManager(NotNullPtr<GameContainer> game, int history_index);

Entity::Entity(NotNullPtr<EngineState> engine_state, NotNullPtr<EntityEventSystem> event_system, const ServerObjectHandle & server_object, NotNullPtr<GameContainer> game) :
  m_EngineState(engine_state),
  m_EventSystem(event_system),
  m_ServerObject(server_object),
  m_GameContainer(game),
  m_Parent(nullptr),
  m_Bucket(0),
  m_Activated(false),
  m_Layer(0),
  m_AssetHash(0)
{

}

Entity::~Entity()
{

}

void Entity::TriggerEventHandler(uint32_t event_type, const void * ev)
{
  m_EventDispatch.TriggerEvent(event_type, ev);
}

NotNullPtr<EngineState> Entity::GetEngineState()
{
  return m_EngineState;
}

NotNullPtr<GameContainer> Entity::GetGameContainer()
{
  return m_GameContainer;
}

SpritePtr & Entity::GetSprite()
{
  return m_Sprite;
}

Vector2f & Entity::GetPosition()
{
  return m_Position;
}

void Entity::SetPosition(const Vector2f & position)
{
  m_Position = position;
}

int & Entity::GetLayer()
{
  return m_Layer;
}

void Entity::SetLayer(int layer)
{
  m_Layer = layer;
}

std::string & Entity::GetName()
{
  return m_Name;
}

uint64_t Entity::GetAssetNameHash()
{
  return m_AssetHash;
}

AnimationState & Entity::GetAnimationState()
{
  return m_RenderState;
}

EntityRenderState & Entity::GetRenderState()
{
  return m_RenderState;
}

void Entity::SetSkinName(uint32_t skin_name_hash)
{
  m_RenderState.m_SkinNameHash = skin_name_hash;
}

void Entity::SetDefaultFrame()
{
  if (m_Sprite.GetResource() != nullptr)
  {
    m_Sprite.GetResource()->GetDefaultFrame(m_RenderState);
  }
  else
  {
    AnimationState & cur_state = m_RenderState;
    cur_state = AnimationState{};
  }
}

bool Entity::FrameAdvance(uint32_t anim_name_hash, bool loop)
{
  if (m_Sprite.GetResource() != nullptr)
  {
    return m_Sprite.GetResource()->FrameAdvance(anim_name_hash, GetAnimationState(), loop);
  }

  return false;
}

bool Entity::SyncToFrame(uint32_t anim_name_hash, int frame)
{
  if (m_Sprite.GetResource() != nullptr)
  {
    return m_Sprite.GetResource()->SyncToFrame(anim_name_hash, GetAnimationState(), frame);
  }

  return false;
}

Box Entity::GetDrawingFrame() const
{
  return Box::FromFrameCenterAndSize(m_Position, Vector2(m_RenderState.m_FrameWidth, m_RenderState.m_FrameHeight));
}

void Entity::SetParent(NullOptPtr<Entity> entity)
{
  if (m_Parent != nullptr)
  {
    m_Parent->RemoveFromChildList(this);
  }

  m_Parent = entity;

  if (m_Parent)
  {
    m_Parent->AddToChildList(this);
    m_Bucket = m_Parent->m_Bucket + 1;
    UpdateChildListBucket();
  }
  else
  {
    m_Bucket = 0;
    UpdateChildListBucket();
  }
}

NullOptPtr<ServerObject> Entity::GetServerObject(int history_index)
{
  auto server_object_manager = ::GetServerObjectManager(m_GameContainer);
  auto obj = server_object_manager ? m_ServerObject.Resolve(*server_object_manager) : nullptr;

  if (history_index == 0)
  {
    return obj;
  }

  if (server_object_manager == nullptr)
  {
    return nullptr;
  }

  history_index = std::min(history_index, obj->GetLifetime());
  server_object_manager = GetServerObjectManager(history_index);
  return m_ServerObject.Resolve(*server_object_manager);
}

void Entity::SetRotation(bool flip_x, bool flip_y, float rotation)
{
  m_RenderState.m_Matrix.x = flip_x ? -1.0f : 1.0f;
  m_RenderState.m_Matrix.y = 0;
  m_RenderState.m_Matrix.z = 0;
  m_RenderState.m_Matrix.w = flip_y ? -1.0f : 1.0f;
}

void Entity::SetCustomDrawingCallback(EntityCustomDraw && draw_callback)
{
  m_CustomDraw = std::move(draw_callback);
}

void Entity::ClearCustomDrawingCallback()
{
  m_CustomDraw.Clear();
}

void Entity::Destroy()
{
  m_EventDispatch.ClearAllHandlers();

  auto comp_list = std::move(m_Components);
  for (auto comp : comp_list)
  {
    comp.second->Destroy();
  }

  m_EngineState->m_EntitySystem->DestroyEntity(this);
}

EntityHandle Entity::GetHandle() const 
{
  return m_Handle;
}

void Entity::SetHandle(Handle & handle)
{
  Handle & handle_conv = m_Handle;
  handle_conv = handle;

  m_Handle.m_EntityManager = m_EngineState->m_EntitySystem.get();
}

void Entity::SetIterator(const SkipFieldIterator & itr)
{
  m_Iterator = itr;
}

const SkipFieldIterator & Entity::GetIterator() const
{
  return m_Iterator;
}

void Entity::Activate()
{
  if (m_Activated)
  {
    return;
  }

  m_Activated = true;
  for (auto & comp : m_Components)
  {
    comp.second->OnActivate();
  }
}

void Entity::ServerUpdate()
{
  if (m_Activated == false)
  {
    return;
  }

  for (auto & comp : m_Components)
  {
    comp.second->ServerUpdate();
  }
}

void Entity::ServerDestroy()
{
  if (m_Activated == false)
  {
    return;
  }

  for (auto & comp : m_Components)
  {
    comp.second->ServerDestroy();
  }
}

bool Entity::IsActivated() const
{
  return m_Activated;
}

void Entity::AddToChildList(NotNullPtr<Entity> entity)
{
  m_ChildEntities.emplace_back(entity);
}

void Entity::RemoveFromChildList(NotNullPtr<Entity> entity)
{
  vremove_quick(m_ChildEntities, entity);
}

void Entity::UpdateChildListBucket()
{
  for (auto & elem : m_Components)
  {
    elem.second->SetBucket(m_Bucket);
  }

  for (auto & elem : m_ChildEntities)
  {
    elem->UpdateBucket(m_Bucket + 1);
  }
}

void Entity::UpdateBucket(int bucket)
{
  m_Bucket = bucket;
  UpdateChildListBucket();
}

void Entity::AddComponentInternal(NotNullPtr<Component> component)
{
  component->SetOwner(this);

  m_Components.push_back(std::make_pair(component->GetTypeNameHash(), component));

  if (m_Activated)
  {
    component->OnActivate();
  }
}

Component * Entity::AddComponentInternal(std::size_t type_index, void * init_data)
{
  auto comp = m_EngineState->m_ComponentSystem->CreateComponent(type_index, init_data);
  AddComponentInternal(comp);
  return comp;
}

void Entity::RemoveComponentInternal(NotNullPtr<Component> component)
{
  for (std::size_t index = 0, end = m_Components.size(); index < end; ++index)
  {
    if (m_Components[index].second == component)
    {
      vremove_index_quick(m_Components, index);
      break;
    }
  }

  std::size_t index = 0;
  m_EventDispatch.RemoveEventsByUserData(component->GetHandle());
}

NullOptPtr<Component> Entity::FindComponentInternal(uint32_t component_type_name_hash)
{
  for (auto & elem : m_Components)
  {
    if (elem.first == component_type_name_hash)
    {
      return elem.second;
    }
  }

  return nullptr;
}

NullOptPtr<Component> Entity::FindComponentThatImplementsInternal(uint32_t component_type_name_hash)
{
  for (auto & elem : m_Components)
  {
    if (elem.second->CastTo(component_type_name_hash))
    {
      return elem.second;
    }
  }

  return nullptr;
}

void Entity::RemoveEventHandler(uint32_t handler_key)
{
  m_EventDispatch.RemoveEvent(handler_key);
}

NullOptPtr<ServerObjectManager> Entity::GetServerObjectManager()
{
  return ::GetServerObjectManager(m_GameContainer);
}

NullOptPtr<ServerObjectManager> Entity::GetServerObjectManager(int history_index)
{
  return ::GetServerObjectManager(m_GameContainer, history_index);
}
