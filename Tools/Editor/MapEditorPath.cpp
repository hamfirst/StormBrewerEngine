
#include "StormData/StormDataJson.h"

#include "Foundation/BasicTypes/BasicTypeFuncs.h"
#include "Foundation/Math/Intersection.h"

#include "Runtime/Map/MapTileJson.h"
#include "Runtime/Map/MapDef.refl.meta.h"

#include "Engine/Rendering/VertexBufferBuilder.h"
#include "Engine/Rendering/RenderUtil.h"
#include "Engine/Rendering/VertexList.h"
#include "Engine/Shader/ShaderManager.h"

#include "MapEditorPath.h"
#include "MapEditor.h"
#include "DrawUtil.h"


MapEditorPath::MapEditorPath(NotNullPtr<MapEditor> editor, MapDef & map, int layer_index) :
  m_Editor(editor),
  m_Map(map),
  m_LayerIndex(layer_index)
{

}

Optional<std::vector<Vector2>> MapEditorPath::GetPreviewPath()
{
  auto path = m_Map.m_Paths.TryGet(m_LayerIndex);
  if (path == nullptr)
  {
    return{};
  }

  std::vector<Vector2> points;

  for (auto point_info : path->m_Points)
  {
    auto pos = Vector2(point_info.second.m_X, point_info.second.m_Y);
    if (m_SelectedPoints.size() > 0 && vfind(m_SelectedPoints, point_info.first))
    {
      points.push_back(pos + m_Offset);
    }
    else if (m_PreviewPoint && m_PreviewPoint.Value() == (int)points.size())
    {
      points.push_back(pos + m_Offset);
    }
    else if (m_PreviewEdge && (m_PreviewEdge.Value() == (int)points.size() || m_PreviewEdge.Value() == (int)points.size() - 1))
    {
      points.push_back(pos + m_Offset);
    }
    else
    {
      points.push_back(pos);
    }
  }

  if (m_PreviewNewPoint)
  {
    points.insert(points.begin() + m_PreviewNewPoint.Value(), m_NewPointPosition + m_Offset);
  }

  return std::move(points);
}

Optional<std::vector<int>> MapEditorPath::GetSelectedPreviewPath()
{
  auto path = m_Map.m_Paths.TryGet(m_LayerIndex);
  if (path == nullptr)
  {
    return{};
  }

  std::vector<int> sel_points;
  int point_index = 0;
  for (auto point_info : path->m_Points)
  {
    if (vfind(m_SelectedPoints, point_info.first))
    {
      sel_points.push_back(point_index);
    }

    point_index++;
  }

  return std::move(sel_points);
}

void MapEditorPath::Draw(GeometryVertexBufferBuilder & buffer, const Box & viewport_bounds, RenderVec2 & screen_center, float magnification)
{
  auto points = GetPreviewPath();
  if (points == false)
  {
    return;
  }

  if (points->size() == 0)
  {
    return;
  }

  for (int edge = 0; edge < points->size() - 1; edge++)
  {
    auto start = points->at(edge);
    auto end = points->at(edge + 1);
    if (m_PreviewEdge && m_PreviewEdge.Value() == edge)
    {
      DrawUtil::DrawHighlightedLine(buffer, start, end, magnification);
    }
    else
    {
      DrawUtil::DrawLine(buffer, start, end, magnification);
    }
  }
}

void MapEditorPath::DrawControls(GeometryVertexBufferBuilder & buffer, const Box & viewport_bounds, RenderVec2 & screen_center, float magnification)
{
  auto points = GetPreviewPath();
  auto sel_points = GetSelectedPreviewPath();

  for (int point = 0; point < points->size(); point++)
  {
    auto pos = points->at(point);
    if (m_PreviewPoint && m_PreviewPoint.Value() == point)
    {
      DrawUtil::DrawHighlightedCornerControl(buffer, pos, magnification);
    }
    else if (vfind(sel_points.Value(), point))
    {
      DrawUtil::DrawSelectedCornerControl(buffer, pos, magnification);
    }
    else
    {
      DrawUtil::DrawCornerControl(buffer, pos, magnification);
    }
  }
}

void MapEditorPath::SetPreviewOffset(Vector2 offset)
{
  m_Offset = offset;
}

void MapEditorPath::SetPreviewPoint(int preview_point)
{
  ClearPreview();
  m_PreviewPoint = preview_point;

  m_Offset = {};
}

void MapEditorPath::SetPreviewEdge(int preview_edge)
{
  ClearPreview();
  m_PreviewEdge = preview_edge;

  m_Offset = {};
}

void MapEditorPath::SetPreviewNewPoint(int preview_point, const Vector2 & position)
{
  ClearPreview();
  ClearSelectedPoints();

  m_PreviewNewPoint = preview_point;
  m_NewPointPosition = position;

  m_Offset = {};
}

void MapEditorPath::SelectPoints(const Box & box)
{
  ClearPreview();
  ClearSelectedPoints();

  auto path = m_Map.m_Paths.TryGet(m_LayerIndex);
  if (path == nullptr)
  {
    return;
  }

  std::vector<Vector2> points;
  for (auto point_info : path->m_Points)
  {
    auto pos = Vector2(point_info.second.m_X, point_info.second.m_Y);

    if (PointInBox(box, pos))
    {
      m_SelectedPoints.push_back(point_info.first);
    }
  }
}

void MapEditorPath::ClearSelectedPoints()
{
  m_SelectedPoints.clear();
}

void MapEditorPath::RemovePreviewPoint()
{
  if (m_PreviewPoint == false)
  {
    return;
  }

  auto preview_path = GetPreviewPath();
  if (preview_path == false)
  {
    return;
  }

  if (m_PreviewPoint.Value() >= preview_path->size())
  {
    return;
  }

  preview_path->erase(preview_path->begin() + m_PreviewPoint.Value());

  WriteData(preview_path.Value());
}

void MapEditorPath::CommitPreview()
{
  if (m_Offset.x == 0 && m_Offset.y == 0 && m_PreviewNewPoint == false)
  {
    return;
  }

  auto preview_path = GetPreviewPath();
  if (preview_path == false)
  {
    return;
  }

  ClearPreview();
  m_Offset = {};

  WriteData(preview_path.Value());
}

void MapEditorPath::ClearPreview()
{
  m_PreviewPoint.Clear();
  m_PreviewEdge.Clear();
  m_PreviewNewPoint.Clear();
}

void MapEditorPath::WriteData(std::vector<Vector2> & points)
{
  auto path = m_Map.m_Paths.TryGet(m_LayerIndex);
  if (path != nullptr)
  {
    RMergeList<MapPathPoint> new_points;
    for (auto & point : points)
    {
      MapPathPoint p;
      p.m_X = point.x;
      p.m_Y = point.y;
      new_points.EmplaceBack(p);
    }

    path->m_Points = std::move(new_points);
  }
}

Optional<int> MapEditorPath::GetPreviewPoint()
{
  return m_PreviewPoint;
}

Optional<int> MapEditorPath::GetPreviewEdge()
{
  return m_PreviewEdge;
}

int MapEditorPath::GetBestNewPointForPosition(const Vector2 & pos)
{
  if (m_PreviewEdge)
  {
    return m_PreviewEdge.Value() + 1;
  }

  auto preview_path = GetPreviewPath();
  if (preview_path == false || preview_path->size() <= 1)
  {
    return 0;
  }

  std::vector<float> distances;

  int best_index = 0;
  float best_dist = 100000.0f;

  for (std::size_t index = 0, end = preview_path->size(); index < end; ++index)
  {
    auto dist = IntersectionVecFuncs<Vector2>::Dist(pos, preview_path->at(index));
    distances.push_back(dist);

    if (best_dist > dist)
    {
      best_dist = dist;
      best_index = index;
    }
  }

  if(best_index == 0)
  {
    if (distances[0] < distances[1])
    {
      return 0;
    }

    return 1;
  }

  int last_index = preview_path->size() - 1;
  if (best_index == last_index)
  {
    if (distances[last_index] < distances[last_index - 1])
    {
      return last_index + 1;
    }

    return last_index;
  }

  if (distances[best_index - 1] < distances[best_index + 1])
  {
    return best_index;
  }

  return best_index + 1;
}

void MapEditorPath::ToggleHidden()
{
  m_Hidden = !m_Hidden;
}

void MapEditorPath::SetHidden(bool hidden)
{
  m_Hidden = hidden;
}

bool MapEditorPath::IsHidden()
{
  return m_Hidden;
}

