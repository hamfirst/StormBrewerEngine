#pragma once

#include "Foundation/SkipField/SkipField.h"


template <typename ComponentType>
class ComponentList
{
public:

  NotNullPtr<ComponentType> AllocateComponent()
  {
    auto ptr = m_ComponentAllocator.Allocate();
    return ptr;
  }

  template <typename InitData>
  NotNullPtr<ComponentType> AllocateComponent(InitData && init_data)
  {
    auto ptr = m_ComponentAllocator.Allocate(std::forward<InitData>(init_data));
    return ptr;
  }

  void FreeComponent(NotNullPtr<ComponentType> component)
  {
    m_ComponentAllocator.Release(component);
  }

  NullOptPtr<Component> ResolveHandle(const ComponentHandle & handle)
  {
    return static_cast<NullOptPtr<Component>>(m_ComponentAllocator.ResolveHandle(handle));
  }

  template <typename Callable>
  void VisitAll(Callable && callable)
  {
    m_ComponentAllocator.VisitAll(std::forward<Callable>(callable));
  }

private:
  SkipField<ComponentType> m_ComponentAllocator;
};
