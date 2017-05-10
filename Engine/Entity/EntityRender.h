#pragma once

#include "Runtime/RuntimeState.h"

#include "Engine/DrawList/DrawList.h"

class EntityRenderer
{
public:
  static void DrawAllEntities(const Box & viewport_bounds, NotNullPtr<RuntimeState> runtime_state, DrawList & draw_list);
};
