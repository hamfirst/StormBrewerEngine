
#pragma once

#include "Foundation/Script/ScriptObject.h"
#include "Foundation/Script/ScriptValue.h"
#include "Foundation/Script/ScriptFuncs.h"

#include "Foundation/Allocator/IdAllocator.h"
#include "Foundation/Any/Any.h"

static const int kScriptInterfaceMaxFunctions = 128;

struct lua_State;
class ScriptInterface;
class ScriptState;

using ScriptInterfaceCallback = int (*)(lua_State *);
using ScriptInterfaceForwardDelegate = int (*)(int, ScriptInterface *, lua_State *);

extern ScriptInterfaceCallback g_ScriptInterfaceCallbackFuncs[kScriptInterfaceMaxFunctions];

class ScriptInterface
{
public:

  ScriptInterface(NotNullPtr<ScriptState> script_state);
  ScriptInterface(const ScriptInterface & rhs) = delete;
  ScriptInterface(ScriptInterface && rhs) = delete;

  ScriptInterface & operator = (const ScriptInterface & rhs) = delete;
  ScriptInterface & operator = (ScriptInterface && rhs) = delete;

  const std::shared_ptr<ScriptObject> & GetObject() const;

  template <typename ReturnValue, typename ... Args>
  void AddFunction(czstr name, Delegate<ReturnValue, Args...> && delegate)
  {
    auto call_method = [](int index, ScriptInterface * interface, lua_State * lua_state) -> int
    {
      static const int num_args = sizeof...(Args);
      if(ScriptFuncs::CheckArgCount(lua_state, num_args) == false)
      {
        ScriptFuncs::ReportError(lua_state, "Called function with improper number of arguments");
        return 0;
      }

      std::tuple<Args...> args;
      using sequence = std::make_index_sequence<sizeof...(Args)>;

      PullArgs(args, sequence{}, lua_state);

      auto delegate = interface->m_Delegates[index].Get<Delegate<ReturnValue, Args...>>();

      if constexpr(!std::is_same_v<ReturnValue, void>)
      {
        auto result = std::apply(*delegate, args);
        ScriptFuncs::PushValue(lua_state, result);
        return 1;
      }
      else
      {
        std::apply(*delegate, args);
        return 0;
      }
    };

    m_ForwardDelegates[m_NextFuncId] = call_method;
    m_Delegates[m_NextFuncId] = StaticAny<128>(std::move(delegate));
    RegisterFunc(name, m_NextFuncId);
    m_NextFuncId++;
  }

private:

  template <int Index>
  friend struct ScriptInterfaceInitFunc;

  void RegisterFunc(czstr name, int index);

  template <typename ... Args, std::size_t ... I>
  static void PullArgs(std::tuple<Args...> & arg, std::index_sequence<I...> seq, void * state)
  {
    auto l = { ScriptFuncs::FetchValue(state, I + 1, std::get<I>(arg))... };
  }

private:
  NotNullPtr<ScriptState> m_ScriptState;

  std::shared_ptr<ScriptObject> m_Object;
  int m_NextFuncId;
  ScriptInterfaceForwardDelegate m_ForwardDelegates[kScriptInterfaceMaxFunctions];
  StaticAny<128> m_Delegates[kScriptInterfaceMaxFunctions];

};