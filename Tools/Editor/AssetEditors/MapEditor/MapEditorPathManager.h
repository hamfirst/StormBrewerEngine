#pragma once

#include "Foundation/SparseList/SparseList.h"

#include "MapEditorPath.h"
#include "Tools/Editor/Utility/DocumentListValueWatcher.h"

class MapEditorPathManager
{
public:
  MapEditorPathManager(NotNullPtr<MapEditor> editor, MapDef & map);
  ~MapEditorPathManager();

  NullOptPtr<MapEditorPath> GetLayerManager(int layer_index);

protected:
  void Resync();
  void HandleListChange(const ReflectionChangeNotification & change);

private:
  NotNullPtr<MapEditor> m_Editor;

  MapDef & m_Map;

  SparseList<std::unique_ptr<MapEditorPath>> m_PathManagers;
  DocumentListValueWatcher m_Watcher;
};

