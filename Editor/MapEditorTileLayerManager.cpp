
#include "MapEditorTileLayerManager.h"
#include "MapEditor.h"

MapEditorTileLayerManager::MapEditorTileLayerManager(NotNullPtr<MapEditor> editor, MapDef & map) :
  m_Editor(editor),
  m_Map(map),
  m_Watcher(m_Editor)
{
  m_Watcher.SetPath(".m_ManualTileLayers", false, false, [] {return true; });
  m_Watcher.SetChangeCallback([=](const ReflectionChangeNotification & change) {HandleListChange(change); });

  Resync();
}

MapEditorTileLayerManager::~MapEditorTileLayerManager()
{

}

NullOptPtr<MapEditorTileManager> MapEditorTileLayerManager::GetLayerManager(int layer_index)
{
  if (m_TileManagers.HasAt((std::size_t)layer_index) == false)
  {
    return nullptr;
  }

  return m_TileManagers[layer_index].get();
}

void MapEditorTileLayerManager::Resync()
{
  SparseList<std::unique_ptr<MapEditorTileManager>> old_layers = std::move(m_TileManagers);

  for (auto elem : m_Map.m_ManualTileLayers)
  {
    m_TileManagers.EmplaceAt(elem.first, std::make_unique<MapEditorTileManager>(m_Editor, m_Map, (int)elem.first));
  }
}

void MapEditorTileLayerManager::HandleListChange(const ReflectionChangeNotification & change)
{
  if (change.m_Type == ReflectionNotifyChangeType::kInsert)
  {
    if (m_Map.m_ManualTileLayers.HasAt(change.m_SubIndex))
    {
      m_TileManagers.EmplaceAt(change.m_SubIndex, std::make_unique<MapEditorTileManager>(m_Editor, m_Map, (int)change.m_SubIndex));
    }
  }
  else if (change.m_Type == ReflectionNotifyChangeType::kRemove)
  {
    m_TileManagers.RemoveAt(change.m_SubIndex);
  }
  else
  {
    Resync();
  }
}
