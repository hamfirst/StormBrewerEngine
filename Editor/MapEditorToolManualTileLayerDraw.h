#pragma once

#include "MapEditor.h"
#include "MapEditorToolBase.h"

class MapEditorToolManualTileLayerDraw : public MapEditorToolBase
{
public:
  MapEditorToolManualTileLayerDraw(MapEditor & map_editor, int layer_index, uint64_t frame_id);

  virtual void Init();
  virtual void Cleanup();

  virtual void RightClick();

  virtual void DrawPreview(const Vector2 & pos, bool alt, bool shift, bool ctrl);

  virtual bool DrawStart(const Vector2 & pos, bool alt, bool shift, bool ctrl);
  virtual void DrawMove(const Vector2 & pos, bool alt, bool shift, bool ctrl);
  virtual void DrawEnd(const Vector2 & pos, bool alt, bool shift, bool ctrl);
  virtual void DrawCancel();

  MapTile GetPreviewTile(const Vector2 & pos);

protected:

  int m_LayerIndex;
  uint64_t m_FrameId;

  Optional<Vector2> m_LastPreview;
  Optional<Vector2> m_LastDraw;
  Optional<Vector2> m_DrawStart;

  std::vector<Vector2> m_DrawPositions;
  std::vector<MapTile> m_DrawTiles;
};
