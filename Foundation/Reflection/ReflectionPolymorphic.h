#pragma once
#pragma once

#include "Foundation\Common.h"
#include "Foundation\Reflection\Reflection.h"

template <class T>
class RPolymorphic
{
  REFLECTION_PARENT_INFO;
public:

  uint32_t GetTypeNameHash()
  {
    return m_TypeNameHash;
  }

private:

  std::unique_ptr<T> m_T;
  uint32_t m_TypeNameHash;
};

