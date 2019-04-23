#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "Bot.refl.h"
#include "HurricaneDDS/DDSThrottle.refl.meta.h"
#include "LobbyShared/SharedTypes.refl.meta.h"
#include "GameData.refl.meta.h"
#include "GameServerMessages.refl.meta.h"


namespace StormReflFileInfo
{
  struct Bot
  {
    static const int types_n = 0;
    template <int i> struct type_info { using type = void; };
  };

}

