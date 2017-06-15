#pragma once

#include "Engine/EngineState.h"
#include "Engine/DrawList/DrawList.h"

class EntityRenderer
{
public:
  static void DrawAllEntities(const Box & viewport_bounds, NotNullPtr<EngineState> engine_state, DrawList & draw_list);
};
