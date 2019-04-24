
#pragma once

#include "Foundation/Optional/NullOpt.h"
#include "Foundation/Script/ScriptClassRef.h"

class ScriptClassBase;
struct ScriptClassInstanceInfo;

struct lua_State;

class ScriptFuncs
{
public:
  static int PushValue(void * state, const int & val);
  static int PushValue(void * state, const float & val);
  static int PushValue(void * state, const bool & val);
  static int PushValue(void * state, const char * val);
  static int PushValue(void * state, const std::string & val);
  static int PushValue(void * state, const ScriptObject & val);
  static int PushValue(void * state, const ScriptClassInstance & val);
  static int PushValue(void * state, const ScriptFuncPtr & val);

  static int PushInstance(void * state, ScriptClassRefData * ref_data, std::size_t type_id_hash);


  template <typename T>
  static int PushValue(void * state, const ScriptClassRef<T> & val)
  {
    return PushInstance(state, val.m_RefData, typeid(T).hash_code());
  }

  template <typename First, typename Second>
  static int PushValue(void * state, const std::pair<First, Second> & pair)
  {
    return PushValue(state, pair.first) + PushValue(state, pair.second);
  }

  template <typename ... Args, std::size_t ... I>
  static int PushValueTuple(void * state, const std::tuple<Args...> & val, const std::integer_sequence<std::size_t, I...> & seq)
  {
    return (PushValue(state, std::get<I>(val)) + ...);
  }

  template <typename ... Args>
  static int PushValue(void * state, const std::tuple<Args...> & val)
  {
    auto seq = std::make_index_sequence<sizeof...(Args)>{};
    return PushValueTuple(state, val, seq);
  }

  template <typename T>
  static int PushValue(void * state, const std::vector<T> & val)
  {
    StartPushTable(state);

    for(std::size_t index = 0, end = val.size(); index < end; ++index)
    {
      ContinuePushTable(state, index, &val[index], [](void * state, const void * ptr)
      {
        auto val = static_cast<const T *>(ptr);
        return PushValue(state, *val);
      });
    }

    return 1;
  }

  template <typename T>
  static int PushValue(void * state, const std::unordered_map<std::string, T> & val)
  {
    StartPushTable(state);

    for(auto && elem : val)
    {
      ContinuePushTable(state, elem.first, &elem.second, [](void * state, const void * ptr) -> int
      {
        auto val = static_cast<const T *>(ptr);
        return PushValue(state, *val);
      });
    }

    return 1;
  }

  static void PullValue(void * state, int & val);
  static void PullValue(void * state, float & val);
  static void PullValue(void * state, bool & val);
  static void PullValue(void * state, std::string & val);
  static void PullValue(void * state, ScriptObject & val);
  static void PullValue(void * state, ScriptClassInstance & val);
  static void PullValue(void * state, ScriptFuncPtr & val);
  static NullOptPtr<ScriptClassRefData> PullInstanceInfo(void * state);

  template <typename T>
  static void PullValue(void * state, ScriptClassRef<T> & val)
  {
    FetchValue<T>(state, -1, val);
  }

  static bool FetchValue(void * state, int pos, int & val);
  static bool FetchValue(void * state, int pos, float & val);
  static bool FetchValue(void * state, int pos, bool & val);
  static bool FetchValue(void * state, int pos, std::string & val);
  static bool FetchValue(void * state, int pos, ScriptObject & val);
  static bool FetchValue(void * state, int pos, ScriptClassInstance & val);
  static bool FetchValue(void * state, int pos, ScriptFuncPtr & val);

  static std::pair<NullOptPtr<ScriptClassRefData>, std::size_t> FetchInstanceInfo(void * state, int pos);

  template <typename T>
  static bool FetchValue(void * state, int pos, ScriptClassRef<T> & val)
  {
    auto instance_info = FetchInstanceInfo(state, pos);
    if(instance_info.second != typeid(T).hash_code())
    {
      val = {};
      return false;
    }

    val = ScriptClassRef<T>(instance_info.first);
    return val.IsValid();
  }

  static bool CheckArgCount(void * state, int args);
  static bool CallFunc(void * state, int num_args, int num_results);
  static void Discard(void * state, int num_stack_vals);
  static void SetTableValue(void * state);
  static void ReportMessage(void * state, czstr message);
  static void ReportError(void * state, czstr message);

private:
  static void StartPushTable(void * state);
  static void ContinuePushTable(void * state, std::size_t index, const void * ptr, int (*Func)(void *, const void *));
  static void ContinuePushTable(void * state, const std::string & key, const void * ptr, int (*Func)(void *, const void *));
};

template <typename ReturnValue, typename ... Args>
struct ScriptFunctionBinder
{
  using LuaFuncType = int (*)(lua_State *);

  template <ReturnValue (*Func)(Args...)>
  static LuaFuncType Process()
  {
    auto call_method = [](lua_State * lua_state) -> int
    {
      static const int num_args = sizeof...(Args);
      if (ScriptFuncs::CheckArgCount(lua_state, num_args) == false)
      {
        ScriptFuncs::ReportError(lua_state, "Called function with improper number of arguments");
        return 0;
      }

      std::tuple<std::decay_t<Args>...> args;
      using sequence = std::make_index_sequence<sizeof...(Args)>;

      PullArgs(args, sequence{}, lua_state);
      if constexpr(std::is_void_v<ReturnValue>)
      {
        std::apply(Func, args);
        return 0;
      }
      else
      {
        auto val = std::apply(Func, args);
        return ScriptFuncs::PushValue(lua_state, val);
      }
    };

    return call_method;
  }

  template <typename ... TArgs, std::size_t ... I>
  static void PullArgs(std::tuple<TArgs...> & arg, std::index_sequence<I...> seq, void * state)
  {
    std::initializer_list<bool> l = { ScriptFuncs::FetchValue(state, I + 1, std::get<I>(arg))... };
  }
};

template <typename ReturnValue, typename ... Args>
auto ScriptFunctionGetBinder(ReturnValue (*Func)(Args...))
{
  return ScriptFunctionBinder<ReturnValue, Args...>{};
}