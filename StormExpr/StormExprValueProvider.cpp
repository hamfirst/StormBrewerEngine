
#include "StormExprValueProvider.h"

StormExprValueProvider::StormExprValueProvider() :
  m_Type(ProviderType::kNone)
{

}

StormExprValueProvider::StormExprValueProvider(float * float_ptr) :
  m_Type(ProviderType::kFloat),
  m_Float(float_ptr)
{

}

StormExprValueProvider::StormExprValueProvider(std::string * str) :
  m_Type(ProviderType::kStdString),
  m_String(str)
{

}

StormExprValueProvider::StormExprValueProvider(const char * const * czstr) :
  m_Type(ProviderType::kCzstr),
  m_Czstr(czstr)
{

}

StormExprValue StormExprValueProvider::GetValue()
{
  switch (m_Type)
  {
  default:
  case ProviderType::kNone:
    return StormExprValue();
  case ProviderType::kFloat:
    return StormExprValue(*m_Float);
  case ProviderType::kStdString:
    return StormExprValue(m_String->data());
  case ProviderType::kCzstr:
    return StormExprValue(*m_Czstr);
  }

}

StormExprValueType StormExprValueProvider::GetValueType()
{
  switch (m_Type)
  {
  default:
  case ProviderType::kNone:
    return StormExprValueType::kNothing;
  case ProviderType::kFloat:
    return StormExprValueType::kFloat;
  case ProviderType::kStdString:
    return StormExprValueType::kString;
  case ProviderType::kCzstr:
    return StormExprValueType::kString;
  }
}

float StormExprValueProvider::GetFloatValue()
{
  return *m_Float;
}

const char * StormExprValueProvider::GetStringValue()
{
  switch (m_Type)
  {
  case ProviderType::kStdString:
    return m_String->data();
  case ProviderType::kCzstr:
    return *m_Czstr;
  }

  return nullptr;
}

void StormExprValueProvider::SetValue(StormExprValue val)
{
  switch (val.GetType())
  {
  case StormExprValueType::kFloat:
    if (m_Type == ProviderType::kFloat)
    {
      *m_Float = val.GetFloatVal();
    }
    break;
  case StormExprValueType::kString:
    if (m_Type == ProviderType::kStdString)
    {
      *m_String = val.GetStringVal();
    }
    break;
  }
}
