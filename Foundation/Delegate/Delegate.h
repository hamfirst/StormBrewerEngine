#pragma once

#include <type_traits>
#include <utility>

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

template <typename ReturnType, typename ... Args>
class Delegate
{
public:
  Delegate() :
    m_Valid(false)
  {
    
  }

  Delegate(const Delegate<ReturnType, Args...> & rhs) noexcept
  {
    m_Valid = rhs.m_Valid;
    if (m_Valid)
    {
      m_Caller = rhs.m_Caller;
      m_Deleter = rhs.m_Deleter;
      m_Copier = rhs.m_Copier;

      m_Copier(rhs.m_Buffer, m_Buffer);
    }
    else
    {
      m_Caller = nullptr;
      m_Deleter = nullptr;
      m_Copier = nullptr;
    }
  }

  Delegate(Delegate<ReturnType, Args...> && rhs) noexcept
  {
    m_Valid = rhs.m_Valid;
    if (m_Valid)
    {
      m_Caller = rhs.m_Caller;
      m_Deleter = rhs.m_Deleter;
      m_Copier = rhs.m_Copier;

      m_Copier(rhs.m_Buffer, m_Buffer);
      if (m_Deleter)
      {
        m_Deleter(rhs.m_Buffer);
      }

      rhs.m_Valid = false;
    }
    else
    {
      m_Caller = nullptr;
      m_Deleter = nullptr;
      m_Copier = nullptr;
    }
  }


  template <typename Callable, typename std::enable_if_t<
    !std::is_same<std::decay_t<Callable>, Delegate<ReturnType, Args...>>::value &&
     std::is_class<std::remove_reference_t<Callable>>::value> * Enable = nullptr>
  Delegate(Callable && callable)
  {
    static_assert(sizeof(Callable) < kMaxDelegateSize, "Delegate cannot fit this callable");
    new (m_Buffer) std::remove_reference_t<Callable>(callable);

    m_Caller = [](void * obj, Args ... args) 
    { 
      std::remove_reference_t<Callable> * callable = static_cast<std::remove_reference_t<Callable> *>(obj);
      return (*callable)(std::forward<Args>(args)...);
    };

    m_Copier = [](const void * src, void * dst)
    {
      const std::remove_reference_t<Callable> * callable = static_cast<const std::remove_reference_t<Callable> *>(src);
      new (dst) std::remove_reference_t<Callable>(*callable);
    };

    m_Deleter = &DelegateDeleter<Callable>::DeleteObj;
    m_Valid = true;
  }

  Delegate(ReturnType(*func)(Args ... args))
  {
    struct DelData
    {
      ReturnType(*m_Func)(Args ... args);
    };

    DelData * func_buffer = reinterpret_cast<DelData *>(m_Buffer);
    func_buffer->m_Func = func;

    m_Copier = [](const void * src, void * dst)
    {
      const DelData * func_buffer_src = static_cast<const DelData *>(src);
      DelData * func_buffer_dst = static_cast<DelData *>(dst);
      *func_buffer_dst = *func_buffer_src;
    };

    m_Caller = [](void * obj, Args ... args)
    {
      DelData * func_buffer = static_cast<DelData *>(obj);
      return func_buffer->m_Func(args...);
    };

    m_Deleter = nullptr;
    m_Valid = true;
  }

  template <typename C>
  Delegate(ReturnType(C::*func)(Args ... args), C * c)
  {
    struct DelData
    {
      ReturnType(C::*m_Func)(Args ... args);
      C * m_C;
    };
    
    DelData * func_buffer = reinterpret_cast<DelData *>(m_Buffer);
    func_buffer->m_Func = func;
    func_buffer->m_C = c;

    m_Copier = [](const void * src, void * dst)
    {
      const DelData * func_buffer_src = static_cast<const DelData *>(src);
      DelData * func_buffer_dst = static_cast<DelData *>(dst);
      *func_buffer_dst = *func_buffer_src;
    };

    m_Caller = [](void * obj, Args ... args)
    {
      DelData * func_buffer = static_cast<DelData *>(obj);

      auto func = func_buffer->m_Func;
      auto c = func_buffer->m_C;
      return (c->*func)(args...);
    };

    m_Deleter = nullptr;
    m_Valid = true;
  }

  ~Delegate()
  {
    Clear();
  }

  Delegate & operator = (const Delegate & rhs) noexcept
  {
    Clear();

    m_Valid = rhs.m_Valid;
    if (m_Valid)
    {
      m_Caller = rhs.m_Caller;
      m_Deleter = rhs.m_Deleter;
      m_Copier = rhs.m_Copier;

      m_Copier(rhs.m_Buffer, m_Buffer);
    }

    return *this;
  }

  Delegate & operator = (Delegate && rhs) noexcept
  {
    Clear();

    m_Valid = rhs.m_Valid;
    if (m_Valid)
    {
      m_Caller = rhs.m_Caller;
      m_Deleter = rhs.m_Deleter;
      m_Copier = rhs.m_Copier;

      m_Copier(rhs.m_Buffer, m_Buffer);
      if (m_Deleter)
      {
        m_Deleter(rhs.m_Buffer);
      }

      rhs.m_Valid = false;
    }

    return *this;
  }

  ReturnType Call(Args ... args)
  {
    if (m_Valid == false)
    {
      return DelegateReturnEmpty<ReturnType>::Process();
    }

    return m_Caller(m_Buffer, std::forward<Args>(args)...);
  }

  ReturnType operator ()(Args ... args)
  {
    if (m_Valid == false)
    {
      return DelegateReturnEmpty<ReturnType>::Process();
    }

    return m_Caller(m_Buffer, std::forward<Args>(args)...);
  }

  void Clear()
  {
    if (m_Valid && m_Deleter != nullptr)
    {
      m_Deleter(m_Buffer);
    }

    m_Caller = nullptr;
    m_Copier = nullptr;
    m_Deleter = nullptr;
    m_Valid = false;
  }

  bool IsValid()
  {
    return m_Valid;
  }

  operator bool()
  {
    return m_Valid;
  }
  
private:

  unsigned char m_Buffer[kMaxDelegateSize];
  ReturnType(*m_Caller)(void * obj, Args ... args) = nullptr;
  void (*m_Deleter)(void * obj) = nullptr;
  void (*m_Copier)(const void * src, void * dst) = nullptr;
  bool m_Valid = false;
};
