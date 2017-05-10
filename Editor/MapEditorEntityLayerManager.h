#pragma once

#include "MapEditorEntityManager.h"
#include "DocumentListValueWatcher.h"

class MapEditorEntityLayerManager
{
public:
  MapEditorEntityLayerManager(NotNullPtr<MapEditor> editor, MapDef & map);
  ~MapEditorEntityLayerManager();

  NullOptPtr<MapEditorEntityManager> GetLayerManager(int layer_index);

protected:
  void Resync();
  void HandleListChange(const ReflectionChangeNotification & change);

private:
  NotNullPtr<MapEditor> m_Editor;

  MapDef & m_Map;

  SparseList<std::unique_ptr<MapEditorEntityManager>> m_EntityManagers;
  DocumentListValueWatcher m_Watcher;
};

