
#include "Engine/EngineCommon.h"

#include "Engine/EngineState.h"
#include "Engine/Entity/Entity.h"
#include "Engine/Entity/EntitySystem.h"
#include "Engine/Component/Component.h"
#include "Engine/Component/ComponentSystem.h"

#include "Foundation/Random/Random.h"

#include "Runtime/Event/EventSystem.h"

#include <sb/vector.h>

template class EventSystem<Entity, EntityHandle>;
template class EventDispatch<Entity, ComponentHandle>;

Entity::Entity(NotNullPtr<EngineState> engine_state, NotNullPtr<EntityEventSystem> event_system, NullOptPtr<ServerObject> server_object, NotNullPtr<GameContainer> game) :
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

Vector2 & Entity::GetPosition()
{
  return m_MoverState.m_Position;
}

MoverState & Entity::GetMoverState()
{
  return m_MoverState;
}

int & Entity::GetLayer()
{
  return m_Layer;
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

bool Entity::FrameAdvance(uint32_t anim_name_hash, bool loop)
{
  if (m_Sprite.GetResource() != nullptr)
  {
    return m_Sprite.GetResource()->FrameAdvance(anim_name_hash, GetAnimationState(), loop);
  }

  return false;
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

NullOptPtr<ServerObject> Entity::GetServerObject()
{
  return m_ServerObject;
}

void Entity::SetRotation(bool flip_x, bool flip_y, float rotation)
{
  m_RenderState.m_Matrix.x = flip_x ? -1.0f : 1.0f;
  m_RenderState.m_Matrix.y = 0;
  m_RenderState.m_Matrix.z = 0;
  m_RenderState.m_Matrix.w = flip_y ? -1.0f : 1.0f;
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

void Entity::TriggerEventHandler(uint32_t event_type, void * ev, NullOptPtr<Entity> src)
{
  m_EventDispatch.TriggerEvent(event_type, ev, src);
}
