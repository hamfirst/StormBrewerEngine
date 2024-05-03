#pragma once

#include "MapEditorToolBase.h"

class MapEditorToolAnchorMultiEditor : public MapEditorToolBase
{
public:
  MapEditorToolAnchorMultiEditor(MapEditor & map_editor, int layer_index);

  virtual void Init();
  virtual void Cleanup();

  virtual void Delete();

  virtual void DrawPreview(const Vector2 & pos, bool alt, bool shift, bool ctrl);

  virtual bool DrawStart(const Vector2 & pos, bool alt, bool shift, bool ctrl);
  virtual void DrawMove(const Vector2 & pos, bool alt, bool shift, bool ctrl);
  virtual void DrawEnd(const Vector2 & pos, bool alt, bool shift, bool ctrl);
  virtual void DrawCancel();

private:

  Vector2 m_Start;

  bool m_SelectMode;
  int m_SelectElem;
};

