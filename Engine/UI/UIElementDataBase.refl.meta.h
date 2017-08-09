#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "UIElementDataBase.refl.h"


namespace StormReflFileInfo
{
  struct UIElementDataBase
  {
    static const int types_n = 0;
    template <int i> struct type_info { using type = void; };
  };

}

