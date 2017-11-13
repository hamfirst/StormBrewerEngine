#pragma once

#include <QWidget>
#include <QPushButton>
#include <QImage>

#include "Runtime/Map/MapDef.refl.h"
#include "Runtime/Sprite/SpriteResource.h"

#include "Engine/Asset/TextureAsset.h"

#include "DocumentValueWatcher.h"

class MapEditor;

class MapEditorParalaxObjectSelector : public QWidget
{
  Q_OBJECT;
public:
  MapEditorParalaxObjectSelector(NotNullPtr<MapEditor> editor, MapDef & map, QWidget * parent = nullptr);
  ~MapEditorParalaxObjectSelector();

  void Clear();

  void SetLayer(int layer_index);
  void SetSelectedParalaxObject(czstr paralax_object_file);

protected:

  virtual void paintEvent(QPaintEvent * ev) override;
  virtual void resizeEvent(QResizeEvent * ev) override;

public slots:

  void pickParalaxObject();

private:
  NotNullPtr<MapEditor> m_Editor;
  MapDef & m_Map;

  int m_LayerIndex;

  std::unique_ptr<QPushButton> m_PickParalaxObject;

  std::string m_ParalaxObjectFile;
  Variant<TextureAsset::LoadCallbackLink, SpriteLoadLink> m_ParalaxObject;
};


