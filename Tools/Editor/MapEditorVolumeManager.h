#pragma once

#include "Foundation/SparseList/SparseList.h"

#include "MapEditorVolume.h"
#include "DocumentListValueWatcher.h"

class MapEditorVolumeManager
{
public:
  MapEditorVolumeManager(NotNullPtr<MapEditor> editor, MapDef & map);
  ~MapEditorVolumeManager();

  NullOptPtr<MapEditorVolume> GetLayerManager(int layer_index);

protected:
  void Resync();
  void HandleListChange(const ReflectionChangeNotification & change);

private:
  NotNullPtr<MapEditor> m_Editor;

  MapDef & m_Map;

  SparseList<std::unique_ptr<MapEditorVolume>> m_VolumeManagers;
  DocumentListValueWatcher m_Watcher;
};

