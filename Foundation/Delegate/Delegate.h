#pragma once

#include <type_traits>
#include <utility>

#include "Foundation/Optional/NullOpt.h"

static const int kMaxDelegateSize = 32;

template <typename Callable, typename Enable=void>
class DelegateDeleter
{
public:
  static void DeleteObj(void * obj)
  {
  }
};

template <typename Callable>
class DelegateDeleter<Callable, typename std::enable_if_t<std::is_destructible<Callable>::value>>
{
public:
  static void DeleteObj(void * obj)
  {
    using CallableDeref = std::remove_reference_t<Callable>;
    CallableDeref * callable = static_cast<CallableDeref *>(obj);
    callable->~CallableDeref();
  }
};

template <typename ReturnType>
struct DelegateReturnEmpty
{
  static ReturnType Process()
  {
    throw std::runtime_error("Calling unset delegate");
  }
};

template <>
struct DelegateReturnEmpty<void>
{
  static void Process()
  {

  }
};

template <typename T, bool Copyable>
struct DelegateCopy
{
  static void Process(const void * src, void * dst)
  {
    const T * src_ptr = static_cast<const T *>(src);
    T * dst_ptr = static_cast<T *>(dst);

    new(dst_ptr) T(*src_ptr);
  }
};

template <typename T>
struct DelegateCopy<T, false>
{
  static void Process(const void * src, void * dst)
  {
    ASSERT(false, "Attempting to copy a noncopyable delegate");
  }
};

template <typename T, bool Copyable>
struct DelegateMove
{
  static void Process(void * src, void * dst)
  {
    T * src_ptr = static_cast<T *>(src);
    T * dst_ptr = static_cast<T *>(dst);

    new(dst_ptr) T(std::move(*src_ptr));
  }
};

template <typename T>
struct DelegateMove<T, false>
{
  static void Process(const void * src, void * dst)
  {
    ASSERT(false, "Attempting to move a nonmovable delegate");
  }
};


template <typename ReturnType, typename ... Args>
struct DelegateCallbacks
{
  DelegateCallbacks() = default;

  template <typename Callable>
  DelegateCallbacks(const Callable & callable, ReturnType(*caller)(void * obj, Args ... args)) :
    m_Caller(caller)
  {
    m_Deleter = [](void * obj) { Callable * callable = static_cast<Callable *>(obj); callable->~Callable(); };
    m_Copier = [](const void * src, void * dst) { DelegateCopy<Callable, std::is_copy_constructible<Callable>::value>::Process(src, dst); };
    m_Mover = [](void * src, void * dst) { DelegateMove<Callable, std::is_move_constructible<Callable>::value>::Process(src, dst); };
    m_HasCopy = std::is_copy_constructible<Callable>::value;
    m_HasMove = std::is_move_constructible<Callable>::value;
  }

  ReturnType(*m_Caller)(void * obj, Args ... args);
  void(*m_Deleter)(void * obj);
  void(*m_Copier)(const void * src, void * dst);
  void(*m_Mover)(void * src, void * dst);

  bool m_HasCopy;
  bool m_HasMove;
};

template <typename ReturnType, typename ... Args>
class Delegate
{
public:
  Delegate() :
    m_Callbacks(nullptr)
  {
    
  }

  Delegate(const Delegate<ReturnType, Args...> & rhs) noexcept
  {
    m_Callbacks = rhs.m_Callbacks;

    if (m_Callbacks)
    {
      m_Callbacks->m_Copier(rhs.m_Buffer, m_Buffer);
    }
  }

  Delegate(Delegate<ReturnType, Args...> && rhs) noexcept
  {
    m_Callbacks = rhs.m_Callbacks;

    if (m_Callbacks)
    {
      if (m_Callbacks->m_Mover)
      {
        m_Callbacks->m_Mover(rhs.m_Buffer, m_Buffer);
      }
      else
      {
        m_Callbacks->m_Copier(rhs.m_Buffer, m_Buffer);
      }

      m_Callbacks->m_Deleter(rhs.m_Buffer);
      rhs.m_Callbacks = nullptr;
    }
  }

  template <typename Callable, typename std::enable_if_t<
    !std::is_same<std::decay_t<Callable>, Delegate<ReturnType, Args...>>::value &&
     std::is_class<std::decay_t<Callable>>::value> * Enable = nullptr>
  Delegate(Callable && callable)
  {
    static_assert(sizeof(Callable) < kMaxDelegateSize, "Delegate cannot fit this callable");
    new (m_Buffer) std::decay_t<Callable>(std::move(callable));

    static DelegateCallbacks<ReturnType, Args...> callbacks(callable, [](void * obj, Args ... args) -> ReturnType 
    { 
      typename std::decay_t<Callable> * c = static_cast<typename std::decay_t<Callable> *>(obj);
      return (*c)(std::forward<Args>(args)...); 
    });

    m_Callbacks = &callbacks;
  }

  template <typename C>
  Delegate(ReturnType(C::*func)(Args ... args), C * c) :
    Delegate([=](Args ... args) -> ReturnType { return (c->*func)(std::forward<Args>(args)...); })
  {

  }

  ~Delegate()
  {
    Clear();
  }

  Delegate & operator = (const Delegate & rhs) noexcept
  {
    Clear();

    m_Callbacks = rhs.m_Callbacks;

    if (m_Callbacks)
    {
      m_Callbacks->m_Copier(rhs.m_Buffer, m_Buffer);
    }

    return *this;
  }

  Delegate & operator = (Delegate && rhs) noexcept
  {
    Clear();

    m_Callbacks = rhs.m_Callbacks;
    if (m_Callbacks)
    {
      if (m_Callbacks->m_Mover)
      {
        m_Callbacks->m_Mover(rhs.m_Buffer, m_Buffer);
      }
      else
      {
        m_Callbacks->m_Copier(rhs.m_Buffer, m_Buffer);
      }

      m_Callbacks->m_Deleter(rhs.m_Buffer);
      rhs.m_Callbacks = nullptr;
    }

    return *this;
  }

  ReturnType Call(Args ... args)
  {
    if (m_Callbacks == nullptr)
    {
      return DelegateReturnEmpty<ReturnType>::Process();
    }

    return m_Callbacks->m_Caller(m_Buffer, std::forward<Args>(args)...);
  }

  ReturnType operator ()(Args ... args)
  {
    if (m_Callbacks == nullptr)
    {
      return DelegateReturnEmpty<ReturnType>::Process();
    }

    return m_Callbacks->m_Caller(m_Buffer, std::forward<Args>(args)...);
  }

  void Clear()
  {
    if (m_Callbacks != nullptr)
    {
      m_Callbacks->m_Deleter(m_Buffer);
    }

    m_Callbacks = nullptr;
  }

  bool IsValid()
  {
    return m_Callbacks != nullptr;
  }

  operator bool()
  {
    return m_Callbacks != nullptr;
  }
  
private:

  unsigned char m_Buffer[kMaxDelegateSize];
  NullOptPtr<DelegateCallbacks<ReturnType, Args...>> m_Callbacks;
};
