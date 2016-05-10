#pragma once

#include "Foundation\Common.h"

template <typename T>
class HasInit
{
  typedef char true_type;
  typedef long false_type;

  template <typename C> static true_type test(decltype(&C::Init));
  template <typename C> static false_type test(...);

public:
  enum { value = sizeof(test<T>(0)) == sizeof(true_type) };
};
