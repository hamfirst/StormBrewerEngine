
#include "MapEditorParallaxLayerManager.h"
#include "MapEditor.h"

MapEditorParallaxLayerManager::MapEditorParallaxLayerManager(NotNullPtr<MapEditor> editor, MapDef & map) :
  m_Editor(editor),
  m_Map(map),
  m_Watcher(m_Editor)
{
  m_Watcher.SetPath(".m_ParallaxLayers", false, false, [] { return true; });
  m_Watcher.SetChangeCallback([=](const ReflectionChangeNotification & change) { HandleListChange(change); });

  Resync();
}

MapEditorParallaxLayerManager::~MapEditorParallaxLayerManager()
{

}

NullOptPtr<MapEditorParallaxLayer> MapEditorParallaxLayerManager::GetLayerManager(int layer_index)
{
  if (m_ParallaxManagers.HasAt((std::size_t)layer_index) == false)
  {
    return nullptr;
  }

  return m_ParallaxManagers[layer_index].get();
}

void MapEditorParallaxLayerManager::Resync()
{
  SparseList<std::unique_ptr<MapEditorParallaxLayer>> old_layers = std::move(m_ParallaxManagers);

  for (auto elem : m_Map.m_ParallaxLayers)
  {
    m_ParallaxManagers.EmplaceAt(elem.first, std::make_unique<MapEditorParallaxLayer>(m_Editor, m_Map, (int)elem.first));
  }
}

void MapEditorParallaxLayerManager::HandleListChange(const ReflectionChangeNotification & change)
{
  if (change.m_Type == ReflectionNotifyChangeType::kInsert)
  {
    if (m_Map.m_ParallaxLayers.HasAt(change.m_SubIndex))
    {
      m_ParallaxManagers.EmplaceAt(change.m_SubIndex, std::make_unique<MapEditorParallaxLayer>(m_Editor, m_Map, (int)change.m_SubIndex));
    }
  }
  else if (change.m_Type == ReflectionNotifyChangeType::kRemove)
  {
    m_ParallaxManagers.RemoveAt(change.m_SubIndex);
  }
  else
  {
    Resync();
  }
}
