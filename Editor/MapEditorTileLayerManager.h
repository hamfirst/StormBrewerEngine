#pragma once

#include "MapEditorTileManager.h"

class MapEditorTileLayerManager
{
public:
  MapEditorTileLayerManager(NotNullPtr<MapEditor> editor, MapDef & map);
  ~MapEditorTileLayerManager();

  NullOptPtr<MapEditorTileManager> GetLayerManager(int layer_index);

protected:
  void Resync();
  void HandleListChange(const ReflectionChangeNotification & change);

private:
  NotNullPtr<MapEditor> m_Editor;

  MapDef & m_Map;

  SparseList<std::unique_ptr<MapEditorTileManager>> m_TileManagers;
  DocumentListValueWatcher m_Watcher;
};

