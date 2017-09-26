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
    m_Mover = [](void * src, void * dst) { new(dst) T(std::move(*(T *)src)); };
    m_Deleter = [](void * ptr) { delete static_cast<T *>(ptr); };
    m_Type = typeid(T).hash_code();
  }

  template <typename T>
  explicit StaticAny(T && t, std::enable_if_t<std::is_same<std::decay_t<T>, Any>::value == false> * Enable = 0)
  {
    new (m_Buffer) T(std::move(t));
    m_Mover = [](void * src, void * dst) { new(dst) T(std::move(*(T *)src)); };
    m_Deleter = [](void * ptr) { delete static_cast<T *>(ptr); };
    m_Type = typeid(T).hash_code();
  }

  StaticAny(const StaticAny<BufferSize, AlignType> & rhs) = delete;
  StaticAny(StaticAny<BufferSize, AlignType> && rhs) :
    m_Type(rhs.m_Type),
    m_Mover(rhs.m_Mover),
    m_Deleter(rhs.m_Deleter)
  {
    if (m_Type != 0)
    {
      rhs.m_Mover(m_Buffer, rhs.m_Buffer);
    }
  }

  StaticAny<BufferSize, AlignType> & operator = (const StaticAny<BufferSize, AlignType> & any) = delete;
  StaticAny<BufferSize, AlignType> & operator = (StaticAny<BufferSize, AlignType> && any)
  {
    Clear();
    m_Type = any.m_Type;
    m_Mover = any.m_Mover;
    m_Deleter = any.m_Deleter;

    if (m_Type != 0)
    {
      any.m_Mover(m_Buffer, any.m_Buffer);
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
    return m_Type == typeid(T).hash_code() ? static_cast<T *>(m_Buffer) : nullptr;
  }

  template <typename T>
  NullOptPtr<const T> Get() const
  {
    return m_Type == typeid(T).hash_code() ? static_cast<const T *>(m_Buffer) : nullptr;
  }

  operator bool() const
  {
    return m_Type != 0;
  }

private:
  std::size_t m_Type;
  void(*m_Mover)(void *, void *);
  void(*m_Deleter)(void *);
  alignas(alignof(AlignType)) char m_Buffer[BufferSize];
};