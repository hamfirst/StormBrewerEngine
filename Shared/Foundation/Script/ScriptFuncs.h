
#pragma once

#include "Foundation/Optional/NullOpt.h"
#include "Foundation/Script/ScriptClassRef.h"

class ScriptClassBase;
struct ScriptClassInstanceInfo;

class ScriptFuncs
{
public:
  static int PushValue(void * state, const int & val);
  static int PushValue(void * state, const float & val);
  static int PushValue(void * state, const bool & val);
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
  static void ReportMessage(void * state, czstr message);
  static void ReportError(void * state, czstr message);
};

