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

private:
  void * m_Ptr;
  void(*m_Deleter)(void *);
  std::size_t m_Type;
};
