
#include "Runtime/RuntimeCommon.h"
#include "Runtime/RuntimeState.h"

#include "Foundation/Random/Random.h"

#include "Runtime/Entity/Entity.h"
#include "Runtime/Entity/EntitySystem.h"
#include "Runtime/Component/Component.h"
#include "Runtime/Component/ComponentSystem.h"

#include <sb/vector.h>

Entity::Entity(NotNullPtr<RuntimeState> runtime_state, NotNullPtr<EventSystem> event_system) :
  m_RuntimeState(runtime_state),
  m_EventSystem(event_system),
  m_Parent(nullptr),
  m_Bucket(0),
  m_Activated(false),
  m_Layer(0)
{

}

Entity::~Entity()
{

}

NotNullPtr<RuntimeState> Entity::GetRuntimeState()
{
  return m_RuntimeState;
}

Sprite & Entity::GetSprite()
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

void Entity::SetRotation(bool flip_x, bool flip_y, float rotation)
{
  m_RenderState.m_Matrix.x = flip_x ? -1.0f : 1.0f;
  m_RenderState.m_Matrix.y = 0;
  m_RenderState.m_Matrix.z = 0;
  m_RenderState.m_Matrix.w = flip_y ? -1.0f : 1.0f;
}

void Entity::Destroy()
{
  m_EventHandlers.clear();

  auto comp_list = std::move(m_Components);
  for (auto comp : comp_list)
  {
    comp.second->Destroy();
  }

  m_RuntimeState->m_EntitySystem->DestroyEntity(this);
}

EntityHandle Entity::GetHandle() const 
{
  return m_Handle;
}

void Entity::SetHandle(Handle & handle)
{
  Handle & handle_conv = m_Handle;
  handle_conv = handle;

  m_Handle.m_EntityManager = m_RuntimeState->m_EntitySystem.get();
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
  auto comp = m_RuntimeState->m_ComponentSystem->CreateComponent(type_index, init_data);
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
  while (index < m_EventHandlers.size())
  {
    if (m_EventHandlers[index].m_Component == component)
    {
      vremove_index_quick(m_EventHandlers, index);
      break;
    }
    else
    {
      index++;
    }
  }
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

uint32_t Entity::AddEventHandler(NotNullPtr<Component> component, uint32_t event_type, Delegate<void, void *> && func)
{
  uint32_t handler_key = GetRandomNumber();
  m_EventHandlers.emplace_back(EntityEventHandler{event_type, handler_key, component, std::move(func)});
  return handler_key;
}

void Entity::RemoveEventHandler(uint32_t handler_key)
{
  for (std::size_t index = 0, end = m_EventHandlers.size(); index < end; ++index)
  {
    if (m_EventHandlers[index].m_HandlerKey == handler_key)
    {
      vremove_index_quick(m_EventHandlers, index);
      return;
    }
  }
}

void Entity::TriggerEventHandler(uint32_t event_type, void * ev)
{
  for (std::size_t index = 0, end = m_EventHandlers.size(); index < end; ++index)
  {
    if (m_EventHandlers[index].m_EventType == event_type)
    {
      m_EventHandlers[index].m_Handler(ev);
    }
  }
}
