#pragma once

#include <QWidget>
#include <QPushButton>
#include <QImage>

#include "Runtime/Map/MapDef.refl.h"
#include "Runtime/ServerObject/ServerObjectResource.h"
#include "Runtime/Entity/EntityResource.h"

#include "Tools/Editor/Utility/DocumentValueWatcher.h"

class MapEditor;

class MapEditorServerObjectSelector : public QWidget
{
  Q_OBJECT;
public:
  MapEditorServerObjectSelector(NotNullPtr<MapEditor> editor, MapDef & map, QWidget * parent = nullptr);
  ~MapEditorServerObjectSelector();

  void Clear();

  void SetLayer(int layer_index);
  void SetSelectedServerObject(czstr entity_file);

protected:

  void LoadEntity();

protected:

  virtual void paintEvent(QPaintEvent * ev) override;
  virtual void resizeEvent(QResizeEvent * ev) override;

public slots:

  void pickServerObject();

private:
  NotNullPtr<MapEditor> m_Editor;
  MapDef & m_Map;

  int m_LayerIndex;

  std::unique_ptr<QPushButton> m_PickServerObject;

  std::string m_ServerObjectFile;
  ServerObjectLoadLink m_ServerObject;
  EntityLoadLink m_Entity;
};


