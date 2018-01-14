#pragma once

#include "MapEditorToolBase.h"
#include "MapEditorLayer.h"

class MapEditorToolAllLayers : public MapEditorToolBase
{
public:
  MapEditorToolAllLayers(MapEditor & map_editor);

  virtual void Init();
  virtual void Cleanup();

  virtual void Delete();

  virtual void DrawPreview(const Vector2 & pos, bool alt, bool shift, bool ctrl);

  virtual bool DrawStart(const Vector2 & pos, bool alt, bool shift, bool ctrl);
  virtual void DrawMove(const Vector2 & pos, bool alt, bool shift, bool ctrl);
  virtual void DrawEnd(const Vector2 & pos, bool alt, bool shift, bool ctrl);
  virtual void DrawCancel();

private:

  Optional<MapEditorLayerSelection> PickLayer(const Vector2 & pos);

  Vector2 m_Start;
  bool m_MoveMode;
};





