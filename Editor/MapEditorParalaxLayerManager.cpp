
#include "MapEditorParalaxLayerManager.h"
#include "MapEditor.h"

MapEditorParalaxLayerManager::MapEditorParalaxLayerManager(NotNullPtr<MapEditor> editor, MapDef & map) :
  m_Editor(editor),
  m_Map(map),
  m_Watcher(m_Editor)
{
  m_Watcher.SetPath(".m_ParalaxLayers", false, false, [] { return true; });
  m_Watcher.SetChangeCallback([=](const ReflectionChangeNotification & change) { HandleListChange(change); });

  Resync();
}

MapEditorParalaxLayerManager::~MapEditorParalaxLayerManager()
{

}

NullOptPtr<MapEditorParalaxLayer> MapEditorParalaxLayerManager::GetLayerManager(int layer_index)
{
  if (m_ParalaxManagers.HasAt((std::size_t)layer_index) == false)
  {
    return nullptr;
  }

  return m_ParalaxManagers[layer_index].get();
}

void MapEditorParalaxLayerManager::Resync()
{
  SparseList<std::unique_ptr<MapEditorParalaxLayer>> old_layers = std::move(m_ParalaxManagers);

  for (auto elem : m_Map.m_ParalaxLayers)
  {
    m_ParalaxManagers.EmplaceAt(elem.first, std::make_unique<MapEditorParalaxLayer>(m_Editor, m_Map, (int)elem.first));
  }
}

void MapEditorParalaxLayerManager::HandleListChange(const ReflectionChangeNotification & change)
{
  if (change.m_Type == ReflectionNotifyChangeType::kInsert)
  {
    if (m_Map.m_ParalaxLayers.HasAt(change.m_SubIndex))
    {
      m_ParalaxManagers.EmplaceAt(change.m_SubIndex, std::make_unique<MapEditorParalaxLayer>(m_Editor, m_Map, (int)change.m_SubIndex));
    }
  }
  else if (change.m_Type == ReflectionNotifyChangeType::kRemove)
  {
    m_ParalaxManagers.RemoveAt(change.m_SubIndex);
  }
  else
  {
    Resync();
  }
}
