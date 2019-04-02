#pragma once

#include "Foundation/Any/Any.h"

#include "Runtime/RuntimeCommon.h"
#include "Runtime/Map/MapDef.refl.h"

#include "Engine/Map/MapManualTileLayerInstance.h"
#include "Engine/Map/MapEffectLayerInstance.h"
#include "Engine/Map/MapParallaxLayerInstance.h"
#include "Engine/DrawList/DrawList.h"
#include "Engine/Entity/EntityHandle.h"
#include "Engine/Rendering/RenderSettings.h"

class GameContainer;

class EngineState;

class MapInstance
{
public:
  MapInstance(NotNullPtr<EngineState> engine_state, MapDef & map_def, std::size_t map_id, const Vector2 & offset);

  void Init(GameContainer & game_container);
  void Update(GameContainer & game_container);
  void Draw(const Box & viewport_bounds, DrawList & draw_list);

private:
  friend class MapRenderer;

  std::vector<MapManualTileLayerInstance> m_ManualTileLayers;
  std::vector<MapParallaxLayerInstance> m_ParallaxLayers;
  std::vector<MapEffectLayerInstance> m_EffectLayers;
  std::vector<EntityHandle> m_MapEntities;

  std::size_t m_MapId;
  Vector2 m_Offset;
};
