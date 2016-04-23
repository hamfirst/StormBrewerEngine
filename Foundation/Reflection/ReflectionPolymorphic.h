#pragma once
#pragma once

#include "Foundation\Common.h"

template <class T>
class RPolymorphic
{
public:


  uint32_t GetTypeNameHash()
  {
    return m_TypeNameHash;
  }

private:

  std::unique_ptr<T> m_T;
  uint32_t m_TypeNameHash;
};

