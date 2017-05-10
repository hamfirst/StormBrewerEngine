#pragma once

#include "Foundation/SkipField/SkipFieldIterator.h"
#include "Foundation/Optional/NullOpt.h"

#include "Runtime/Component/ComponentHandle.h"
#include "Runtime/Component/ComponentRegistrationMacros.h"

class Entity;
class ComponentSystem;
class ComponentUpdateBucketList;
class ComponentInitData;

typedef NullOptPtr<Component> (*ComponentResolver)(const ComponentHandle & handle, void * comp_store);

class RUNTIME_EXPORT Component
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

  template <typename T, typename Event>
  uint32_t AddEventHandler(void (T::*func)(NotNullPtr<Event>))
  {
    return m_Entity->AddEventHandler(this, Event::TypeNameHash, [this, func](void * ev) { (((T *)this)->*func)((Event *)ev); });
  }

  void Destroy();
  bool IsDestroyed();

  int GetBucket() const;
  ComponentHandle GetHandle() const;

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

