#pragma once

#include <functional>

#include "Foundation/Common.h"

#include "Foundation/BasicTypes/BasicTypes.refl.h"
#include "Foundation/BasicTypes/BasicTypeHash.h"

namespace std
{
  template <>
  struct hash<Vector2>
  {
    std::size_t operator() (Vector2 const & v) const
    {
      return std::hash<int>{}(v.x) ^ (std::hash<int>{}(v.y) << 1);
    }
  };
}
