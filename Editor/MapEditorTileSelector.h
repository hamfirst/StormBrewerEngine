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
  void SetSelectedAnimation(uint64_t frame_id);

protected:

  void LoadTileSheet(czstr file_name);

  void HandleTileSheetReload(NotNullPtr<TileSheetResource> resource);
  void UpdateScroll();
  Vector2 VisitElements(Delegate<void, QImage *, int, int, int, int, int, int, int, int, uint64_t, bool> && callback);

protected:

  virtual void paintEvent(QPaintEvent * ev) override;
  virtual void resizeEvent(QResizeEvent * ev) override;
  virtual void mouseMoveEvent(QMouseEvent * ev) override;
  virtual void mousePressEvent(QMouseEvent * ev) override;
  virtual void wheelEvent(QWheelEvent * ev) override;
  virtual void leaveEvent(QEvent * ev) override;

public slots:

  void handleScrollChanged();
  void tick();

private:
  NotNullPtr<MapEditor> m_Editor;
  MapDef & m_Map;

  int m_LayerIndex;
  int m_NumFrames;

  std::unique_ptr<QScrollBar> m_ScrollX;
  std::unique_ptr<QScrollBar> m_ScrollY;
  bool m_ShowScrollX;
  bool m_ShowScrollY;

  bool m_SelectedAnimation;
  uint64_t m_SelectedFrame;

  bool m_HighlightedAnimation;
  uint64_t m_HighlightedFrame;

  TileSheetLoadLink m_TileSheet;
  std::vector<TextureAsset::LoadCallbackLink> m_Textures;

  DocumentValueWatcher m_TileSheetFileWatcher;
};
