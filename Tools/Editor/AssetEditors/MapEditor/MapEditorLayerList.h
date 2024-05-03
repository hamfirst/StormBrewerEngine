#pragma once

#include <QWidget>
#include <QScrollBar>

#include "Runtime/Map/MapDef.refl.h"

#include "Tools/Editor/Utility/DocumentListValueWatcher.h"
#include "Tools/Editor/Utility/DocumentSubValueListMirror.h"
#include "MapEditorLayer.h"

class MapEditor;
class MapEditorLayerList;

class MapEditorLayerList : public QWidget
{
  Q_OBJECT;
public:
  MapEditorLayerList(NotNullPtr<MapEditor> editor, MapDef & map, QWidget * parent = nullptr);

  void ChangeLayerSelection(const MapEditorLayerSelection & layer);
  void ClearLayerSelection();

  void ToggleSelectedLayer();
  bool IsLayerHidden(const MapEditorLayerSelection & layer);
  void SetHideLayer(const MapEditorLayerSelection & layer, bool hidden);
  void DeleteLayer(const MapEditorLayerSelection & layer);

protected:

  int VisitElements(Delegate<bool, const MapEditorLayerSelection &, int> && visitor);
  Optional<MapEditorLayerSelection> GetLayerForPosition(int y);

  void LayerRemoved(const MapEditorLayerSelection & layer);
  void UpdateScroll();

protected:
  void paintEvent(QPaintEvent * ev) override;
  void resizeEvent(QResizeEvent * ev) override;

  void keyPressEvent(QKeyEvent * ev) override;

  void mousePressEvent(QMouseEvent * ev) override;
  void wheelEvent(QWheelEvent * ev) override;

public slots:

  void scrollChanged();
  void buildPathfinding();
  void clearPathfinding();
  void addManualTileLayer();
  void removeManualTileLayer();
  void addEntityLayer();
  void removeEntityLayer();
  void addServerObjectLayer();
  void removeServerObjectLayer();
  void addParallaxLayer();
  void removeParallaxLayer();
  void addEffectLayer();
  void removeEffectLayer();

private:
  friend struct MapEditorLayerListElement;

  NotNullPtr<MapEditor> m_Editor;
  MapDef & m_Map;

  Optional<MapEditorLayerSelection> m_Selection;

  std::unique_ptr<QScrollBar> m_ScrollBar;

  bool m_SelectNewLayers;
  bool m_ManualTileParentExpanded = true;
  bool m_EntityParentExpanded = true;
  bool m_ServerObjectParentExpanded = true;
  bool m_ParallaxParentExpanded = true;
  bool m_EffectParentExpanded = true;
  bool m_VolumeExpanded = true;
  bool m_PathExpanded = true;
  bool m_AnchorExpanded = true;

  DocumentSubValueListMirror m_ManualTileLayerMirror;
  DocumentSubValueListMirror m_EntityLayerMirror;
  DocumentSubValueListMirror m_ServerObjectLayerMirror;
  DocumentSubValueListMirror m_ParallaxLayerMirror;
  DocumentSubValueListMirror m_EffectLayerMirror;
  DocumentSubValueListMirror m_VolumeLayerMirror;
  DocumentSubValueListMirror m_PathLayerMirror;
  DocumentSubValueListMirror m_AnchorLayerMirror;
};
