#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "WelcomeInfo.refl.h"
#include "LobbyShared/SharedTypes.refl.meta.h"


namespace StormReflFileInfo
{
  struct WelcomeInfo
  {
    static const int types_n = 0;
    template <int i> struct type_info { using type = void; };
  };

}

