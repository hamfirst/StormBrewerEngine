#pragma once

#include "Foundation/SparseList/SparseList.h"

#include "MapEditorParalaxLayer.h"
#include "DocumentListValueWatcher.h"

class MapEditorParalaxLayerManager
{
public:
  MapEditorParalaxLayerManager(NotNullPtr<MapEditor> editor, MapDef & map);
  ~MapEditorParalaxLayerManager();

  NullOptPtr<MapEditorParalaxLayer> GetLayerManager(int layer_index);

protected:
  void Resync();
  void HandleListChange(const ReflectionChangeNotification & change);

private:
  NotNullPtr<MapEditor> m_Editor;

  MapDef & m_Map;

  SparseList<std::unique_ptr<MapEditorParalaxLayer>> m_ParalaxManagers;
  DocumentListValueWatcher m_Watcher;
};

