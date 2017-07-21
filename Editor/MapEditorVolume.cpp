
#include "StormData/StormDataJson.h"

#include "Foundation/BasicTypes/BasicTypeFuncs.h"

#include "Runtime/Map/MapTileJson.h"

#include "Engine/Rendering/VertexBufferBuilder.h"
#include "Engine/Rendering/RenderUtil.h"
#include "Engine/Rendering/VertexList.h"
#include "Engine/Shader/ShaderManager.h"

#include "MapEditorVolume.h"
#include "MapEditor.h"
#include "DrawUtil.h"


MapEditorVolume::MapEditorVolume(NotNullPtr<MapEditor> editor, MapDef & map, int layer_index) :
  m_Editor(editor),
  m_Map(map),
  m_LayerIndex(layer_index)
{

}

Optional<Box> MapEditorVolume::GetPreviewBox()
{
  auto volume = m_Map.m_Volumes.TryGet(m_LayerIndex);
  if (volume == nullptr)
  {
    return{};
  }

  Box box = Box{ Vector2(volume->m_XStart, volume->m_YStart), Vector2(volume->m_XEnd, volume->m_YEnd) };

  if (m_PreviewPoint)
  {
    auto point = Box::GetPoint(box, m_PreviewPoint.Value());
    point += m_PointOffset;
    Box::SetPoint(box, m_PreviewPoint.Value(), point);
    box = Box::FromPoints(box.m_Start, box.m_End);
  }
  else if (m_PreviewEdge)
  {
    Box::OffsetEdge(box, m_PreviewEdge.Value(), m_EdgeOffset);
  }

  return box;
}

void MapEditorVolume::Draw(GeometryVertexBufferBuilder & buffer, const Box & viewport_bounds, RenderVec2 & screen_center, float magnification)
{
  auto box = GetPreviewBox();
  if (box == false)
  {
    return;
  }

  DrawUtil::DrawBox(buffer, box.Value());

  for (int edge = 0; edge < 4; edge++)
  {
    auto line = Box::GetEdge(box.Value(), edge);
    if (m_PreviewEdge && m_PreviewEdge.Value() == edge)
    {
      DrawUtil::DrawHighlightedLine(buffer, line.m_Start, line.m_End, magnification);
    }
    else
    {
      DrawUtil::DrawLine(buffer, line.m_Start, line.m_End, magnification);
    }
  }
}

void MapEditorVolume::DrawControls(GeometryVertexBufferBuilder & buffer, const Box & viewport_bounds, RenderVec2 & screen_center, float magnification)
{
  auto box = GetPreviewBox();
  if (box == false)
  {
    return;
  }

  for (int point = 0; point < 4; point++)
  {
    auto pos = Box::GetPoint(box.Value(), point);
    if (m_PreviewPoint && m_PreviewPoint.Value() == point)
    {
      DrawUtil::DrawHighlightedCornerControl(buffer, pos, magnification);
    }
    else
    {
      DrawUtil::DrawCornerControl(buffer, pos, magnification);
    }
  }
}

void MapEditorVolume::SetPreviewPointOffset(Vector2 offset)
{
  m_PointOffset = offset;
}

void MapEditorVolume::SetPreviewEdgeOffset(int offset)
{
  m_EdgeOffset = offset;
}

void MapEditorVolume::SetPreviewPoint(int preview_point)
{
  m_PreviewPoint = preview_point;
  m_PreviewEdge.Clear();

  m_PointOffset = {};
}

void MapEditorVolume::SetPreviewEdge(int preview_edge)
{
  m_PreviewPoint.Clear();
  m_PreviewEdge = preview_edge;

  m_EdgeOffset = {};
}

void MapEditorVolume::ClearPreview()
{
  m_PreviewPoint.Clear();
  m_PreviewEdge.Clear();
}

void MapEditorVolume::CommitPreview()
{
  auto preview_box = GetPreviewBox();
  ClearPreview();
  auto old_box = GetPreviewBox();

  if (preview_box == false)
  {
    return;
  }

  if (old_box.Value() == preview_box.Value())
  {
    return;
  }

  auto volume = m_Map.m_Volumes.TryGet(m_LayerIndex);
  if (volume != nullptr)
  {
    m_Editor->BeginTransaction();
    volume->m_XStart = preview_box->m_Start.x;
    volume->m_YStart = preview_box->m_Start.y;
    volume->m_XEnd = preview_box->m_End.x;
    volume->m_YEnd = preview_box->m_End.y;
    m_Editor->CommitChanges();
  }
}

Optional<int> MapEditorVolume::GetPreviewPoint()
{
  return m_PreviewPoint;
}

Optional<int> MapEditorVolume::GetPreviewEdge()
{
  return m_PreviewEdge;
}

void MapEditorVolume::ToggleHidden()
{
  m_Hidden = !m_Hidden;
}

void MapEditorVolume::SetHidden(bool hidden)
{
  m_Hidden = hidden;
}

bool MapEditorVolume::IsHidden()
{
  return m_Hidden;
}

