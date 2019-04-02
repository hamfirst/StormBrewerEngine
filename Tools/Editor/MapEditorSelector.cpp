
#include "MapEditorSelector.h"

MapEditorSelector::MapEditorSelector(NotNullPtr<MapEditor> editor, MapDef & map, QWidget * parent) :
  m_TileSelector(std::make_unique<MapEditorTileSelector>(editor, map, this)),
  m_EntitySelector(std::make_unique<MapEditorEntitySelector>(editor, map, this)),
  m_ServerObjectSelector(std::make_unique<MapEditorServerObjectSelector>(editor, map, this)),
  m_ParallaxObjectSelector(std::make_unique<MapEditorParallaxObjectSelector>(editor, map, this))
{
  m_TileSelector->hide();
  m_EntitySelector->hide();
  m_ServerObjectSelector->hide();
  m_ParallaxObjectSelector->hide();
}

NotNullPtr<MapEditorTileSelector> MapEditorSelector::GetTileSelector()
{
  return m_TileSelector.get();
}

NotNullPtr<MapEditorEntitySelector> MapEditorSelector::GetEntitySelector()
{
  return m_EntitySelector.get();
}

NotNullPtr<MapEditorServerObjectSelector> MapEditorSelector::GetServerObjectSelector()
{
  return m_ServerObjectSelector.get();
}

NotNullPtr<MapEditorParallaxObjectSelector> MapEditorSelector::GetParallaxObjectSelector()
{
  return m_ParallaxObjectSelector.get();
}

void MapEditorSelector::resizeEvent(QResizeEvent * ev)
{
  m_TileSelector->setGeometry(0, 0, width(), height());
  m_EntitySelector->setGeometry(0, 0, width(), height());
  m_ServerObjectSelector->setGeometry(0, 0, width(), height());
  m_ParallaxObjectSelector->setGeometry(0, 0, width(), height());
}
