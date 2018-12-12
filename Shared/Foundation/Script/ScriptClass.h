#pragma once

#include "Foundation/Common.h"
#include "Foundation/Script/ScriptObject.h"
#include "Foundation/Script/ScriptValue.h"
#include "Foundation/Script/ScriptFuncs.h"
#include "Foundation/Script/ScriptClassDelegate.h"
#include "Foundation/Script/ScriptClassRef.h"

struct lua_State;

class ScriptClassBase
{
protected:
  ScriptClassBase(czstr name, NotNullPtr<ScriptState> script_state);

  virtual void * CreateNewObject() = 0;
  virtual void DestroyObject(void * obj) = 0;
  virtual std::size_t GetTypeNameHash() = 0;

  static void * ReadObjPointer(void * state);
  static ScriptClassBase * ReadClassPointer(void * state);

protected:
  friend class ScriptClassInternal;
  friend struct ScriptClassRefData;


  template <typename T, typename ReturnValue, typename ... Args>
  friend class ScriptClassFunctionAdder;

  std::string m_Name;
  std::unordered_map<uint32_t, void(*)(const void *, void *)> m_ReadMethods;
  std::unordered_map<uint32_t, void(*)(void *, void *)> m_WriteMethods;
  std::unordered_map<uint32_t, int(*)(lua_State *)> m_CallMethods;
};

template <typename T>
class ScriptClass;

template <typename T, typename ReturnValue, typename ... Args>
class ScriptClassFunctionAdder
{
public:

  template <ReturnValue(T::*Func)(Args...)>
  void AddFunction(czstr name);

private:

  template <typename ClassT>
  friend class ScriptClass;

  ScriptClassFunctionAdder(NotNullPtr<ScriptClass<T>> c) :
    m_Class(c)
  {

  }

  template <typename ... TArgs, std::size_t ... I>
  static void PullArgs(std::tuple<TArgs...> & arg, std::index_sequence<I...> seq, void * state)
  {
    std::initializer_list<bool> l = { ScriptFuncs::FetchValue(state, I + 1, std::get<I>(arg))... };
  }

private:

  NotNullPtr<ScriptClass<T>> m_Class;
};

template <typename T>
struct ScriptClassPushMember
{
  static void Process(const T & val, void * state)
  {
    ScriptFuncs::PushValue(state, val);
  }
};

template <typename ReturnType, typename ... Args>
struct ScriptClassPushMember<ScriptClassDelegate<ReturnType, Args...>>
{
  static void Process(const ScriptClassDelegate<ReturnType, Args...> & val, void * state)
  {
    ScriptFuncs::PushValue(state, val.m_FuncPtr);
  }
};

template <typename T>
struct ScriptClassAssignMember
{
  static void Process(T & val, void * state)
  {
    ScriptFuncs::PushValue(state, val);
  }
};

template <typename ReturnType, typename ... Args>
struct ScriptClassAssignMember<ScriptClassDelegate<ReturnType, Args...>>
{
  template <typename Arg, typename ... TArgs>
  static void PushArgs(void * state, Arg && arg, TArgs && ... args)
  {
    ScriptFuncs::PushValue(state, std::forward<Arg>(arg));
    PushArgs(state, std::forward<TArgs>(args)...);
  }

  static void PushArgs(void * state)
  {

  }

  static void Process(ScriptClassDelegate<ReturnType, Args...> & val, void * state)
  {
    val.m_Delegate = [state, obj = &val](Args ... args) -> ReturnType
    {
      ScriptFuncs::PushValue(state, obj->m_FuncPtr);
      PushArgs(state, std::forward<Args>(args)...);

      if constexpr (std::is_same_v<void, ReturnType>)
      {
        ScriptFuncs::CallFunc(state, sizeof...(Args), 0);
      }
      else
      {
        auto result = ScriptFuncs::CallFunc(state, sizeof...(Args), 0);
        if (result == false)
        {
          return {};
        }
        else
        {
          ReturnType ret_val;
          ScriptFuncs::PullValue(state, ret_val);
          ScriptFuncs::Discard(state, 1);
          return ret_val;
        }
      }
    };

    ScriptFuncs::PullValue(state, val.m_FuncPtr);
  }
};

template <typename T>
class ScriptClass : public ScriptClassBase
{
public:
  ScriptClass(czstr name, NotNullPtr<ScriptState> script_state,
    Delegate<NotNullPtr<T>> && new_obj_cb, Delegate<void, NotNullPtr<T>> && delete_obj_cb) :
    ScriptClassBase(name, script_state),
    m_NewObject(std::move(new_obj_cb)),
    m_DeleteObject(std::move(delete_obj_cb))
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

      ScriptClassPushMember<MemberType>::Process(val, state);
    };

    m_ReadMethods.emplace(std::make_pair(hash, read_method));

    auto write_method = [](void * ptr, void * state)
    {
      auto obj = static_cast<T *>(ptr);
      auto & val = obj->*MemberPtr;

      ScriptClassAssignMember<MemberType>::Process(val, state);
    };

    m_WriteMethods.emplace(std::make_pair(hash, write_method));
  }


  ScriptClassRef<T> CreateInstance()
  {
    auto ref_data = new ScriptClassRefData;
    ref_data->m_RefCount = 1;
    ref_data->m_Instance = CreateNewObject();
    ref_data->m_Class = this;
    return ScriptClassRef<T>(ref_data);
  }

  template <typename ReturnValue, typename ... Args>
  ScriptClassFunctionAdder<T, ReturnValue, Args...> GetFunctionAdder()
  {
    return ScriptClassFunctionAdder<T, ReturnValue, Args...>(this);
  }

  void Register();

private:

  template <typename ClassT, typename ReturnValue, typename ... Args>
  friend class ScriptClassFunctionAdder;

  virtual void * CreateNewObject() override
  {
    return m_NewObject();
  }

  virtual void DestroyObject(void * obj) override
  {
    m_DeleteObject(static_cast<T *>(obj));
  }

  virtual std::size_t GetTypeNameHash() override
  {
    return typeid(T).hash_code();
  }

private:

  Delegate<NotNullPtr<T>> m_NewObject;
  Delegate<void, NotNullPtr<T>> m_DeleteObject;

};

template <typename T, typename ReturnValue, typename ... Args>
struct ScriptClassFunctionCaller
{
  template <ReturnValue(T::*Func)(Args...), typename ArgsTuple, std::size_t ... Index>
  static int Process(void * state, T & obj, ArgsTuple && args_tuple, const std::index_sequence<Index...> & seq)
  {
    auto result = (obj.*Func)(std::get<Index>(args_tuple)...);
    ScriptFuncs::PushValue(state, result);
    return 1;
  }
};

template <typename T, typename ... Args>
struct ScriptClassFunctionCaller<T, void, Args...>
{
  template <void(T::*Func)(Args...), typename ArgsTuple, std::size_t ... Index>
  static int Process(void * state, T & obj, ArgsTuple && args_tuple, const std::index_sequence<Index...> & seq)
  {
    (obj.*Func)(std::get<Index>(args_tuple)...);
    return 0;
  }
};


template <typename T, typename ReturnValue, typename ... Args>  template <ReturnValue(T::*Func)(Args...)>
void ScriptClassFunctionAdder<T, ReturnValue, Args...>::AddFunction(czstr name)
{
  auto hash = crc32(name);

  auto call_method = [](lua_State * lua_state) -> int
  {
    auto obj = static_cast<T *>(ScriptClassBase::ReadObjPointer(lua_state));
    if (obj == nullptr)
    {
      ScriptFuncs::ReportError(lua_state, "Could not read script object pointer");
      return 0;
    }

    static const int num_args = sizeof...(Args);
    if (ScriptFuncs::CheckArgCount(lua_state, num_args) == false)
    {
      ScriptFuncs::ReportError(lua_state, "Called function with improper number of arguments");
      return 0;
    }

    std::tuple<std::decay_t<Args>...> args;
    using sequence = std::make_index_sequence<sizeof...(Args)>;

    PullArgs(args, sequence{}, lua_state);
    return ScriptClassFunctionCaller<T, ReturnValue, Args...>::template Process<Func>(lua_state, *obj, args, sequence{});
  };

  m_Class->m_CallMethods.emplace(std::make_pair(hash, call_method));
}
