#pragma once

#include "Engine/EngineCommon.h"

#include "Foundation/Handle/Handle.h"

class Component;
class ComponentManager;

template <typename T>
NullOptPtr<T> ComponentCast(NotNullPtr<Component> comp);

class ENGINE_EXPORT ComponentHandle : public SpecificHandle<ComponentManager>
{
public:
  ComponentHandle();
  ComponentHandle(const ComponentHandle & rhs) = default;
  ComponentHandle(ComponentHandle && rhs) = default;

  ComponentHandle & operator = (const ComponentHandle & rhs) = default;
  ComponentHandle & operator = (ComponentHandle && rhs) = default;

  NullOptPtr<Component> Resolve();

  template <typename T>
  NullOptPtr<T> ResolveTo()
  {
    auto comp = Resolve();
    if (comp)
    {
      return ComponentCast<T>(comp);
    }

    return nullptr;
  }

private:

  friend class Component;

  NullOptPtr<Component> (*ResolveFunc)(const ComponentHandle & handle, void * comp_store);
  void * m_ComponentStore;
};
