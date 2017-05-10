#pragma once

#include <QWidget>
#include <QScrollBar>
#include <QImage>

#include "Runtime/Map/MapDef.refl.h"
#include "Runtime/TileSheet/TileSheetResource.h"

#include "Engine/Asset/TextureAsset.h"

#include "DocumentValueWatcher.h"

class MapEditor;

class MapEditorTileSelector : public QWidget
{
  Q_OBJECT;
public:
  MapEditorTileSelector(NotNullPtr<MapEditor> editor, MapDef & map, QWidget * parent = nullptr);
  ~MapEditorTileSelector();

  void LoadManualTileLayer(std::size_t index);
  void Clear();

  void SetLayer(int layer_index);
  void SetSelectedTile(uint64_t frame_id);

protected:

  void LoadTileSheet(czstr file_name);

  void HandleTileSheetReload(NotNullPtr<TileSheetResource> resource);
  void UpdateScroll();
  int VisitElements(Delegate<void, QImage *, int, int, int, int, int, int, int, int, uint64_t> && callback);

protected:

  virtual void paintEvent(QPaintEvent * ev) override;
  virtual void resizeEvent(QResizeEvent * ev) override;
  virtual void mouseMoveEvent(QMouseEvent * ev) override;
  virtual void mousePressEvent(QMouseEvent * ev) override;
  virtual void wheelEvent(QWheelEvent * ev) override;
  virtual void leaveEvent(QEvent * ev) override;

public slots:

  void handleScrollChanged();

private:
  NotNullPtr<MapEditor> m_Editor;
  MapDef & m_Map;

  int m_LayerIndex;

  std::unique_ptr<QScrollBar> m_Scroll;
  bool m_ShowScroll;

  uint64_t m_SelectedFrame;
  uint64_t m_HighlightedFrame;

  TileSheetLoadLink m_TileSheet;
  std::vector<TextureAsset::LoadCallbackLink> m_Textures;

  DocumentValueWatcher m_TileSheetFileWatcher;
};
