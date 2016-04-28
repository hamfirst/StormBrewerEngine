#pragma once

#include "Foundation\Common.h"

template <typename T>
class HasInit
{
  typedef char one;
  typedef long two;

  template <typename C> static one test(decltype(&C::Init));
  template <typename C> static two test(...);

public:
  enum { value = sizeof(test<T>(0)) == sizeof(char) };
};
