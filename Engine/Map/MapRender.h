#pragma once

#include "Foundation/Any/Any.h"

#include "Runtime/Map/MapDef.refl.h"

#include "Engine/EngineState.h"
#include "Engine/DrawList/DrawList.h"

class MapRenderer
{
public:
  static void DrawAllMaps(NotNullPtr<EngineState> engine_state, DrawList & draw_list);
};

Any CreateMapEngineData(MapDef & map_def);