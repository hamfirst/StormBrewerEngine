#pragma once

#include <typeinfo>

#include "Foundation/Optional/NullOpt.h"

class Any
{
public:

  Any();

  template <typename T>
  explicit Any(const T & t, std::enable_if_t<std::is_same<std::decay_t<T>, Any>::value == false> * Enable = 0)
  {
    m_Ptr = new T(t);
    m_Deleter = [](void * ptr) { delete static_cast<T *>(ptr); };
    m_Type = typeid(T).hash_code();
  }

  template <typename T>
  explicit Any(T && t, std::enable_if_t<std::is_same<std::decay_t<T>, Any>::value == false> * Enable = 0)
  {
    m_Ptr = new T(std::move(t));
    m_Deleter = [](void * ptr) { delete static_cast<T *>(ptr); };
    m_Type = typeid(T).hash_code();
  }

  Any(const Any & rhs) = delete;
  Any(Any && rhs);

  Any & operator = (const Any & any) = delete;
  Any & operator = (Any && any);

  ~Any();

  void Clear();

  template <typename T>
  NullOptPtr<T> Get()
  {
    return m_Type == typeid(T).hash_code() ? static_cast<T *>(m_Ptr) : nullptr;
  }

  template <typename T>
  NullOptPtr<const T> Get() const
  {
    return m_Type == typeid(T).hash_code() ? static_cast<const T *>(m_Ptr) : nullptr;
  }

  operator bool() const
  {
    return m_Ptr != nullptr;
  }

  void * GetRaw()
  {
    return m_Ptr;
  }

  const void * GetRaw() const
  {
    return m_Ptr;
  }

private:
  void * m_Ptr;
  void(*m_Deleter)(void *);
  std::size_t m_Type;
};

class AnyPtr
{
  AnyPtr();

  template <typename T>
  explicit AnyPtr(T * t)
  {
    m_Ptr = t;
    m_Type = typeid(T).hash_code();
  }

  AnyPtr(const AnyPtr & rhs);
  AnyPtr(AnyPtr && rhs);

  AnyPtr & operator = (const AnyPtr & any);
  AnyPtr & operator = (AnyPtr && any);

  template <typename T>
  AnyPtr & operator = (T * t)
  {
    m_Ptr = t;
    m_Type = typeid(T).hash_code();
    return *this;
  }

  ~AnyPtr();

  void Clear();

  template <typename T>
  NullOptPtr<T> Get()
  {
    return m_Type == typeid(T).hash_code() ? static_cast<T *>(m_Ptr) : nullptr;
  }

  template <typename T>
  NullOptPtr<const T> Get() const
  {
    return m_Type == typeid(T).hash_code() ? static_cast<const T *>(m_Ptr) : nullptr;
  }

  operator bool() const
  {
    return m_Ptr != nullptr;
  }

  void * m_Ptr;
  std::size_t m_Type;
};

template <int BufferSize, typename AlignType = void *>
class StaticAny
{
public:

  StaticAny()
  {
    m_Type = 0;
  }

  template <typename T>
  explicit StaticAny(const T & t, std::enable_if_t<std::is_same<std::decay_t<T>, StaticAny<BufferSize, AlignType>>::value == false> * Enable = 0)
  {
    new (m_Buffer) T(t);
    m_Copier = [](const void * src, void * dst) { new(dst) T(*(const T *)src); };
    m_Mover = [](void * src, void * dst) { new(dst) T(std::move(*(T *)src)); };
    m_Deleter = [](void * ptr) { static_cast<T *>(ptr)->~T(); };
    m_Type = typeid(T).hash_code();
  }

  template <typename T>
  explicit StaticAny(T && t, std::enable_if_t<std::is_same<std::decay_t<T>, Any>::value == false> * Enable = 0)
  {
    new (m_Buffer) T(std::move(t));
    m_Copier = [](const void * src, void * dst) { new(dst) T(*(const T *)src); };
    m_Mover = [](void * src, void * dst) { new(dst) T(std::move(*(T *)src)); };
    m_Deleter = [](void * ptr) { static_cast<T *>(ptr)->~T(); };
    m_Type = typeid(T).hash_code();
  }

  StaticAny(const StaticAny<BufferSize, AlignType> & rhs) :
    m_Type(rhs.m_Type),
    m_Copier(rhs.m_Copier),
    m_Mover(rhs.m_Mover),
    m_Deleter(rhs.m_Deleter)
  {
    if (m_Type != 0)
    {
      rhs.m_Copier(rhs.m_Buffer, m_Buffer);
    }
  }

  StaticAny(StaticAny<BufferSize, AlignType> && rhs) :
    m_Type(rhs.m_Type),
    m_Copier(rhs.m_Copier),
    m_Mover(rhs.m_Mover),
    m_Deleter(rhs.m_Deleter)
  {
    if (m_Type != 0)
    {
      rhs.m_Mover(rhs.m_Buffer, m_Buffer);
    }
  }

  StaticAny<BufferSize, AlignType> & operator = (const StaticAny<BufferSize, AlignType> & any)
  {
    Clear();
    m_Type = any.m_Type;
    m_Copier = any.m_Copier;
    m_Mover = any.m_Mover;
    m_Deleter = any.m_Deleter;

    if (m_Type != 0)
    {
      any.m_Copier(any.m_Buffer, m_Buffer);
    }
    return *this;
  }

  StaticAny<BufferSize, AlignType> & operator = (StaticAny<BufferSize, AlignType> && any)
  {
    Clear();
    m_Type = any.m_Type;
    m_Copier = any.m_Copier;
    m_Mover = any.m_Mover;
    m_Deleter = any.m_Deleter;

    if (m_Type != 0)
    {
      any.m_Mover(any.m_Buffer, m_Buffer);
    }
    return *this;
  }

  ~StaticAny()
  {
    if (m_Type != 0)
    {
      m_Deleter(m_Buffer);
    }
  }

  void Clear()
  {
    if (m_Type != 0)
    {
      m_Deleter(m_Buffer);
      m_Type = 0;
    }
  }

  template <typename T>
  NullOptPtr<T> Get()
  {
    return m_Type == typeid(T).hash_code() ? reinterpret_cast<T *>(&m_Buffer[0]) : nullptr;
  }

  template <typename T>
  NullOptPtr<const T> Get() const
  {
    return m_Type == typeid(T).hash_code() ? reinterpret_cast<const T *>(&m_Buffer[0]) : nullptr;
  }

  operator bool() const
  {
    return m_Type != 0;
  }

private:
  std::size_t m_Type;
  void(*m_Copier)(const void *, void *);
  void(*m_Mover)(void *, void *);
  void(*m_Deleter)(void *);
  alignas(alignof(AlignType)) char m_Buffer[BufferSize];
};