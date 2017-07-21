#pragma once

#include "Foundation/Any/Any.h"

#include "Runtime/RuntimeCommon.h"
#include "Runtime/Map/MapDef.refl.h"

#include "Engine/Map/MapManualTileLayerInstance.h"
#include "Engine/Map/MapEffectLayerInstance.h"
#include "Engine/Map/MapParalaxLayerInstance.h"
#include "Engine/DrawList/DrawList.h"

class GameContainer;

class EngineState;

class MapInstance
{
public:
  MapInstance(NotNullPtr<EngineState> engine_state, MapDef & map_def, std::size_t map_id);
  void RemoveCollision(NotNullPtr<EngineState> engine_state);

  void Update(GameContainer & game_container);
  void Draw(DrawList & draw_list);

private:
  friend class MapRenderer;

  std::vector<MapManualTileLayerInstance> m_ManualTileLayers;
  std::vector<MapParalaxLayerInstance> m_ParalaxLayers;
  std::vector<MapEffectLayerInstance> m_EffectLayers;
  std::size_t m_MapId;
};
