
#include "Engine/EngineCommon.h"
#include "Engine/Map/MapEngineInstance.h"


MapEngineInstance::MapEngineInstance(MapDef & map)
{
  for (auto elem : map.m_ManualTileLayers)
  {
    m_ManualTileLayers.emplace_back(map, elem.first);
  }
}

void MapEngineInstance::Draw(DrawList & draw_list)
{
  for (auto & layer : m_ManualTileLayers)
  {
    draw_list.PushDraw(layer.GetLayerOrder(), [&](const Box & viewport_bounds, const RenderVec2 & screen_center)
    {
      layer.Draw(viewport_bounds, screen_center);
    });
  }
}
