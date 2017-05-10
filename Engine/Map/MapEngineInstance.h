#pragma once

#include "Runtime/Map/MapDef.refl.h"

#include "Engine/Map/MapManualTileLayerInstance.h"
#include "Engine/DrawList/DrawList.h"


class MapEngineInstance
{
public:
  MapEngineInstance(MapDef & map);

  void Draw(DrawList & draw_list);

private:

  std::vector<MapManualTileLayerInstance> m_ManualTileLayers;
};

