#pragma once

#include "Foundation/Common.h"

#include "Runtime/Map/MapDef.refl.h"

#include "Engine/Rendering/GeometryVertexBufferBuilder.h"

#include "DocumentValueWatcher.h"

class MapEditor;
class RenderUtil;

class MapEditorPath
{
public:
  MapEditorPath(NotNullPtr<MapEditor> editor, MapDef & map, int layer_index);

  Optional<std::vector<Vector2>> GetPreviewPath();
  Optional<std::vector<int>> GetSelectedPreviewPath();

  void Draw(GeometryVertexBufferBuilder & builder, const Box & viewport_bounds, RenderVec2 & screen_center, float magnification);
  void DrawControls(GeometryVertexBufferBuilder & builder, const Box & viewport_bounds, RenderVec2 & screen_center, float magnification);

  void SetPreviewOffset(Vector2 offset);
  void SetPreviewPoint(int preview_point);
  void SetPreviewEdge(int preview_edge);
  void SetPreviewNewPoint(int preview_point, const Vector2 & position);
  void SelectPoints(const Box & box);
  void ClearSelectedPoints();

  void RemovePreviewPoint();

  void CommitPreview();
  void ClearPreview();

  void WriteData(std::vector<Vector2> & points);

  Optional<int> GetPreviewPoint();
  Optional<int> GetPreviewEdge();
  int GetBestNewPointForPosition(const Vector2 & pos);

  void ToggleHidden();
  void SetHidden(bool hidden);
  bool IsHidden();

private:
  NotNullPtr<MapEditor> m_Editor;

  Optional<int> m_PreviewPoint;
  Optional<int> m_PreviewEdge;
  Optional<int> m_PreviewNewPoint;
  std::vector<std::size_t> m_SelectedPoints;
  Vector2 m_Offset;
  Vector2 m_NewPointPosition;

  MapDef & m_Map;
  int m_LayerIndex;
  bool m_Hidden = false;
};
