#pragma once

#include "Foundation/Common.h"

class MapEditor;

class MapEditorToolBase
{
public:
  MapEditorToolBase(MapEditor & map_editor);

  virtual void Init();
  virtual void Cleanup();
  virtual void DrawPreview(const Vector2 & pos, bool alt, bool shift, bool ctrl);
  virtual void RightClick();
  virtual void Delete();

  virtual bool DrawStart(const Vector2 & pos, bool alt, bool shift, bool ctrl);
  virtual void DrawMove(const Vector2 & pos, bool alt, bool shift, bool ctrl);
  virtual void DrawEnd(const Vector2 & pos, bool alt, bool shift, bool ctrl);
  virtual void DrawCancel();

  void Snap(Vector2 & pos);

protected:
  MapEditor & m_MapEditor;
};

