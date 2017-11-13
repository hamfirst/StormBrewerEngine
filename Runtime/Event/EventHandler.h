#pragma once

#include "Runtime/RuntimeCommon.h"

#include "StormRefl/StormReflMetaFuncs.h"
#include "StormRefl/StormReflMetaCall.h"

template <typename T, typename ... Args>
class EventHandler
{
public:

  static std::vector<std::pair<uint32_t, Delegate<void, void *, const void *, Args...>>> RegisterEventHandlers()
  {
    std::vector<std::pair<uint32_t, Delegate<void, void *, const void *, Args...>>> handlers;
    auto visitor = [&](auto f)
    {
      using FuncType = decltype(f);
      using ParamType = typename std::decay_t<typename FuncType::template param_info<0>::param_type>;

      auto func_ptr = FuncType::GetFunctionPtr();
      handlers.push_back(std::make_pair(ParamType::TypeNameHash, [func_ptr](void * ptr, const void * ev, Args... args)
      {
        T * p_this = static_cast<T *>(ptr);
        const ParamType * param = static_cast<const ParamType *>(ev);
        p_this->func_ptr(*param, std::forward<Args>(args)...);
      }));

    };

    StormReflFuncVisitor<T>::VisitFuncs(visitor);
    return handlers;
  }

  void TriggerEventHandler(uint32_t event_type, const void * ev, Args...args)
  {
    T * t = static_cast<T *>(this);
    static std::vector<std::pair<uint32_t, Delegate<void, void *, const void *, Args...>>> handlers;

    for (auto & elem : handlers)
    {
      if (elem.first == event_type)
      {
        elem.second(t, ev, std::forward<Args>(args)...);
        return;
      }
    }
  }
};

