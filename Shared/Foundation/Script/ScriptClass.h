#pragma once

#include "Foundation/Common.h"
#include "Foundation/Script/ScriptObject.h"
#include "Foundation/Script/ScriptValue.h"

class ScriptClassBase
{
protected:
  ScriptClassBase(NotNullPtr<ScriptState> script_state);

  static void PushValue(void * state, const int & val);
  static void PushValue(void * state, const float & val);
  static void PushValue(void * state, const bool & val);
  static void PushValue(void * state, const std::string & val);

  static void PullValue(void * state, int & val);
  static void PullValue(void * state, float & val);
  static void PullValue(void * state, bool & val);
  static void PullValue(void * state, std::string & val);

  static void FetchValue(void * state, int pos, int & val);
  static void FetchValue(void * state, int pos, float & val);
  static void FetchValue(void * state, int pos, bool & val);
  static void FetchValue(void * state, int pos, std::string & val);

protected:
  ScriptObject m_MetaTable;
  std::unordered_map<uint32_t, void (*)(const void *, void *)> m_ReadMethods;
  std::unordered_map<uint32_t, void (*)(void *, void *)> m_WriteMethods;
  std::unordered_map<uint32_t, void (*)(void *, void *)> m_CallMethods;
};

template <typename T>
class ScriptClass : public ScriptClassBase
{
public:
  ScriptClass(NotNullPtr<ScriptState> script_state) :
    ScriptClassBase(script_state)
  {

  }

  template <typename MemberType, MemberType T::*MemberPtr>
  void AddMember(czstr name)
  {
    auto hash = crc32(name);

    auto read_method = [](const void * ptr, void * state)
    {
      auto obj = static_cast<const T *>(ptr);
      auto & val = obj->*MemberPtr;

      ScriptClassBase::PushValue(state, val);
    };

    m_ReadMethods.emplace(std::make_pair(hash, read_method));

    auto write_method = [](void * ptr, void * state)
    {
      auto obj = static_cast<T *>(ptr);
      auto & val = obj->*MemberPtr;

      ScriptClassBase::PullValue(state, val);
    };

    m_WriteMethods.emplace(std::make_pair(hash, write_method));
  }

  template <typename ReturnValue, typename ... Args, ReturnValue (T::*Func)(Args...)>
  void AddFunction(czstr name)
  {
    auto hash = crc32(name);

    auto call_method = [](void * ptr, void * state)
    {
      auto obj = static_cast<const T *>(ptr);

      std::tuple<Args...> args;


      if constexpr(!std::is_same_v<ReturnValue, void>)
      {

      }
    };

    m_CallMethods.emplace(std::make_pair(hash, call_method));
  }

private:

  template <int N, typename ... Args>
  void PullArg(std::tuple<Args...> & args, void * state)
  {
    PullValue(state, std::template get<N>(args));
  }
};
