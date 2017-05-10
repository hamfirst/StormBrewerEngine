#pragma once

#include "Runtime/RuntimeCommon.h"
#include "Foundation/Handle/Handle.h"

class Component;
class ComponentManager;

class RUNTIME_EXPORT ComponentHandle : public SpecificHandle<ComponentManager>
{
public:
  ComponentHandle();
  ComponentHandle(const ComponentHandle & rhs) = default;
  ComponentHandle(ComponentHandle && rhs) = default;

  ComponentHandle & operator = (const ComponentHandle & rhs) = default;
  ComponentHandle & operator = (ComponentHandle && rhs) = default;

  NullOptPtr<Component> Resolve();

  template <typename T>
  NullOptPtr<Component> ResolveTo()
  {
    auto comp = Resolve();
    if (comp)
    {
      return comp->CastTo<T>();
    }

    return nullptr;
  }

private:

  friend class Component;

  NullOptPtr<Component> (*ResolveFunc)(const ComponentHandle & handle, void * comp_store);
  void * m_ComponentStore;
};
