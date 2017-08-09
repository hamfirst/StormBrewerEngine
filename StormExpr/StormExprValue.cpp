
#include <cstdlib>
#include <cstring>

#include "StormExprValue.h"
#include "StormExprValueProvider.h"

StormExprValue::StormExprValue() :
  m_Type(StormExprValueType::kNothing)
{

}

StormExprValue::StormExprValue(float val) :
  m_Type(StormExprValueType::kFloat),
  m_Float(val)
{

}

StormExprValue::StormExprValue(const char * str) :
  m_Type(StormExprValueType::kString)
{
  m_StrLen = strlen(str);
  m_String = (char *)malloc(m_StrLen + 1);
  memcpy(m_String, str, m_StrLen + 1);
}


StormExprValue::StormExprValue(const char * str1, const char * str2) :
  m_Type(StormExprValueType::kString)
{
  auto str1len = strlen(str1);
  auto str2len = strlen(str2);
  m_StrLen = str2len + str1len;
  m_String = (char *)malloc(m_StrLen + 1);
  memcpy(m_String, str1, str1len);
  memcpy(m_String + str1len, str2, str2len + 1);
}

StormExprValue::StormExprValue(const StormExprValue & rhs) :
  m_Type(rhs.m_Type)
{
  if (m_Type == StormExprValueType::kString)
  {
    m_String = (char *)malloc(rhs.m_StrLen + 1);
    m_StrLen = rhs.m_StrLen;

    memcpy(m_String, rhs.m_String, rhs.m_StrLen + 1);
  }
  else
  {
    m_Float = rhs.m_Float;
  }
}

StormExprValue::StormExprValue(StormExprValue && rhs) :
  m_Type(rhs.m_Type)
{
  if (m_Type == StormExprValueType::kString)
  {
    m_String = rhs.m_String;
    m_StrLen = rhs.m_StrLen;

    rhs.m_String = nullptr;
    rhs.m_Type = StormExprValueType::kNothing;
  }
  else
  {
    m_Float = rhs.m_Float;
  }
}

StormExprValue::~StormExprValue()
{
  if (m_Type == StormExprValueType::kString)
  {
    free(m_String);
  }
}

StormExprValue & StormExprValue::operator = (const StormExprValue & rhs)
{
  Clear();

  m_Type = rhs.m_Type;
  if (m_Type == StormExprValueType::kString)
  {
    m_String = (char *)malloc(rhs.m_StrLen + 1);
    m_StrLen = rhs.m_StrLen;

    memcpy(m_String, rhs.m_String, rhs.m_StrLen + 1);
  }
  else
  {
    m_Float = rhs.m_Float;
  }

  return *this;
}

StormExprValue & StormExprValue::operator = (StormExprValue && rhs)
{
  Clear();

  m_Type = rhs.m_Type;
  if (m_Type == StormExprValueType::kString)
  {
    m_String = rhs.m_String;
    m_StrLen = rhs.m_StrLen;

    rhs.m_String = nullptr;
    rhs.m_Type = StormExprValueType::kNothing;
  }
  else
  {
    m_Float = rhs.m_Float;
  }

  return *this;
}

bool StormExprValue::operator == (const StormExprValue & rhs) const
{
  if (m_Type != rhs.m_Type)
  {
    return false;
  }

  switch (m_Type)
  {
  case StormExprValueType::kNothing:
    return true;
  case StormExprValueType::kFloat:
    return m_Float == rhs.m_Float;
  case StormExprValueType::kString:
    return m_StrLen == rhs.m_StrLen ? !strcmp(m_String, rhs.m_String) : false;
  }
  return false;
}

bool StormExprValue::operator != (const StormExprValue & rhs) const
{
  bool eq = (*this == rhs);
  return !eq;
}

void StormExprValue::Clear()
{
  if (m_Type == StormExprValueType::kString)
  {
    free(m_String);
  }

  m_Type = StormExprValueType::kNothing;
}

StormExprValueType StormExprValue::GetType()
{
  return m_Type;
}

float StormExprValue::GetFloatVal()
{
  return m_Float;
}

const char * StormExprValue::GetStringVal()
{
  return m_String;
}

std::size_t StormExprValue::GetStringLength()
{
  return m_StrLen;
}

void StormExprValue::GetValueProvider(StormExprValueProvider & value_provider)
{
  switch (m_Type)
  {
  case StormExprValueType::kNothing:
    value_provider = StormExprValueProvider{};
    return;
  case StormExprValueType::kFloat:
    value_provider = StormExprValueProvider(&m_Float);
    return;
  case StormExprValueType::kString:
    value_provider = StormExprValueProvider(&m_String);
    return;
  }
}

StormExprValue::operator float()
{
  return GetFloatVal();
}

StormExprValue::operator const char *()
{
  return GetStringVal();
}

StormExprValue::operator std::string()
{
  return GetStringVal();
}
