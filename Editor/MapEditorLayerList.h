#pragma once

#include <QWidget>
#include <QScrollBar>

#include "Runtime/Map/MapDef.refl.h"

#include "DocumentListValueWatcher.h"
#include "DocumentSubValueListMirror.h"
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

public slots:

  void scrollChanged();
  void addManualTileLayer();
  void removeManualTileLayer();
  void addEntityLayer();
  void removeEntityLayer();
  void addParalaxLayer();
  void removeParalaxLayer();
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
  bool m_ParalaxParentExpanded = true;
  bool m_EffectParentExpanded = true;
  bool m_VolumeExpanded = true;
  bool m_PathExpanded = true;

  DocumentSubValueListMirror m_ManualTileLayerMirror;
  DocumentSubValueListMirror m_EntityLayerMirror;
  DocumentSubValueListMirror m_ParalaxLayerMirror;
  DocumentSubValueListMirror m_EffectLayerMirror;
  DocumentSubValueListMirror m_VolumeLayerMirror;
  DocumentSubValueListMirror m_PathLayerMirror;
};
