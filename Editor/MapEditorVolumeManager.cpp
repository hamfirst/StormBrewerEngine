
#include "MapEditorVolumeManager.h"
#include "MapEditor.h"

MapEditorVolumeManager::MapEditorVolumeManager(NotNullPtr<MapEditor> editor, MapDef & map) :
  m_Editor(editor),
  m_Map(map),
  m_Watcher(m_Editor)
{
  m_Watcher.SetPath(".m_Volumes", false, false, [] { return true; });
  m_Watcher.SetChangeCallback([=](const ReflectionChangeNotification & change) { HandleListChange(change); });

  Resync();
}

MapEditorVolumeManager::~MapEditorVolumeManager()
{

}

NullOptPtr<MapEditorVolume> MapEditorVolumeManager::GetLayerManager(int layer_index)
{
  if (m_VolumeManagers.HasAt((std::size_t)layer_index) == false)
  {
    return nullptr;
  }

  return m_VolumeManagers[layer_index].get();
}

void MapEditorVolumeManager::Resync()
{
  SparseList<std::unique_ptr<MapEditorVolume>> old_layers = std::move(m_VolumeManagers);

  for (auto elem : m_Map.m_ParalaxLayers)
  {
    m_VolumeManagers.EmplaceAt(elem.first, std::make_unique<MapEditorVolume>(m_Editor, m_Map, (int)elem.first));
  }
}

void MapEditorVolumeManager::HandleListChange(const ReflectionChangeNotification & change)
{
  if (change.m_Type == ReflectionNotifyChangeType::kInsert)
  {
    if (m_Map.m_Volumes.HasAt(change.m_SubIndex))
    {
      m_VolumeManagers.EmplaceAt(change.m_SubIndex, std::make_unique<MapEditorVolume>(m_Editor, m_Map, (int)change.m_SubIndex));
    }
  }
  else if (change.m_Type == ReflectionNotifyChangeType::kRemove)
  {
    m_VolumeManagers.RemoveAt(change.m_SubIndex);
  }
  else
  {
    Resync();
  }
}
