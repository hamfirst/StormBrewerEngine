
#pragma once

#include "Foundation/Delegate/Delegate.h"

#include "Foundation/Script/ScriptFuncPtr.h"

template <typename ReturnType, typename ... Args>
class ScriptClassDelegate
{
public:

  ScriptClassDelegate() = default;
  ScriptClassDelegate(const ScriptClassDelegate & rhs) = delete;
  ScriptClassDelegate(ScriptClassDelegate && rhs) = delete;
  ~ScriptClassDelegate() = default;

  ScriptClassDelegate & operator = (const ScriptClassDelegate & rhs) = delete;
  ScriptClassDelegate & operator = (ScriptClassDelegate && rhs) = delete;

  template <typename Callable, typename std::enable_if_t<
          !std::is_same<std::decay_t<Callable>, Delegate<ReturnType, Args...>>::value &&
          std::is_class<std::decay_t<Callable>>::value> * Enable = nullptr>
  ScriptClassDelegate & operator = (Callable && callable)
  {
    m_FuncPtr.Clear();
    m_Delegate = std::forward<Callable>(callable);
  }

  ReturnType Call(Args ... args)
  {
    return m_Delegate.Call(std::forward<Args>(args)...);
  }

  ReturnType operator()(Args ... args)
  {
    return m_Delegate.Call(std::forward<Args>(args)...);
  }

private:

  template <typename T>
  friend class ScriptClass;

  friend class ScriptClassBase;

  ScriptFuncPtr m_FuncPtr;
  Delegate<ReturnType, Args...> m_Delegate;
};

template <typename T>
struct ScriptClassIsDelegateT : public std::false_type
{

};

template <typename ReturnType, typename ... Args>
struct ScriptClassIsDelegateT<ScriptClassDelegate<ReturnType, Args...>> : public std::true_type
{

};

template <typename T>
constexpr bool ScriptClassIsDelegate = ScriptClassIsDelegateT<T>::value;
