#pragma once

#include <string>

#include "StormExprValue.h"

class StormExprValueProvider
{
public:

  StormExprValueProvider();
  StormExprValueProvider(float * float_ptr);
  StormExprValueProvider(std::string * str);
  StormExprValueProvider(const char * const * czstr);

  StormExprValueProvider(const StormExprValueProvider & rhs) = default;
  StormExprValueProvider(StormExprValueProvider && rhs) = default;

  StormExprValueProvider & operator = (const StormExprValueProvider & rhs) = default;
  StormExprValueProvider & operator = (StormExprValueProvider && rhs) = default;

  StormExprValue GetValue();

  StormExprValueType GetValueType();

  float GetFloatValue();
  const char * GetStringValue();

  void SetValue(StormExprValue val);

private:

  enum ProviderType
  {
    kNone,
    kFloat,
    kStdString,
    kCzstr
  };

private:

  ProviderType m_Type;

  union
  {
    float * m_Float;
    std::string * m_String;
    const char * const * m_Czstr;
  };
};
