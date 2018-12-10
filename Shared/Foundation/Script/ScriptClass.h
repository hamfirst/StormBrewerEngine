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

  std::string m_Name;
  std::unordered_map<uint32_t, void (*)(const void *, void *)> m_ReadMethods;
  std::unordered_map<uint32_t, void (*)(void *, void *)> m_WriteMethods;
  std::unordered_map<uint32_t, int (*)(lua_State *)> m_CallMethods;
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

      if constexpr (ScriptClassIsDelegate<MemberType>)
      {
        ScriptFuncs::PushValue(state, val.m_FuncPtr);
      }
      else
      {
        ScriptFuncs::PushValue(state, val);
      }
    };

    m_ReadMethods.emplace(std::make_pair(hash, read_method));

    auto write_method = [](void * ptr, void * state)
    {
      auto obj = static_cast<T *>(ptr);
      auto & val = obj->*MemberPtr;


      if constexpr (ScriptClassIsDelegate<MemberType>)
      {
        AssignDelegate(state, val);
      }
      else
      {
        ScriptFuncs::PullValue(state, val);
      }
    };

    m_WriteMethods.emplace(std::make_pair(hash, write_method));
  }

  template <typename ReturnValue, typename ... Args, ReturnValue (T::*Func)(Args...)>
  void AddFunction(czstr name)
  {
    auto hash = crc32(name);

    auto call_method = [](lua_State * lua_state) -> int
    {
      auto obj = ReadObjPointer(lua_state);
      if(obj == nullptr)
      {
        ScriptFuncs::ReportError(lua_state, "Could not read script object pointer");
        return 0;
      }

      static const int num_args = sizeof...(Args);
      if(ScriptFuncs::CheckArgCount(lua_state, num_args) == false)
      {
        ScriptFuncs::ReportError(lua_state, "Called function with improper number of arguments");
        return 0;
      }

      std::tuple<std::decay_t<Args>...> args;
      using sequence = std::make_index_sequence<sizeof...(Args)>;

      PullArgs(args, sequence{}, lua_state);

      if constexpr(!std::is_same_v<ReturnValue, void>)
      {
        auto result = std::apply(obj->*Func, args);
        ScriptFuncs::PushValue(lua_state, result);
        return 1;
      }
      else
      {
        std::apply(obj->*Func, args);
        return 0;
      }
    };

    m_CallMethods.emplace(std::make_pair(hash, call_method));
  }

  ScriptClassRef<T> CreateInstance()
  {
    auto ref_data = new ScriptClassRefData;
    ref_data->m_RefCount = 1;
    ref_data->m_Instance = CreateNewObject();
    ref_data->m_Class = this;
    return ScriptClassRef<T>(ref_data);
  }

  void Register();

private:


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

  template <typename ... Args, std::size_t ... I>
  static void PullArgs(std::tuple<Args...> & arg, std::index_sequence<I...> seq, void * state)
  {
    auto l = { ScriptFuncs::FetchValue(state, I + 1, std::get<I>(arg))... };
  }

  template <typename Arg, typename ... Args>
  static void PushArgs(void * state, Arg && arg, Args && ... args)
  {
    ScriptFuncs::PushValue(state, std::forward<Arg>(arg));
    PushArgs(state, std::forward<Args>(args)...);
  }

  static void PushArgs(void * state)
  {

  }

  template <typename ReturnValue, typename ... Args>
  static void AssignDelegate(void * state, ScriptClassDelegate<ReturnValue, Args...> & del)
  {
    del.m_Delegate = [state, obj = &del](Args ... args) -> ReturnValue
    {
      ScriptFuncs::PushValue(state, obj->m_FuncPtr);
      PushArgs(state, std::forward<Args>(args)...);

      if constexpr(std::is_same_v<void, ReturnValue>)
      {
        ScriptFuncs::CallFunc(state, sizeof...(Args), 0);
      }
      else
      {
        auto result = ScriptFuncs::CallFunc(state, sizeof...(Args), 0);
        if(result == false)
        {
          return {};
        }
        else
        {
          ReturnValue ret_val;
          ScriptFuncs::PullValue(state, ret_val);
          ScriptFuncs::Discard(state, 1);
          return ret_val;
        }
      }
    };

    ScriptFuncs::PullValue(state, del.m_FuncPtr);
  }

private:

  Delegate<NotNullPtr<T>> m_NewObject;
  Delegate<void, NotNullPtr<T>> m_DeleteObject;

};

