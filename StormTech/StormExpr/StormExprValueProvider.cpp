
#include "StormExprValueProvider.h"

StormExprValueProvider::StormExprValueProvider() :
  m_Type(ProviderType::kNone)
{

}

StormExprValueProvider::StormExprValueProvider(const void * base_ptr, const float * float_ptr) :
  m_Type(ProviderType::kFloat)
{
  m_BaseOffset = (const char *)float_ptr - (const char *)base_ptr;
}

StormExprValueProvider::StormExprValueProvider(const void * base_ptr, const std::string * str) :
  m_Type(ProviderType::kStdString)
{
  m_BaseOffset = (const char *)str - (const char *)base_ptr;
}

StormExprValueProvider::StormExprValueProvider(const void * base_ptr, const char * const * czstr) :
  m_Type(ProviderType::kCzstr)
{
  m_BaseOffset = (const char *)czstr - (const char *)base_ptr;
}

StormExprValueProvider::StormExprValueProvider(const void * base_ptr, const StormExprValue * val_ptr) :
  m_Type(ProviderType::kValue)
{
  m_BaseOffset = (const char *)val_ptr - (const char *)base_ptr;
}

StormExprValue StormExprValueProvider::GetValue(const void * base_ptr) const
{
  const char * ptr = (const char *)base_ptr + m_BaseOffset;

  switch (m_Type)
  {
  default:
  case ProviderType::kNone:
    return StormExprValue();
  case ProviderType::kFloat:
    return StormExprValue(*(const float *)ptr);
  case ProviderType::kStdString:
    return StormExprValue(((const std::string *)ptr)->data());
  case ProviderType::kCzstr:
    return StormExprValue(*(const char * const *)ptr);
  case ProviderType::kValue:
    return StormExprValue(*(const StormExprValue *)ptr);
  }
}

StormExprValueType StormExprValueProvider::GetValueType(const void * base_ptr) const
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
  case ProviderType::kValue:
    {
      const char * ptr = (const char *)base_ptr + m_BaseOffset;
      return ((const StormExprValue *)ptr)->GetType();
    }
  }
}
