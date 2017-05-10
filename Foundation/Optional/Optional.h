#pragma once


template <class T>
class Optional
{
public:
  Optional() = default;

  Optional(const Optional<T> & rhs)
  {
    m_Valid = rhs.m_Valid;
    if (m_Valid)
    {
      const T * src = reinterpret_cast<const T *>(rhs.m_Buffer);
      new(m_Buffer) T(*src);
    }
  }

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

  Optional(const T & rhs) :
    m_Valid(true)
  {
    new(m_Buffer) T(rhs);
  }

  Optional(T && rhs) :
    m_Valid(true)
  {
    new(m_Buffer) T(std::move(rhs));
  }

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

  bool m_Valid = false;
  char m_Buffer[sizeof(T)];

};

