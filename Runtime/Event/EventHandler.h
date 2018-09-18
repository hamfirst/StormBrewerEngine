#pragma once

#include "Runtime/RuntimeCommon.h"
#include "Runtime/Event/Event.h"

#include "StormRefl/StormReflMetaFuncs.h"
#include "StormRefl/StormReflMetaCall.h"

template <bool ProperSignature>
struct EventHandlerRegisterHelper
{
  template <typename T, typename FuncPtr, typename ParamType>
  static void Process(FuncPtr func_ptr, std::vector<std::pair<uint32_t, Delegate<bool, void *, void *, const EventMetaData &>>> & handlers)
  {
    handlers.push_back(std::make_pair(ParamType::TypeNameHash, [func_ptr](void * ptr, void * ev, const EventMetaData & meta)
    {
      T * p_this = static_cast<T *>(ptr);
      ParamType * param = static_cast<ParamType *>(ev);
      return (p_this->*func_ptr)(*param, meta);
    }));
  }
};

template <>
struct EventHandlerRegisterHelper<false>
{
  template <typename FuncPtr, typename ParamType, typename ... Args>
  static void Process(FuncPtr ptr, std::vector<std::pair<uint32_t, Delegate<bool, void *, void *, Args...>>> & handlers)
  {

  }
};

template <typename T>
class EventHandler
{
public:

  static std::vector<std::pair<uint32_t, Delegate<bool, void *, void *, const EventMetaData &>>> RegisterEventHandlers()
  {
    std::vector<std::pair<uint32_t, Delegate<bool, void *, void *, const EventMetaData &>>> handlers;
    auto visitor = [&](auto f)
    {
      using FuncType = decltype(f);
      using ParamType = typename std::decay_t<typename FuncType::template param_info<0>::param_type>;

      auto func_ptr = FuncType::GetFunctionPtr();
      constexpr bool ProperSignature = true;

      EventHandlerRegisterHelper<ProperSignature>::template Process<T, decltype(func_ptr), ParamType>(func_ptr, handlers);
    };

    StormReflFuncVisitor<T>::VisitFuncs(visitor);
    return handlers;
  }

  bool TriggerEventHandler(uint32_t event_type, void * ev, const EventMetaData & meta)
  {
    T * t = static_cast<T *>(this);
    static auto handlers = RegisterEventHandlers();

    for (auto & elem : handlers)
    {
      if (elem.first == event_type)
      {
        return elem.second(t, ev, meta);
      }
    }

    return true;
  }
};

