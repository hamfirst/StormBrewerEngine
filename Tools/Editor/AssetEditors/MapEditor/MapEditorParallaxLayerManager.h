#pragma once

#include "Foundation/SparseList/SparseList.h"

#include "MapEditorParallaxLayer.h"
#include "Tools/Editor/Utility/DocumentListValueWatcher.h"

class MapEditorParallaxLayerManager
{
public:
  MapEditorParallaxLayerManager(NotNullPtr<MapEditor> editor, MapDef & map);
  ~MapEditorParallaxLayerManager();

  NullOptPtr<MapEditorParallaxLayer> GetLayerManager(int layer_index);

protected:
  void Resync();
  void HandleListChange(const ReflectionChangeNotification & change);

private:
  NotNullPtr<MapEditor> m_Editor;

  MapDef & m_Map;

  SparseList<std::unique_ptr<MapEditorParallaxLayer>> m_ParallaxManagers;
  DocumentListValueWatcher m_Watcher;
};

