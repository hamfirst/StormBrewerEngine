#pragma once

#include "MapEditorToolBase.h"

class MapEditorToolServerObjectLayerDraw : public MapEditorToolBase
{
public:
  MapEditorToolServerObjectLayerDraw(MapEditor & map_editor, int layer_index, czstr ServerObject_file);

  virtual void Init();
  virtual void Cleanup();

  virtual void RightClick();

  virtual void DrawPreview(const Vector2 & pos, bool alt, bool shift, bool ctrl);

  virtual bool DrawStart(const Vector2 & pos, bool alt, bool shift, bool ctrl);

private:

  int m_LayerIndex;
  std::string m_ServerObjectFile;
};

