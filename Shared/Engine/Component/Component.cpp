
#include "Engine/EngineCommon.h"

#include "Runtime/Component/ComponentInitData.refl.meta.h"
#include "Runtime/Component/ComponentInitDataTypeDatabase.h"
#include "Runtime/Component/ComponentInitDataTypeDatabaseRegister.h"

#include "Engine/EngineState.h"
#include "Engine/Entity/Entity.h"
#include "Engine/Component/Component.h"
#include "Engine/Component/ComponentSystem.h"
#include "Engine/Audio/AudioManager.h"
#include "Engine/VisualEffect/VisualEffectManager.h"

#include "Engine/Component/ComponentList.h"
#include "Engine/Component/ComponentUpdateBucketList.h"
#include "Engine/Component/ComponentUpdateRegistrationTemplates.h"

REGISTER_BASE_COMPONENT(Component);

Component::Component() :
  m_Bucket(0)
{

}

Component::~Component()
{

}

NotNullPtr<Entity> Component::GetEntity()
{
  return m_Entity;
}

const NotNullPtr<Entity> Component::GetEntity() const
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

AudioHandle Component::PlayAudio(const AssetReference<AudioAsset> & asset_ref, VolumeCategory cat, float volume, float pan, bool looping)
{
  return g_AudioManager.PlayAudio(asset_ref, cat, volume, pan, looping);
}

NotNullPtr<VisualEffectInstance> Component::CreateVisualEffect(const VisualEffectResourcePtr & fx_resource)
{
  return CreateVisualEffect(fx_resource, GetEntity()->GetLayer(), GetEntity()->GetPosition());
}

NotNullPtr<VisualEffectInstance> Component::CreateVisualEffect(const VisualEffectResourcePtr & fx_resource, int layer, const Vector2f & pos)
{
  auto engine_state = GetEntity()->GetEngineState();
  return engine_state->GetVisualEffectManager()->CreateVisualEffect(fx_resource, layer, pos);
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

void Component::ServerUpdate()
{

}

void Component::ServerDestroy()
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
