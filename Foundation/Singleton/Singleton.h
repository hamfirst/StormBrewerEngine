#pragma once

#include "Foundation/CallList/CallList.h"

extern PreMainCallList g_SingletonInitCallList;

template <typename T>
class SingletonHasInit final
{
  typedef char true_type;
  typedef long false_type;

  template <typename C> static true_type test(decltype(&C::Init));
  template <typename C> static false_type test(...);

public:
  enum { value = sizeof(test<T>(0)) == sizeof(true_type) };
};

template <bool Register>
struct SingletonRegisterInit
{
  template <typename T>
  static void Register(T * t)
  {
    g_SingletonInitCallList.AddCall([=]() {t->Init(); });
  }
};

template <>
struct SingletonRegisterInit<false>
{
  template <typename T>
  static void Register(T * t)
  {
  }
};

template <class T>
class Singleton
{
public:

  Singleton()
  {
    static T singleton;
    m_T = &singleton;

    SingletonRegisterInit<SingletonHasInit<T>::value>::Register(m_T);
  }

  T * operator * ()
  {
    return m_T;
  }

  const T * operator * () const
  {
    return m_T;
  }

  T * operator -> ()
  {
    return m_T;
  }

  const T * operator -> () const
  {
    return m_T;
  }

private:
  T * m_T;
};

