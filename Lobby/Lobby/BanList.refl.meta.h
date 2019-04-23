#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "BanList.refl.h"


namespace StormReflFileInfo
{
  struct BanList
  {
    static const int types_n = 0;
    template <int i> struct type_info { using type = void; };
  };

}

