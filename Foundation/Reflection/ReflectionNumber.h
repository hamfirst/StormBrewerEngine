#pragma once

#include <type_traits>

#include "Foundation\Reflection\Reflection.h"
#include "Foundation\Reflection\ReflectionChangeNotifier.h"

class RBool
{
public:
  REFLECTION_CHANGE_NOTIFIER_INFO;

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

  bool operator == (const RBool & val) const
  {
    return m_Value != val.m_Value;
  }

private:
  void Set(bool val)
  {
    m_Value = val;

#ifdef REFLECTION_CHANGE_NOTIFIER
    ReflectionNotifySet(m_ReflectionInfo, m_Value);
#endif
  }

  bool m_Value;
};

static bool ParseBool(const std::string & val)
{
  if (val == "true")
  {
    return true;
  }
  else if (val == "false")
  {
    return false;
  }
  else
  {
    throw std::runtime_error("Invalid bool");
  }
}

template <class NumericType>
class RNumber
{
public:
  REFLECTION_CHANGE_NOTIFIER_INFO;

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

  float AsFloat() const
  {
    return (float)m_Value;
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

#ifdef REFLECTION_CHANGE_NOTIFIER
    ReflectionNotifySet(m_ReflectionInfo, m_Value);
#endif
  }

  NumericType m_Value;
};

template <typename NumericType>
static NumericType ParseNumber(const std::string & str)
{
  return static_cast<NumericType>(std::stoll(str));
}

template <>
static uint8_t ParseNumber(const std::string & str)
{
  return static_cast<uint8_t>(std::stoull(str));
}

template <>
static uint16_t ParseNumber(const std::string & str)
{
  return static_cast<uint16_t>(std::stoull(str));
}

template <>
static uint32_t ParseNumber(const std::string & str)
{
  return static_cast<uint32_t>(std::stoull(str));
}

template <>
static uint64_t ParseNumber(const std::string & str)
{
  return static_cast<uint64_t>(std::stoull(str));
}

template <>
static float ParseNumber(const std::string & str)
{
  return static_cast<float>(std::stof(str));
}