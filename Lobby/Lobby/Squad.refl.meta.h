#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "Squad.refl.h"
#include "HurricaneDDS/DDSThrottle.refl.meta.h"
#include "LobbyShared/SharedTypes.refl.meta.h"


namespace StormReflFileInfo
{
  struct Squad
  {
    static const int types_n = 0;
    template <int i> struct type_info { using type = void; };
  };

}

