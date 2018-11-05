#pragma once

#include <typeinfo>
#include <type_traits>

#include "Foundation/Optional/NullOpt.h"
#include "Foundation/Assert/Assert.h"

#include "StormRefl/StormReflMetaInfoBase.h"
#include "StormRefl/StormReflMetaFuncs.h"

template <typename T>
class Castable;

template <typename T>
struct IsCastable : public std::false_type {};

template <typename T>
struct IsCastable<Castable<T>> : public std::true_type {};

template <typename T>
class Castable
{
public:

  Castable()
  {
    m_Object = nullptr;
    m_ObjectCast = nullptr;
  }

  template <typename R>
  explicit Castable(R & r)
  {
    if constexpr (std::is_same_v<R, T>)
    {
      m_Object = &r;
      m_ObjectCast = static_cast<void * (*)(std::size_t, void *)>(&StormReflTypeInfo<T>::CastFromTypeIdHash);
    }
    else
    {
      if constexpr (IsCastable<R>::value)
      {
        m_Object = r.m_ObjectCast(typeid(T).hash_code(), &r);

        if(m_Object)
        {
          m_ObjectCast = r.m_ObjectCast;
        }
        else
        {
          m_ObjectCast = nullptr;
        }
      }
      else
      {

        m_Object = StormReflTypeInfo<T>::CastFromTypeIdHash(typeid(R).hash_code(), &r);

        if(m_Object)
        {
          m_ObjectCast = &StormReflTypeInfo<R>::CastFromTypeIdHash;
        }
        else
        {
          m_ObjectCast = nullptr;
        }
      }

    }
  }

  Castable(const Castable<T> & rhs) = default;
  Castable(Castable<T> && rhs) = default;
  Castable<T> & operator = (const Castable<T> & rhs) = default;
  Castable<T> & operator = (Castable<T> && rhs) = default;

  template <typename R>
  NullOptPtr<R> CastTo() const
  {
    return static_cast<R *>(m_ObjectCast(typeid(R).hash_code(), m_Object));
  }

  NullOptPtr<T> operator -> ()
  {
    return m_Object;
  }

  NullOptPtr<const T> operator -> () const
  {
    return m_Object;
  }

  T * Value() const
  {
    return m_Object;
  }

  T & operator * ()
  {
    ASSERT(m_Object, "Dereferencing invalid castable");
    return *m_Object;
  }

  const T & operator *() const
  {
    ASSERT(m_Object, "Dereferencing invalid castable");
    return *m_Object;
  }

  void Clear()
  {
    m_Object = nullptr;
    m_ObjectCast = nullptr;
  }

  explicit operator bool () const
  {
    return m_Object != nullptr;
  }

private:
  T * m_Object;
  void * (*m_ObjectCast)(std::size_t, void *);
};

template <typename T>
class ConstCastable;

template <typename T>
struct IsConstCastable : public std::false_type {};

template <typename T>
struct IsConstCastable<ConstCastable<T>> : public std::true_type {};

template <typename T>
class ConstCastable
{
public:

  ConstCastable()
  {
    m_Object = nullptr;
    m_ObjectCast = nullptr;
  }

  template <typename R>
  explicit ConstCastable(const R & r)
  {
    if constexpr (std::is_same_v<R, T>)
    {
      m_Object = &r;
      m_ObjectCast = static_cast<const void * (*)(std::size_t, const void *)>(&StormReflTypeInfo<T>::CastFromTypeIdHash);
    }
    else
    {
      if constexpr (IsConstCastable<R>::value)
      {
        m_Object = r.m_ObjectCast(typeid(T).hash_code(), &r);

        if(m_Object)
        {
          m_ObjectCast = r.m_ObjectCast;
        }
        else
        {
          m_ObjectCast = nullptr;
        }
      }
      else
      {

        m_Object = StormReflTypeInfo<T>::CastFromTypeIdHash(typeid(R).hash_code(), &r);

        if(m_Object)
        {
          m_ObjectCast = &StormReflTypeInfo<R>::CastFromTypeIdHash;
        }
        else
        {
          m_ObjectCast = nullptr;
        }
      }

    }
  }

  ConstCastable(const ConstCastable<T> & rhs) = default;
  ConstCastable(ConstCastable<T> && rhs) = default;
  ConstCastable<T> & operator = (const ConstCastable<T> & rhs) = default;
  ConstCastable<T> & operator = (ConstCastable<T> && rhs) = default;

  template <typename R>
  NullOptPtr<const R> CastTo() const
  {
    return static_cast<const R *>(m_ObjectCast(typeid(R).hash_code(), m_Object));
  }

  NullOptPtr<const T> operator -> () const
  {
    return m_Object;
  }

  const T * Value() const
  {
    return m_Object;
  }

  const T & operator *() const
  {
    ASSERT(m_Object, "Dereferencing invalid castable");
    return *m_Object;
  }

  void Clear()
  {
    m_Object = nullptr;
    m_ObjectCast = nullptr;
  }

  explicit operator bool () const
  {
    return m_Object != nullptr;
  }

private:
  const T * m_Object;
  const void * (*m_ObjectCast)(std::size_t, const void *);
};

