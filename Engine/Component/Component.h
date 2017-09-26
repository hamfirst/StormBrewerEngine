#pragma once

#include "Foundation/SkipField/SkipFieldIterator.h"
#include "Foundation/Optional/NullOpt.h"

#include "Engine/Entity/Entity.h"
#include "Engine/Audio/VolumeCategory.h"
#include "Engine/Audio/AudioHandle.h"

#include "Engine/Component/ComponentHandle.h"
#include "Engine/Component/ComponentRegistrationMacros.h"

class Entity;
class ComponentSystem;
class ComponentUpdateBucketList;
class ComponentInitData;

template <class AssetType>
class AssetReference;

class AudioAsset;

class VisualEffectInstance;
class VisualEffectDef;
class VisualEffectResource;
using VisualEffectResourcePtr = DocumentResourcePtr<VisualEffectDef, VisualEffectResource>;

class GameSharedGlobalResources;
class GameClientGlobalResources;

typedef NullOptPtr<Component> (*ComponentResolver)(const ComponentHandle & handle, void * comp_store);

class ENGINE_EXPORT Component
{
public:
  Component();
  virtual ~Component();

  DECLARE_BASE_COMPONENT;

  Entity * GetEntity();
  const Entity * GetEntity() const;

  template <typename T>
  NullOptPtr<T> CastTo()
  {
    if (CastToInternal(T::TypeNameHash))
    {
      return static_cast<T *>(this);
    }

    return nullptr;
  }

  template <typename T>
  const NullOptPtr<T> CastTo() const
  {
    if (CastToInternal(T::TypeNameHash))
    {
      return static_cast<const T *>(this);
    }

    return nullptr;
  }

  NullOptPtr<Component> CastTo(uint32_t type_name_hash);
  NullOptPtr<const Component> CastTo(uint32_t type_name_hash) const;

  template <typename EventType>
  uint32_t AddEventHandler(Delegate<void, const EventType &, NullOptPtr<Entity>> && handler)
  {
    return GetEntity()->m_EventDispatch.AddEventHandler<EventType>(std::move(handler), GetHandle());
  }

  void Destroy();
  bool IsDestroyed();

  int GetBucket() const;
  ComponentHandle GetHandle() const;

  GameSharedGlobalResources & GetSharedGlobalResources();
  GameClientGlobalResources & GetClientGlobalResources();

  AudioHandle PlayAudio(const AssetReference<AudioAsset> & asset_ref, VolumeCategory cat = VolumeCategory::kSoundEffects, float volume = 1.0f, float pan = 0.0f, bool looping = false);

  NotNullPtr<VisualEffectInstance> CreateVisualEffect(const VisualEffectResourcePtr & fx_resource);
  NotNullPtr<VisualEffectInstance> CreateVisualEffect(const VisualEffectResourcePtr & fx_resource, int layer, const Vector2f & pos);

protected:

  void InitComponentStore(void * comp_store);
  void * GetComponentSore();

private:

  friend class Entity;
  friend class ComponentSystem;

  template <typename Type>
  friend class SkipField;

  void SetOwner(NotNullPtr<Entity> entity);
  virtual void OnActivate();
  virtual void OnDestroy();
  virtual void ServerUpdate();
  virtual void ServerDestroy();

  void SetHandle(Handle & handle);
  void SetIterator(const SkipFieldIterator & itr);
  const SkipFieldIterator & GetIterator() const;

  void SetBucket(int bucket);

private:

  NullOptPtr<Entity> m_Entity; // This is set to nullptr when the component has been destroyed
  NotNullPtr<ComponentSystem> m_ComponentSystem;
  
  int m_Bucket;

  ComponentHandle m_Handle;
  SkipFieldIterator m_Iterator;

};

template <typename T>
NullOptPtr<T> ComponentCast(NotNullPtr<Component> comp)
{
  return comp->CastTo<T>();
}
