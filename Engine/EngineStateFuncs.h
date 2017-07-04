#pragma once

#include "Engine/EngineState.h"
#include "Engine/Component/ComponentSystem.h"

template <typename T>
void EngineState::VisitComponents(Delegate<void, NotNullPtr<T>> & cb)
{
  auto callback = [](NotNullPtr<Component> comp, void * user_data)
  {
    Delegate<void, NotNullPtr<T>> * callback = static_cast<Delegate<void, NotNullPtr<T>> *>(user_data);
    callback->Call(comp);
  };

  m_ComponentSystem->VisitAll(T::TypeNameHash, callback, &cb);
}
