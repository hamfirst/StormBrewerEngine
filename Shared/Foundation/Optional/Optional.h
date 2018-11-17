#pragma once

#include <type_traits>

template <class T>
class Optional
{
public:
  using MyType = T;

  Optional() :
    m_Valid(false)
  {

  }
  
  template <typename U = T, typename std::enable_if<std::is_copy_constructible<U>::value, int>::type = 0>
  Optional(const Optional<T> & rhs)
  {
    m_Valid = rhs.m_Valid;
    if (m_Valid)
    {
      const T * src = reinterpret_cast<const T *>(rhs.m_Buffer);
      new(m_Buffer) T(*src);
    }
  }

  template <typename U = T, typename std::enable_if<std::is_move_constructible<U>::value, int>::type = 0>
  Optional(Optional<T> && rhs)
  {
    m_Valid = rhs.m_Valid;
    if (m_Valid)
    {
      T * src = reinterpret_cast<T *>(rhs.m_Buffer);
      new(m_Buffer) T(std::move(*src));
      rhs.Clear();
    }
  }

  template <typename U = T, typename std::enable_if<std::is_copy_constructible<U>::value, int>::type = 0>
  Optional(const T & rhs) :
    m_Valid(true)
  {
    new(m_Buffer) T(rhs);
  }
  
  template <typename U = T, typename std::enable_if<std::is_move_constructible<U>::value, int>::type = 0>
  Optional(T && rhs) :
    m_Valid(true)
  {
    new(m_Buffer) T(std::move(rhs));
  }

  template <typename U = T, typename std::enable_if<std::is_copy_constructible<U>::value, int>::type = 0>
  Optional<T> & operator =(const Optional<T> & rhs)
  {
    Clear();
    m_Valid = rhs.m_Valid;
    if (m_Valid)
    {
      const T * src = reinterpret_cast<const T *>(rhs.m_Buffer);
      new(m_Buffer) T(*src);
    }

    return *this;
  }
  
  template <typename U = T, typename std::enable_if<std::is_move_constructible<U>::value, int>::type = 0>
  Optional<T> & operator =(Optional<T> && rhs)
  {
    Clear();
    m_Valid = rhs.m_Valid;
    if (m_Valid)
    {
      T * src = reinterpret_cast<T *>(rhs.m_Buffer);
      new(m_Buffer) T(std::move(*src));
      rhs.Clear();
    }
    return *this;
  }
  
  template <typename U = T, typename std::enable_if<std::is_copy_constructible<U>::value, int>::type = 0>
  Optional<T> & operator =(const T & rhs)
  {
    Clear();
    m_Valid = true;
    new(m_Buffer) T(rhs);
    
    return *this;
  }
  
  template <typename U = T, typename std::enable_if<std::is_move_constructible<U>::value, int>::type = 0>
  Optional<T> & operator =(T && rhs)
  {
    Clear();
    m_Valid = true;
    new(m_Buffer) T(std::move(rhs));
    return *this;
  }

  ~Optional()
  {
    Clear();
  }

  template <typename ... Args>
  T & Emplace(Args && ... args)
  {
    Clear();

    T * src  = new(m_Buffer) T(std::forward<Args>(args)...);
    m_Valid = true;
    return *src;
  }

  void Clear()
  {
    if (m_Valid)
    {
      T * ptr = reinterpret_cast<T *>(m_Buffer);
      ptr->~T();
    }

    m_Valid = false;
  }

  operator bool() const
  {
    return m_Valid;
  }

  bool IsValid() const
  {
    return m_Valid;
  }

  T & Value()
  {
    if (!m_Valid)
    {
      throw false;
    }

    return *reinterpret_cast<T *>(m_Buffer);
  }

  const T & Value() const
  {
    if (!m_Valid)
    {
      throw false;
    }

    return *reinterpret_cast<const T *>(m_Buffer);
  }

  T & operator *()
  {
    if (!m_Valid)
    {
      throw false;
    }

    return *reinterpret_cast<T *>(m_Buffer);
  }

  const T & operator *() const
  {
    if (!m_Valid)
    {
      throw false;
    }

    return *reinterpret_cast<const T *>(m_Buffer);
  }

  T * operator ->()
  {
    if (!m_Valid)
    {
      throw false;
    }

    return reinterpret_cast<T *>(m_Buffer);
  }

  const T * operator ->() const
  {
    if (!m_Valid)
    {
      throw false;
    }

    return reinterpret_cast<const T *>(m_Buffer);
  }

  T * GetPtr()
  {
    if (!m_Valid)
    {
      return nullptr;
    }

    return reinterpret_cast<T *>(m_Buffer);
  }

  const T * GetPtr() const
  {
    if (!m_Valid)
    {
      return nullptr;
    }

    return reinterpret_cast<const T *>(m_Buffer);
  }

public:

  bool m_Valid;
  alignas(alignof(T)) unsigned char m_Buffer[sizeof(T)];

};

