#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "BuiltInChannel.refl.h"
#include "LobbyShared/SharedTypes.refl.meta.h"


namespace StormReflFileInfo
{
  struct BuiltInChannel
  {
    static const int types_n = 0;
    template <int i> struct type_info { using type = void; };
  };

}

