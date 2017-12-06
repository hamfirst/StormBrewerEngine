#pragma once

#include "Runtime/RuntimeCommon.h"

#include "StormRefl/StormReflMetaFuncs.h"
#include "StormRefl/StormReflMetaCall.h"

template <bool ProperSignature>
struct EventHandlerRegisterHelper
{
  template <typename T, typename FuncPtr, typename ParamType, typename ... Args>
  static void Process(FuncPtr func_ptr, std::vector<std::pair<uint32_t, Delegate<void, void *, const void *, Args...>>> & handlers)
  {
    handlers.push_back(std::make_pair(ParamType::TypeNameHash, [func_ptr](void * ptr, const void * ev, Args... args)
    {
      T * p_this = static_cast<T *>(ptr);
      const ParamType * param = static_cast<const ParamType *>(ev);
      (p_this->*func_ptr)(*param, std::forward<Args>(args)...);
    }));
  }
};

template <>
struct EventHandlerRegisterHelper<false>
{
  template <typename FuncPtr, typename ParamType, typename ... Args>
  static void Process(FuncPtr ptr, std::vector<std::pair<uint32_t, Delegate<void, void *, const void *, Args...>>> & handlers)
  {

  }
};

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
      constexpr bool ProperSignature = (sizeof...(Args) == FuncType::params_n - 1);

      EventHandlerRegisterHelper<ProperSignature>::template Process<T, decltype(func_ptr), ParamType, Args...>(func_ptr, handlers);
    };

    StormReflFuncVisitor<T>::VisitFuncs(visitor);
    return handlers;
  }

  void TriggerEventHandler(uint32_t event_type, const void * ev, Args...args)
  {
    T * t = static_cast<T *>(this);
    static std::vector<std::pair<uint32_t, Delegate<void, void *, const void *, Args...>>> handlers = RegisterEventHandlers();

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

