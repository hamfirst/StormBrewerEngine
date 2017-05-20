#pragma once

#include <memory>

#include <QTabWidget>
#include <QGridLayout>

#include "Runtime/Map/MapDef.refl.h"

#include "DocumentEditorWidgetBase.h"
#include "GenericFrame.h"
#include "PropertyEditor.h"
#include "MapEditorLayer.h"
#include "MapEditorLayerList.h"
#include "MapEditorViewer.h"
#include "MapEditorSelector.h"
#include "MapEditorTileLayerManager.h"
#include "MapEditorEntityLayerManager.h"
#include "MapEditorParalaxLayerManager.h"
#include "MapEditorVolumeManager.h"
#include "MapEditorPathManager.h"


static const uint64_t kInvalidFrameId = ~0;

class MapEditor : public DocumentEditorWidgetBase
{
  Q_OBJECT;
public:
  MapEditor(PropertyFieldDatabase & property_db, const std::string & root_path, MapDef & map, DocumentChangeLinkDelegate && change_link_callback,
    DocumentBeginTransactionDelegate && begin_transaction_callback, DocumentCommitChangesDelegate && commit_change_callback, QWidget *parent = nullptr);

  void ChangeLayerSelection(const MapEditorLayerSelection & layer, bool change_viewer_position = true);
  void ClearLayerSelection();

  MapEditorTileLayerManager & GetManualTileManager();
  MapEditorEntityLayerManager & GetEntityManager();
  MapEditorParalaxLayerManager & GetParalaxManager();
  MapEditorVolumeManager & GetVolumeManager();
  MapEditorPathManager & GetPathManager();

  MapEditorSelector & GetSelector();
  MapEditorLayerList & GetLayerList();
  MapEditorViewer & GetViewer();

  void SelectManualTile(int layer_index, uint64_t frame_id);
  void SetSelectedEntity(int layer_index, czstr entity_file);
  void ClearPropertyPanel();

  const RPolymorphic<VolumeDataBase, VolumeTypeDatabase, VolumeDataTypeInfo> & GetVolumeInitData() const;
  void CreateNewVolume(const Box & box);

  const RPolymorphic<PathDataBase, PathTypeDatabase, PathDataTypeInfo> & GetPathInitData() const;
  void CreateNewPath(const Line & line);

public:

  void AboutToClose() override;

private:

  MapDef & m_Map;
  MapEditorTileLayerManager m_ManualTileLayers;
  MapEditorEntityLayerManager m_EntityLayers;
  MapEditorParalaxLayerManager m_ParalaxLayers;
  MapEditorVolumeManager m_Volumes;
  MapEditorPathManager m_Paths;

  std::unique_ptr<QGridLayout> m_Layout;
  std::unique_ptr<GenericFrame> m_Properties;

  std::unique_ptr<MapEditorSelector> m_Selector;
  std::unique_ptr<MapEditorLayerList> m_LayerList;
  std::unique_ptr<MapEditorViewer> m_Viewer;

  RPolymorphic<VolumeDataBase, VolumeTypeDatabase, VolumeDataTypeInfo> m_VolumeInitData;
  RPolymorphic<PathDataBase, PathTypeDatabase, PathDataTypeInfo> m_PathInitData;

  PropertyEditor * m_PropertyEditor;
  bool m_IgnoreSelectionChanges;
};
