
#include "Engine/EngineCommon.h"
#include "Engine/Map/MapRender.h"
#include "Engine/Map/MapEngineInstance.h"
#include "Runtime/Map/MapSystem.h"
#include "Runtime/Map/MapInstance.h"

void MapRenderer::DrawAllMaps(NotNullPtr<RuntimeState> runtime_state, DrawList & draw_list)
{
  auto map_system = runtime_state->m_MapSystem.get();
  for (auto & map : map_system->m_Maps)
  {
    MapEngineInstance * inst = map.second->m_EngineData.Get<MapEngineInstance>();
    if (inst == nullptr)
    {
      continue;
    }

    inst->Draw(draw_list);
  }
}

Any CreateMapEngineData(MapDef & map_def)
{
  return Any(MapEngineInstance(map_def));
}
