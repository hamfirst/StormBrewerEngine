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
#include "MapEditorLayerManager.h"
#include "MapEditorEntityManager.h"
#include "MapEditorServerObjectManager.h"
#include "MapEditorTileManager.h"
#include "MapEditorParalaxLayer.h"
#include "MapEditorEffectLayer.h"
#include "MapEditorVolume.h"
#include "MapEditorPath.h"
#include "MapEditorAnchor.h"
#include "MapEditorTypes.refl.h"


static const uint64_t kInvalidFrameId = ~0;

struct MapEditorTextures
{
  TextureAsset::AssetRef m_VfxTexture;
};

class MapEditor : public DocumentEditorWidgetBase
{
  Q_OBJECT;
public:
  MapEditor(EditorContainer & editor_container, PropertyFieldDatabase & property_db, const std::string & root_path, MapDef & map, DocumentChangeLinkDelegate && change_link_callback,
    DocumentBeginTransactionDelegate && begin_transaction_callback, DocumentCommitChangesDelegate && commit_change_callback, QWidget *parent = nullptr);

  void ChangeLayerSelection(const MapEditorLayerSelection & layer, bool change_viewer_position = true);
  void ClearLayerSelection();

  void CalculatePathfindingInfo();
  void ClearPathfindingInfo();

  MapEditorLayerManager<MapManualTileLayer, MapEditorTileManager> & GetManualTileManager();
  MapEditorLayerManager<MapEntityLayer, MapEditorEntityManager> & GetEntityManager();
  MapEditorLayerManager<MapServerObjectLayer, MapEditorServerObjectManager> & GetServerObjectManager();
  MapEditorLayerManager<MapParalaxLayer, MapEditorParalaxLayer> & GetParalaxManager();
  MapEditorLayerManager<MapEffectLayer, MapEditorEffectLayer> & GetEffectManager();
  MapEditorLayerManager<MapVolume, MapEditorVolume> & GetVolumeManager();
  MapEditorLayerManager<MapPath, MapEditorPath> & GetPathManager();
  MapEditorLayerManager<MapAnchor, MapEditorAnchor> & GetAnchorManager();

  MapDef & GetMapDef();
  MapEditorSelector & GetSelector();
  MapEditorLayerList & GetLayerList();
  MapEditorViewer & GetViewer();

  void SelectManualTile(int layer_index, uint64_t frame_id);
  void SelectManualAnimation(int layer_index, uint64_t frame_id);
  void SetSelectedEntity(int layer_index, czstr entity_file);
  void SetSelectedServerObject(int layer_index, czstr server_object_file);
  void SetSelectedParalaxObject(int layer_index, const MapParalaxLayerObject & paralax_object_data);

  void ClearPropertyPanel();
  void ClearSelectors();

  const RPolymorphic<VolumeDataBase, VolumeTypeDatabase, VolumeDataTypeInfo> & GetVolumeInitData() const;
  void CreateNewVolume(const Box & box);

  const RPolymorphic<PathDataBase, PathTypeDatabase, PathDataTypeInfo> & GetPathInitData() const;
  void CreateNewPath(const Line & line);

  const MapEditorAnchorInitData & GetAnchorInitData() const;
  void CreateNewAnchor(const Vector2 & point);
  void DuplicateAnchorData(int layer_index);

  MapParalaxLayerObject & GetParalaxObjectInitData();
  MapEditorParalaxObjectType & GetParalaxObject();
  void CreateNewParalaxObject(int layer_index, const Vector2 & point);
  void CreateNewParalaxObject(czstr file_name, int layer_index, const Vector2 & point);

  MapEditorTextures & GetTextures();
public:

  void AboutToClose() override;

private:
  MapDef & m_Map;
  MapEditorLayerManager<MapManualTileLayer, MapEditorTileManager> m_ManualTileLayers;
  MapEditorLayerManager<MapEntityLayer, MapEditorEntityManager> m_EntityLayers;
  MapEditorLayerManager<MapServerObjectLayer, MapEditorServerObjectManager> m_ServerObjectLayers;
  MapEditorLayerManager<MapParalaxLayer, MapEditorParalaxLayer> m_ParalaxLayers;
  MapEditorLayerManager<MapEffectLayer, MapEditorEffectLayer> m_EffectLayers;
  MapEditorLayerManager<MapVolume, MapEditorVolume> m_Volumes;
  MapEditorLayerManager<MapPath, MapEditorPath> m_Paths;
  MapEditorLayerManager<MapAnchor, MapEditorAnchor> m_Anchors;

  Optional<MapEditorTextures> m_Textures;

  std::unique_ptr<QGridLayout> m_Layout;
  std::unique_ptr<GenericFrame> m_Properties;

  std::unique_ptr<MapEditorSelector> m_Selector;
  std::unique_ptr<MapEditorLayerList> m_LayerList;
  std::unique_ptr<MapEditorViewer> m_Viewer;

  RPolymorphic<VolumeDataBase, VolumeTypeDatabase, VolumeDataTypeInfo> m_VolumeInitData;
  RPolymorphic<PathDataBase, PathTypeDatabase, PathDataTypeInfo> m_PathInitData;
  MapEditorAnchorInitData m_AnchorInitData;

  MapParalaxLayerObject m_ParalaxInitData;
  MapEditorParalaxObjectType m_ParalaxInitObject;

  PropertyEditor * m_PropertyEditor;
  bool m_IgnoreSelectionChanges;
};
