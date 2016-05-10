#pragma once

#include <type_traits>

#include "Foundation\Reflection\Reflection.h"
#include "Foundation\Reflection\ReflectionChangeNotifier.h"

class RBool
{
public:
  REFLECTION_PARENT_INFO;

  RBool()
  {
    m_Value = false;
  }

  RBool(bool val)
  {
    m_Value = val;
  }

  bool operator = (bool val)
  {
    Set(m_Value);
    return m_Value;
  }

  operator bool() const
  {
    return m_Value;
  }

  bool operator !() const
  {
    return !m_Value;
  }

  bool operator ==(bool val) const
  {
    return m_Value == val;
  }

  bool operator !=(bool val) const
  {
    return m_Value != val;
  }

private:
  void Set(bool val)
  {
    m_Value = val;

#ifdef REFLECTION_PARENT
    ReflectionNotifySet(m_ReflectionInfo, m_Value);
#endif
  }

  bool m_Value;
};

template <class NumericType>
class RNumber
{
public:
  REFLECTION_PARENT_INFO;

  RNumber()
  {
    m_Value = 0;
  }

  RNumber(NumericType val)
  {
    m_Value = val;
  }

  RNumber(const RNumber & val)
  {
    m_Value = val.m_Value;
  }

  NumericType operator = (NumericType val)
  {
    Set(val);
    return m_Value;
  }

  operator NumericType() const
  {
    return m_Value;
  }

  operator bool () const
  {
    return m_Value != 0;
  }

  NumericType operator ++()
  {
    Set(m_Value + 1);
    return m_Value;
  }

  NumericType operator --()
  {
    Set(m_Value - 1);
    return m_Value;
  }

  NumericType operator !() const
  {
    return !m_Value;
  }

  NumericType operator + (NumericType val) const
  {
    return m_Value + val;
  }

  NumericType operator += (NumericType val)
  {
    Set(m_Value + val);
    return m_Value;
  }

  NumericType operator - (NumericType val) const
  {
    return m_Value - val;
  }

  NumericType operator -= (NumericType val)
  {
    Set(m_Value - val);
    return m_Value;
  }

  NumericType operator * (NumericType val) const
  {
    return m_Value * val;
  }

  NumericType operator *= (NumericType val)
  {
    Set(m_Value * val);
    return m_Value;
  }

  NumericType operator / (NumericType val) const
  {
    return m_Value / val;
  }

  NumericType operator /= (NumericType val)
  {
    Set(m_Value / val);
    return m_Value;
  }

  template <class T = NumericType>
  typename std::enable_if<std::is_integral<T>::value, T>::type operator % (NumericType val) const
  {
    return m_Value % val;
  }

  template <class T = NumericType>
  typename std::enable_if<std::is_integral<T>::value, T>::type operator %= (NumericType val)
  {
    Set(m_Value % val);
    return m_Value;
  }

  template <class T = NumericType>
  typename std::enable_if<std::is_integral<T>::value, T>::type operator & (NumericType val) const
  {
    return m_Value & val;
  }

  template <class T = NumericType>
  typename std::enable_if<std::is_integral<T>::value, T>::type operator &= (NumericType val)
  {
    Set(m_Value & val);
    return m_Value;
  }

  template <class T = NumericType>
  typename std::enable_if<std::is_integral<T>::value, T>::type operator | (NumericType val) const
  {
    return m_Value | val;
  }

  template <class T = NumericType>
  typename std::enable_if<std::is_integral<T>::value, T>::type operator |= (NumericType val)
  {
    Set(m_Value | val);
    return m_Value;
  }

  template <class T = NumericType>
  typename std::enable_if<std::is_integral<T>::value, T>::type operator ^ (NumericType val) const
  {
    return m_Value ^ val;
  }

  template <class T = NumericType>
  typename std::enable_if<std::is_integral<T>::value, T>::type operator ^= (NumericType val)
  {
    Set(m_Value ^ val);
    return m_Value;
  }

  template <class T = NumericType>
  typename std::enable_if<std::is_integral<T>::value, T>::type operator ~ () const
  {
    return ~m_Value;
  }

  template <class T = NumericType>
  typename std::enable_if<std::is_integral<T>::value, T>::type operator >> (NumericType val) const
  {
    return m_Value >> val;
  }

  template <class T = NumericType>
  typename std::enable_if<std::is_integral<T>::value, T>::type operator >>= (NumericType val)
  {
    Set(m_Value >> val);
    return m_Value;
  }

  template <class T = NumericType>
  typename std::enable_if<std::is_integral<T>::value, T>::type operator << (NumericType val) const
  {
    return m_Value << val;
  }

  template <class T = NumericType>
  typename std::enable_if<std::is_integral<T>::value, T>::type operator <<= (NumericType val)
  {
    Set(m_Value << val);
    return m_Value;
  }

  bool operator == (NumericType val) const
  {
    return m_Value == val;
  }

  bool operator != (NumericType val) const
  {
    return m_Value != val;
  }

  bool operator > (NumericType val) const
  {
    return m_Value > val;
  }

  bool operator >= (NumericType val) const
  {
    return m_Value >= val;
  }

  bool operator < (NumericType val) const
  {
    return m_Value < val;
  }

  bool operator <= (NumericType val) const
  {
    return m_Value <= val;
  }

private:
  void Set(NumericType val)
  {
    m_Value = val;

#ifdef REFLECTION_PARENT
    ReflectionNotifySet(m_ReflectionInfo, m_Value);
#endif
  }

  NumericType m_Value;
};
