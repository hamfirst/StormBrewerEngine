#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "Rewards.refl.h"
#include "GameData.refl.meta.h"


namespace StormReflFileInfo
{
  struct Rewards
  {
    static const int types_n = 0;
    template <int i> struct type_info { using type = void; };
  };

}

