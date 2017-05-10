#pragma once

#include "Runtime/RuntimeCommon.h"
#include "Runtime/Map/MapDef.refl.h"
#include "Runtime/Map/MapInstance.h"

class RuntimeState;

class MapSystem
{
public:
  MapSystem(NotNullPtr<RuntimeState> runtime_state);

  std::size_t InstantiateMap(MapDef & map_def);
  void UnloadMap(std::size_t map_id);

private:
  friend class MapRenderer;

  NotNullPtr<RuntimeState> m_RuntimeState;

  std::size_t m_NextMapId;
  std::unordered_map<std::size_t, std::unique_ptr<MapInstance>> m_Maps;
};
