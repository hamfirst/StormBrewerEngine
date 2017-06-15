
#include "Engine/EngineCommon.h"
#include "Engine/Map/MapRender.h"
#include "Engine/Map/MapInstance.h"
#include "Engine/Map/MapSystem.h"

void MapRenderer::DrawAllMaps(NotNullPtr<EngineState> engine_state, DrawList & draw_list)
{
  auto map_system = engine_state->m_MapSystem.get();
  for (auto & map : map_system->m_Maps)
  {
    MapInstance * inst = map.second.get();
    inst->Draw(draw_list);
  }
}
