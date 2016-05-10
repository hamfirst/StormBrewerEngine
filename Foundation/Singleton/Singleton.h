#pragma once

#include "Foundation\CallList\CallList.h"
#include "Foundation\Reflection\TypeInfo.h"

extern PreMainCallList g_SingletonInitCallList;

template <class T>
class Singleton
{
public:

  Singleton()
  {
    static T singleton;
    m_T = &singleton;

    AddInit<HasInit<T>::value>();
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

  template <bool>
  void AddInit()
  {

  }

  template <>
  void AddInit<true>()
  {
    g_SingletonInitCallList.AddCall([=]() {m_T->Init(); });
  }
};

