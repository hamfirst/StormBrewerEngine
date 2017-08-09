#pragma once

#include "Foundation/Common.h"

#include "Runtime/Map/MapDef.refl.h"

#include "Engine/Rendering/GeometryVertexBufferBuilder.h"

#include "DocumentValueWatcher.h"

class MapEditor;
class RenderUtil;

class MapEditorAnchor
{
public:
  MapEditorAnchor(NotNullPtr<MapEditor> editor, MapDef & map, int layer_index);

  Optional<Vector2> GetPreviewAnchor();

  void Draw(GeometryVertexBufferBuilder & builder, const Box & viewport_bounds, RenderVec2 & screen_center, float magnification);
  void DrawControls(GeometryVertexBufferBuilder & builder, const Box & viewport_bounds, RenderVec2 & screen_center, float magnification);

  void SetSelected();
  void ClearSelected();
  bool IsSelected();
  void Select(const Box & selection_box);

  void SetHighlighted();
  void ClearHighlighted();
  bool IsHighlighted();

  void SetPreviewOffset(Vector2 offset);
  void CommitPreview();
  void ClearPreview();

  void WriteData(const Vector2 & pos);

  void ToggleHidden();
  void SetHidden(bool hidden);
  bool IsHidden();

private:
  NotNullPtr<MapEditor> m_Editor;

  bool m_Selected = false;
  bool m_Highlighted = false;
  Optional<Vector2> m_Offset;

  MapDef & m_Map;
  int m_LayerIndex;
  bool m_Hidden = false;
};
