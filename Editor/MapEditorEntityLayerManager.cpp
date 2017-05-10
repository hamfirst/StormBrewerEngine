
#include "MapEditorEntityLayerManager.h"
#include "MapEditor.h"

MapEditorEntityLayerManager::MapEditorEntityLayerManager(NotNullPtr<MapEditor> editor, MapDef & map) :
  m_Editor(editor),
  m_Map(map),
  m_Watcher(m_Editor)
{
  m_Watcher.SetPath(".m_EntityLayers", false, false, [] {return true; });
  m_Watcher.SetChangeCallback([=](const ReflectionChangeNotification & change) { HandleListChange(change); });

  Resync();
}

MapEditorEntityLayerManager::~MapEditorEntityLayerManager()
{

}

NullOptPtr<MapEditorEntityManager> MapEditorEntityLayerManager::GetLayerManager(int layer_index)
{
  if (m_EntityManagers.HasAt((std::size_t)layer_index) == false)
  {
    return nullptr;
  }

  return m_EntityManagers[layer_index].get();
}

void MapEditorEntityLayerManager::Resync()
{
  SparseList<std::unique_ptr<MapEditorEntityManager>> old_layers = std::move(m_EntityManagers);

  for (auto elem : m_Map.m_EntityLayers)
  {
    m_EntityManagers.EmplaceAt(elem.first, std::make_unique<MapEditorEntityManager>(m_Editor, m_Map, (int)elem.first));
  }
}

void MapEditorEntityLayerManager::HandleListChange(const ReflectionChangeNotification & change)
{
  if (change.m_Type == ReflectionNotifyChangeType::kInsert)
  {
    if (m_Map.m_EntityLayers.HasAt(change.m_SubIndex))
    {
      m_EntityManagers.EmplaceAt(change.m_SubIndex, std::make_unique<MapEditorEntityManager>(m_Editor, m_Map, (int)change.m_SubIndex));
    }
  }
  else if (change.m_Type == ReflectionNotifyChangeType::kRemove)
  {
    m_EntityManagers.RemoveAt(change.m_SubIndex);
  }
  else
  {
    Resync();
  }
}
