#pragma once

#include <QWidget>
#include <QPushButton>
#include <QImage>

#include "Runtime/Map/MapDef.refl.h"
#include "Runtime/Entity/EntityResource.h"

#include "DocumentValueWatcher.h"

class MapEditor;

class MapEditorEntitySelector : public QWidget
{
  Q_OBJECT;
public:
  MapEditorEntitySelector(NotNullPtr<MapEditor> editor, MapDef & map, QWidget * parent = nullptr);
  ~MapEditorEntitySelector();

  void Clear();

  void SetLayer(int layer_index);
  void SetSelectEntity(czstr entity_file);

protected:

  virtual void paintEvent(QPaintEvent * ev) override;
  virtual void resizeEvent(QResizeEvent * ev) override;

public slots:

  void pickEntity();

private:
  NotNullPtr<MapEditor> m_Editor;
  MapDef & m_Map;

  int m_LayerIndex;

  std::unique_ptr<QPushButton> m_PickEntity;

  std::string m_EntityFile;
  EntityLoadLink m_Entity;
};


