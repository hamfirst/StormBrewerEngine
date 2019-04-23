#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "BotMessages.refl.h"
#include "Lobby/GameData.refl.meta.h"
#include "Lobby/GameServerMessages.refl.meta.h"
#include "Game/GameNetworkData.refl.meta.h"


namespace StormReflFileInfo
{
  struct BotMessages
  {
    static const int types_n = 0;
    template <int i> struct type_info { using type = void; };
  };

}

