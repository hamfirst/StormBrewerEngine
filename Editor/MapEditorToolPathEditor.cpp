
#include "Foundation/Math/Util.h"
#include "Foundation/Math/Intersection.h"

#include "MapEditorToolPathEditor.h"
#include "MapEditor.h"


MapEditorToolPathEditor::MapEditorToolPathEditor(MapEditor & map_editor, int layer_index) :
  MapEditorToolBase(map_editor),
  m_LayerIndex(layer_index)
{

}

void MapEditorToolPathEditor::Init()
{

}

void MapEditorToolPathEditor::Cleanup()
{
  auto path = m_MapEditor.GetPathManager().GetLayerManager(m_LayerIndex);
  if (path)
  {
    path->ClearPreview();
  }

  m_MapEditor.GetViewer().ClearSelectionBox();
}

void MapEditorToolPathEditor::DrawPreview(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  auto path = m_MapEditor.GetPathManager().GetLayerManager(m_LayerIndex);
  if (path)
  {
    path->ClearPreview();

    auto screen_space_pos = (Vector2)m_MapEditor.GetViewer().TransformFromMapSpaceToScreenSpace(pos);

    auto points = path->GetPreviewPath();

    if (points && points->size() > 0)
    {
      int best_index = -1;
      float best_dist = 40;

      for (int point = 0; point < points->size(); point++)
      {
        auto point_pos = points->at(point);
        auto screen_space = (Vector2)m_MapEditor.GetViewer().TransformFromMapSpaceToScreenSpace(point_pos);

        auto dist = ManhattanDist(screen_space, screen_space_pos);
        if (dist < best_dist)
        {
          best_dist = dist;
          best_index = point;
          path->SetPreviewPoint(point);
          break;
        }
      }

      if (best_index == -1)
      {
        for (int edge = 0; edge < points->size() - 1; edge++)
        {
          auto start = (Vector2)m_MapEditor.GetViewer().TransformFromMapSpaceToScreenSpace(points->at(edge));
          auto end = (Vector2)m_MapEditor.GetViewer().TransformFromMapSpaceToScreenSpace(points->at(edge + 1));

          auto dist = LineToPointDistance(start, end, screen_space_pos);
          if (dist < best_dist)
          {
            best_dist = dist;
            best_index = edge;
            path->SetPreviewEdge(edge);
            break;
          }
        }
      }
    }
  }
}

bool MapEditorToolPathEditor::DrawStart(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  auto path = m_MapEditor.GetPathManager().GetLayerManager(m_LayerIndex);
  if (path)
  {
    auto snapped_pos = pos;
    m_MapEditor.GetViewer().SnapToGrid(snapped_pos, false);

    m_SelectMode = false;

    if (alt)
    {
      m_Start = snapped_pos;
      auto best_point = path->GetBestNewPointForPosition(pos);
      path->SetPreviewNewPoint(best_point, snapped_pos);
      return true;
    }
    else if (ctrl)
    {
      path->RemovePreviewPoint();
      return false;
    }
    else if (path->GetPreviewPoint() || path->GetPreviewEdge())
    {
      m_Start = snapped_pos;
      return true;
    }
    else
    {
      path->ClearSelectedPoints();

      m_SelectMode = true;
      m_Start = pos;
      return true;
    }
  }

  return false;
}

void MapEditorToolPathEditor::DrawMove(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  auto path = m_MapEditor.GetPathManager().GetLayerManager(m_LayerIndex);
  if (path)
  {
    if (m_SelectMode)
    {
      auto box = Box::FromPoints(m_Start, pos);
      m_MapEditor.GetViewer().SetSelectionBox(box);

      path->SelectPoints(box);
    }
    else
    {
      auto snapped_pos = pos;
      m_MapEditor.GetViewer().SnapToGrid(snapped_pos, false);

      auto offset = snapped_pos - m_Start;
      path->SetPreviewOffset(offset);
    }
  }
}

void MapEditorToolPathEditor::DrawEnd(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  auto path = m_MapEditor.GetPathManager().GetLayerManager(m_LayerIndex);
  if (path)
  {
    path->CommitPreview();
  }

  m_MapEditor.GetViewer().ClearSelectionBox();
}

void MapEditorToolPathEditor::DrawCancel()
{
  auto path = m_MapEditor.GetPathManager().GetLayerManager(m_LayerIndex);
  if (path)
  {
    path->ClearPreview();
  }

  m_MapEditor.GetViewer().ClearSelectionBox();
}
