#pragma once

#include <QWidget>
#include <QPushButton>
#include <QImage>

#include "Runtime/Map/MapDef.refl.h"
#include "Runtime/Sprite/SpriteResource.h"

#include "Engine/Asset/TextureAsset.h"

#include "MapEditorParallaxLayer.h"
#include "Tools/Editor/Utility/DocumentValueWatcher.h"

class MapEditor;

class MapEditorParallaxObjectSelector : public QWidget
{
  Q_OBJECT;
public:
  MapEditorParallaxObjectSelector(NotNullPtr<MapEditor> editor, MapDef & map, QWidget * parent = nullptr);
  ~MapEditorParallaxObjectSelector();

  void Clear();

  void SetLayer(int layer_index);
  void SetSelectedParallaxObject(czstr parallax_object_file);

protected:

  virtual void paintEvent(QPaintEvent * ev) override;
  virtual void resizeEvent(QResizeEvent * ev) override;

public slots:

  void pickParallaxObject();

private:
  NotNullPtr<MapEditor> m_Editor;
  MapDef & m_Map;

  int m_LayerIndex;

  std::unique_ptr<QPushButton> m_PickParallaxObject;

  std::string m_ParallaxObjectFile;
  MapEditorParallaxObjectType m_ParallaxObject;
};


