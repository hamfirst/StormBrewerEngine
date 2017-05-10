
#include "Runtime/RuntimeCommon.h"

#include "Runtime/Component/Component.h"
#include "Runtime/Component/ComponentSystem.h"
#include "Runtime/Component/ComponentInitData.refl.meta.h"
#include "Runtime/Component/ComponentInitDataTypeDatabase.h"
#include "Runtime/Component/ComponentInitDataTypeDatabaseRegister.h"

#include "Runtime/Component/ComponentList.h"
#include "Runtime/Component/ComponentUpdateBucketList.h"
#include "Runtime/Component/ComponentUpdateRegistrationTemplates.h"
#include "Runtime/Entity/Entity.h"

REGISTER_BASE_COMPONENT(Component);

Component::Component() :
  m_Bucket(0)
{

}

Component::~Component()
{

}

Entity * Component::GetEntity()
{
  return m_Entity;
}

const Entity * Component::GetEntity() const
{
  return m_Entity;
}


NullOptPtr<Component> Component::CastTo(uint32_t type_name_hash)
{
  if (CastToInternal(type_name_hash))
  {
    return this;
  }

  return nullptr;
}

NullOptPtr<const Component> Component::CastTo(uint32_t type_name_hash) const
{
  if (CastToInternal(type_name_hash))
  {
    return this;
  }

  return nullptr;
}

void Component::Destroy()
{
  OnDestroy();

  m_Entity->RemoveComponentInternal(this);
  m_Entity = nullptr;

  m_ComponentSystem->AddToDeadComponentList(this);
}

bool Component::IsDestroyed()
{
  return m_Entity == nullptr;
}

int Component::GetBucket() const
{
  return m_Bucket;
}

ComponentHandle Component::GetHandle() const
{
  return m_Handle;
}

void Component::InitComponentStore(void * comp_store)
{
  m_Handle.m_ComponentStore = comp_store;
}

void * Component::GetComponentSore()
{
  return m_Handle.m_ComponentStore;
}

void Component::SetOwner(NotNullPtr<Entity> entity)
{
  m_Entity = entity;
}

void Component::OnActivate()
{

}

void Component::OnDestroy()
{

}

void Component::SetHandle(Handle & handle)
{
  Handle & int_handle = m_Handle;
  int_handle = handle;
  m_Handle.ResolveFunc = GetResolver();
}

void Component::SetIterator(const SkipFieldIterator & itr)
{
  m_Iterator = itr;
}

const SkipFieldIterator & Component::GetIterator() const
{
  return m_Iterator;
}

void Component::SetBucket(int bucket)
{
  m_Bucket = bucket;
}
