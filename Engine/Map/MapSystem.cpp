
#include "Engine/EngineCommon.h"
#include "Engine/Map/MapSystem.h"
#include "Engine/Map/MapInstance.h"

MapSystem::MapSystem(NotNullPtr<EngineState> engine_state) :
  m_EngineState(engine_state),
  m_NextMapId(1)
{

}

std::size_t MapSystem::InstantiateMap(MapDef & map_def)
{
  auto map_id = m_NextMapId;
  m_NextMapId++;

  m_Maps.emplace(map_id, std::make_unique<MapInstance>(m_EngineState, map_def, map_id));
  return map_id;
}

void MapSystem::UnloadMap(std::size_t map_id)
{
  auto itr = m_Maps.find(map_id);
  if (itr == m_Maps.end())
  {
    return;
  }

  itr->second->RemoveCollision(m_EngineState);
  m_Maps.erase(itr);
}

NullOptPtr<MapInstance> MapSystem::GetMapInstance(std::size_t map_id)
{
  auto itr = m_Maps.find(map_id);
  return (itr == m_Maps.end()) ? nullptr : itr->second.get();
}

void MapSystem::DrawAllMaps(const Box & viewport_bounds, DrawList & draw_list)
{
  for (auto & map : m_Maps)
  {
    MapInstance * inst = map.second.get();
    inst->Draw(viewport_bounds, draw_list);
  }
}
