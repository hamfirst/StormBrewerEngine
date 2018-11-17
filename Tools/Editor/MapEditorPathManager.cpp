
#include "MapEditorPathManager.h"
#include "MapEditor.h"

MapEditorPathManager::MapEditorPathManager(NotNullPtr<MapEditor> editor, MapDef & map) :
  m_Editor(editor),
  m_Map(map),
  m_Watcher(m_Editor)
{
  m_Watcher.SetPath(".m_Paths", false, false, [] { return true; });
  m_Watcher.SetChangeCallback([=](const ReflectionChangeNotification & change) { HandleListChange(change); });

  Resync();
}

MapEditorPathManager::~MapEditorPathManager()
{

}

NullOptPtr<MapEditorPath> MapEditorPathManager::GetLayerManager(int layer_index)
{
  if (m_PathManagers.HasAt((std::size_t)layer_index) == false)
  {
    return nullptr;
  }

  return m_PathManagers[layer_index].get();
}

void MapEditorPathManager::Resync()
{
  SparseList<std::unique_ptr<MapEditorPath>> old_layers = std::move(m_PathManagers);

  for (auto elem : m_Map.m_ParalaxLayers)
  {
    m_PathManagers.EmplaceAt(elem.first, std::make_unique<MapEditorPath>(m_Editor, m_Map, (int)elem.first));
  }
}

void MapEditorPathManager::HandleListChange(const ReflectionChangeNotification & change)
{
  if (change.m_Type == ReflectionNotifyChangeType::kInsert)
  {
    if (m_Map.m_Paths.HasAt(change.m_SubIndex))
    {
      m_PathManagers.EmplaceAt(change.m_SubIndex, std::make_unique<MapEditorPath>(m_Editor, m_Map, (int)change.m_SubIndex));
    }
  }
  else if (change.m_Type == ReflectionNotifyChangeType::kRemove)
  {
    m_PathManagers.RemoveAt(change.m_SubIndex);
  }
  else
  {
    Resync();
  }
}
