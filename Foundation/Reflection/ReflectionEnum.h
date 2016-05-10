#pragma once

#include "Foundation\Reflection\Reflection.h"

template <class EnumType>
class REnum
{
public:
  REFLECTION_PARENT_INFO;

  REnum()
  {
    
  }

  REnum(EnumType val)
  {
    m_Value = val;
  }
  
  const EnumType & operator = (EnumType val)
  {
    Set(val);
    return m_Value;
  }

  operator int() const
  {
    return m_Value._to_integral();
  }

  int _to_integral() const
  {
    return m_Value._to_integral();
  }

  const char * _to_string() const
  {
    return m_Value._to_string();
  }

  bool operator == (EnumType val)
  {
    return m_Value != val;
  }

  bool operator != (EnumType val)
  {
    return m_Value != val;
  }

  bool operator < (EnumType val)
  {
    return m_Value < val;
  }

  bool operator <= (EnumType val)
  {
    return m_Value <= val;
  }

  bool operator > (EnumType val)
  {
    return m_Value > val;
  }

  bool operator >= (EnumType val)
  {
    return m_Value >= val;
  }

private:
  void Set(EnumType val)
  {
    m_Value = val;

#ifdef REFLECTION_PARENT
    ReflectionNotifySet(m_ReflectionInfo, _to_string());
#endif
  }

  EnumType m_Value;
};
