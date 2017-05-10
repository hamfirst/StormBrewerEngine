#pragma once

#include "Foundation/Any/Any.h"

#include "Runtime/RuntimeState.h"
#include "Runtime/Map/MapDef.refl.h"

#include "Engine/DrawList/DrawList.h"

class MapRenderer
{
public:
  static void DrawAllMaps(NotNullPtr<RuntimeState> runtime_state, DrawList & draw_list);
};

Any CreateMapEngineData(MapDef & map_def);