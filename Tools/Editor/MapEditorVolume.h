#pragma once

#include "Foundation/Common.h"

#include "Runtime/Map/MapDef.refl.h"

#include "Engine/Rendering/GeometryVertexBufferBuilder.h"

#include "DocumentValueWatcher.h"

class MapEditor;

class MapEditorVolume
{
public:
  MapEditorVolume(NotNullPtr<MapEditor> editor, MapDef & map, int layer_index);

  Optional<Box> GetPreviewBox();

  void Draw(GeometryVertexBufferBuilder & builder, const Box & viewport_bounds, RenderVec2 & screen_center, float magnification);
  void DrawControls(GeometryVertexBufferBuilder & builder, const Box & viewport_bounds, RenderVec2 & screen_center, float magnification);

  void SetPreviewPointOffset(Vector2 offset);
  void SetPreviewEdgeOffset(int offset);
  void SetPreviewPoint(int preview_point);
  void SetPreviewEdge(int preview_edge);

  void CommitPreview();
  void ClearPreview();

  Optional<int> GetPreviewPoint();
  Optional<int> GetPreviewEdge();

  void ToggleHidden();
  void SetHidden(bool hidden);
  bool IsHidden();

private:
  NotNullPtr<MapEditor> m_Editor;

  Optional<int> m_PreviewPoint;
  Optional<int> m_PreviewEdge;
  int m_EdgeOffset;
  Vector2 m_PointOffset;

  MapDef & m_Map;
  int m_LayerIndex;
  bool m_Hidden = false;
};
