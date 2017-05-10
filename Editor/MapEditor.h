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

  MapEditorSelector & GetSelector();
  MapEditorLayerList & GetLayerList();
  MapEditorViewer & GetViewer();

  void SelectManualTile(int layer_index, uint64_t frame_id);
  void SetSelectedEntity(int layer_index, czstr entity_file);
  void ClearPropertyPanel();

public:

  void AboutToClose() override;

private:

  MapDef & m_Map;
  MapEditorTileLayerManager m_ManualTileLayers;
  MapEditorEntityLayerManager m_EntityLayers;
  MapEditorParalaxLayerManager m_ParalaxLayers;

  std::unique_ptr<QGridLayout> m_Layout;
  std::unique_ptr<GenericFrame> m_Properties;

  std::unique_ptr<MapEditorSelector> m_Selector;
  std::unique_ptr<MapEditorLayerList> m_LayerList;
  std::unique_ptr<MapEditorViewer> m_Viewer;

  PropertyEditor * m_PropertyEditor;
  bool m_IgnoreSelectionChanges;
};
