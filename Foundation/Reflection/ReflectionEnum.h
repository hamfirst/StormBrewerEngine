#pragma once

#include "Foundation\Reflection\Reflection.h"

template <class EnumType>
class REnum
{
public:
  REFLECTION_CHANGE_NOTIFIER_INFO;

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

  operator EnumType() const
  {
    return m_Value;
  }

  int _to_integral() const
  {
    return m_Value._to_integral();
  }

  const char * _to_string() const
  {
    return m_Value._to_string();
  }

  bool operator == (EnumType val) const
  {
    return m_Value == val;
  }

  bool operator == (const REnum<EnumType> & val) const
  {
    return m_Value == val.m_Value;
  }

  bool operator != (EnumType val) const
  {
    return m_Value != val;
  }

  bool operator < (EnumType val) const
  {
    return m_Value < val;
  }

  bool operator <= (EnumType val) const
  {
    return m_Value <= val;
  }

  bool operator > (EnumType val) const
  {
    return m_Value > val;
  }

  bool operator >= (EnumType val) const
  {
    return m_Value >= val;
  }

private:
  void Set(EnumType val)
  {
    m_Value = val;

#ifdef REFLECTION_CHANGE_NOTIFIER
    ReflectionNotifySet(m_ReflectionInfo, _to_string());
#endif
  }

  EnumType m_Value;
};
