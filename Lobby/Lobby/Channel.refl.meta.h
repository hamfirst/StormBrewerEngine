#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "Channel.refl.h"
#include "LobbyShared/SharedTypes.refl.meta.h"
#include "Squad.refl.meta.h"
#include "BuiltInChannel.refl.meta.h"


namespace StormReflFileInfo
{
  struct Channel
  {
    static const int types_n = 0;
    template <int i> struct type_info { using type = void; };
  };

}

