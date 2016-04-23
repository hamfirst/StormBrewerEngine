#pragma once

template <class T>
class Singleton
{
public:

  Singleton()
  {
    static T singleton;
    m_T = &singleton;
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


