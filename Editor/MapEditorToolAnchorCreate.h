#pragma once

#include "MapEditorToolBase.h"

class MapEditorToolAnchorCreate : public MapEditorToolBase
{
public:
  MapEditorToolAnchorCreate(MapEditor & map_editor);

  virtual void Init();
  virtual void Cleanup();

  virtual void RightClick();

  virtual void DrawPreview(const Vector2 & pos, bool alt, bool shift, bool ctrl);

  virtual bool DrawStart(const Vector2 & pos, bool alt, bool shift, bool ctrl);
  virtual void DrawMove(const Vector2 & pos, bool alt, bool shift, bool ctrl);
  virtual void DrawEnd(const Vector2 & pos, bool alt, bool shift, bool ctrl);
  virtual void DrawCancel();

private:

};

