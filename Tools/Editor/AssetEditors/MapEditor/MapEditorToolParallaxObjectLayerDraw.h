#pragma once

#include "MapEditorToolBase.h"

class MapEditorToolParallaxObjectLayerDraw : public MapEditorToolBase
{
public:
  MapEditorToolParallaxObjectLayerDraw(MapEditor & map_editor, int layer_index);

  virtual void Init();
  virtual void Cleanup();

  virtual void RightClick();

  virtual void DrawPreview(const Vector2 & pos, bool alt, bool shift, bool ctrl);

  virtual bool DrawStart(const Vector2 & pos, bool alt, bool shift, bool ctrl);

private:

  int m_LayerIndex;
};

