#pragma once

#include <string>
#include <cstddef>

#include "StormExprValue.h"

class StormExprValueProvider
{
public:

  StormExprValueProvider();
  StormExprValueProvider(const void * base_ptr, const float * float_ptr);
  StormExprValueProvider(const void * base_ptr, const std::string * str);
  StormExprValueProvider(const void * base_ptr, const char * const * czstr);
  StormExprValueProvider(const void * base_ptr, const StormExprValue * val_ptr);

  StormExprValueProvider(const StormExprValueProvider & rhs) = default;
  StormExprValueProvider(StormExprValueProvider && rhs) = default;

  StormExprValueProvider & operator = (const StormExprValueProvider & rhs) = default;
  StormExprValueProvider & operator = (StormExprValueProvider && rhs) = default;

  StormExprValue GetValue(const void * base_ptr) const;
  StormExprValueType GetValueType(const void * base_ptr) const;

private:

  enum ProviderType
  {
    kNone,
    kFloat,
    kStdString,
    kValue,
    kCzstr
  };

private:

  ProviderType m_Type;
  ptrdiff_t m_BaseOffset;
};
