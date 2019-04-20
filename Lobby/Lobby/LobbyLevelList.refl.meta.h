#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "LobbyLevelList.refl.h"
#include "Game/GameNetworkData.refl.meta.h"
#include "Runtime/Map/MapDef.refl.meta.h"


namespace StormReflFileInfo
{
  struct LobbyLevelList
  {
    static const int types_n = 0;
    template <int i> struct type_info { using type = void; };
  };

}

