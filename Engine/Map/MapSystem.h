#pragma once

#include "Engine/EngineCommon.h"
#include "Engine/Map/MapInstance.h"

#include "Runtime/Map/MapDef.refl.h"

class EngineState;

class MapSystem
{
public:
  MapSystem(NotNullPtr<EngineState> engine_state);

  std::size_t InstantiateMap(MapDef & map_def);
  void UnloadMap(std::size_t map_id);

  void DrawAllMaps(DrawList & draw_list);
private:

  NotNullPtr<EngineState> m_EngineState;

  std::size_t m_NextMapId;
  std::unordered_map<std::size_t, std::unique_ptr<MapInstance>> m_Maps;
};
