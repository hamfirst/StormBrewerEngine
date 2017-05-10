
#include "Runtime/RuntimeCommon.h"
#include "Runtime/Map/MapSystem.h"
#include "Runtime/Map/MapInstance.h"

MapSystem::MapSystem(NotNullPtr<RuntimeState> runtime_state) :
  m_RuntimeState(runtime_state),
  m_NextMapId(1)
{

}

std::size_t MapSystem::InstantiateMap(MapDef & map_def)
{
  auto map_id = m_NextMapId;
  m_NextMapId++;

  m_Maps.emplace(map_id, std::make_unique<MapInstance>(m_RuntimeState, map_def, map_id));
  return map_id;
}

void MapSystem::UnloadMap(std::size_t map_id)
{
  auto itr = m_Maps.find(map_id);
  if (itr == m_Maps.end())
  {
    return;
  }

  itr->second->RemoveCollision(m_RuntimeState);
  m_Maps.erase(itr);
}

