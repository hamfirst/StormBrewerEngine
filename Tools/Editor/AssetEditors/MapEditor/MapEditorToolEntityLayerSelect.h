#pragma once

#include "MapEditorToolBase.h"

class MapEditorToolEntityLayerSelect : public MapEditorToolBase
{
public:
  MapEditorToolEntityLayerSelect(MapEditor & map_editor, int layer_index);

  virtual void Init();
  virtual void Cleanup();

  virtual void Delete();

  virtual bool DrawStart(const Vector2 & pos, bool alt, bool shift, bool ctrl);
  virtual void DrawMove(const Vector2 & pos, bool alt, bool shift, bool ctrl);
  virtual void DrawEnd(const Vector2 & pos, bool alt, bool shift, bool ctrl);
  virtual void DrawCancel();

private:

  Vector2 m_Start;
  int m_LayerIndex;
  bool m_MoveMode;
};





