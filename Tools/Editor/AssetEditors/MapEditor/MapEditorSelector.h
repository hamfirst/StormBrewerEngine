#pragma once

#include <QWidget>

#include "MapEditorTileSelector.h"
#include "MapEditorEntitySelector.h"
#include "MapEditorServerObjectSelector.h"
#include "MapEditorParallaxObjectSelector.h"

class MapEditorSelector : public QWidget
{
  Q_OBJECT;
public:
  MapEditorSelector(NotNullPtr<MapEditor> editor, MapDef & map, QWidget * parent = nullptr);

  NotNullPtr<MapEditorTileSelector> GetTileSelector();
  NotNullPtr<MapEditorEntitySelector> GetEntitySelector();
  NotNullPtr<MapEditorServerObjectSelector> GetServerObjectSelector();
  NotNullPtr<MapEditorParallaxObjectSelector> GetParallaxObjectSelector();

protected:

  void resizeEvent(QResizeEvent * ev);

private:

  std::unique_ptr<MapEditorTileSelector> m_TileSelector;
  std::unique_ptr<MapEditorEntitySelector> m_EntitySelector;
  std::unique_ptr<MapEditorServerObjectSelector> m_ServerObjectSelector;
  std::unique_ptr<MapEditorParallaxObjectSelector> m_ParallaxObjectSelector;
};


