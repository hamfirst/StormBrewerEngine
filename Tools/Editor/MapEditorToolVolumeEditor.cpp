
#include "Foundation/Math/Util.h"
#include "Foundation/Math/Intersection.h"

#include "MapEditorToolVolumeEditor.h"
#include "MapEditor.h"


MapEditorToolVolumeEditor::MapEditorToolVolumeEditor(MapEditor & map_editor, int layer_index) :
  MapEditorToolBase(map_editor),
  m_LayerIndex(layer_index)
{

}

void MapEditorToolVolumeEditor::Init()
{

}

void MapEditorToolVolumeEditor::Cleanup()
{
  auto volume = m_MapEditor.GetVolumeManager().GetLayerManager(m_LayerIndex);
  if (volume)
  {
    volume->ClearPreview();
  }
}

void MapEditorToolVolumeEditor::DrawPreview(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  auto volume = m_MapEditor.GetVolumeManager().GetLayerManager(m_LayerIndex);
  if (volume)
  {
    volume->ClearPreview();

    auto screen_space_pos = (Vector2)m_MapEditor.GetViewer().TransformFromMapSpaceToScreenSpace(pos);

    auto box = volume->GetPreviewBox();

    if (box)
    {
      int best_index = -1;
      float best_dist = 40;

      for (int point = 0; point < 4; point++)
      {
        auto point_pos = Box::GetPoint(box.Value(), point);
        auto screen_space = (Vector2)m_MapEditor.GetViewer().TransformFromMapSpaceToScreenSpace(point_pos);

        auto dist = ManhattanDist(screen_space, screen_space_pos);
        if (dist < best_dist)
        {
          best_dist = dist;
          best_index = point;
          volume->SetPreviewPoint(point);
          break;
        }
      }

      if (best_index == -1)
      {
        for (int edge = 0; edge < 4; edge++)
        {
          auto line = Box::GetEdge(box.Value(), edge);
          auto start = (Vector2)m_MapEditor.GetViewer().TransformFromMapSpaceToScreenSpace(line.m_Start);
          auto end = (Vector2)m_MapEditor.GetViewer().TransformFromMapSpaceToScreenSpace(line.m_End);

          auto dist = LineToPointDistance(start, end, screen_space_pos);
          if (dist < best_dist)
          {
            best_dist = dist;
            best_index = edge;
            volume->SetPreviewEdge(edge);
            break;
          }
        }
      }
    }
  }
}

bool MapEditorToolVolumeEditor::DrawStart(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  auto volume = m_MapEditor.GetVolumeManager().GetLayerManager(m_LayerIndex);
  if (volume)
  {
    if (volume->GetPreviewPoint())
    {
      auto snapped_pos = pos;
      m_MapEditor.GetViewer().SnapToGrid(snapped_pos);

      m_Start = snapped_pos;
      return true;
    }
    else if (volume->GetPreviewEdge())
    {
      auto snapped_pos = pos;
      m_MapEditor.GetViewer().SnapToGrid(snapped_pos);

      m_Start = snapped_pos;
      return true;
    }
  }

  return false;
}

void MapEditorToolVolumeEditor::DrawMove(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  auto volume = m_MapEditor.GetVolumeManager().GetLayerManager(m_LayerIndex);
  if (volume)
  {
    auto snapped_pos = pos;
    m_MapEditor.GetViewer().SnapToGrid(snapped_pos);

    auto offset = snapped_pos - m_Start;

    if (volume->GetPreviewPoint())
    {
      volume->SetPreviewPointOffset(offset);
    }
    else
    {
      switch (volume->GetPreviewEdge().Value())
      {
      case 0:
        volume->SetPreviewEdgeOffset(-offset.y);
        break;
      case 1:
        volume->SetPreviewEdgeOffset(-offset.x);
        break;
      case 2:
        volume->SetPreviewEdgeOffset(offset.y);
        break;
      case 3:
        volume->SetPreviewEdgeOffset(offset.x);
        break;
      }
    }
  }
}

void MapEditorToolVolumeEditor::DrawEnd(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  auto volume = m_MapEditor.GetVolumeManager().GetLayerManager(m_LayerIndex);
  if (volume)
  {
    volume->CommitPreview();
  }
}

void MapEditorToolVolumeEditor::DrawCancel()
{
  auto volume = m_MapEditor.GetVolumeManager().GetLayerManager(m_LayerIndex);
  if (volume)
  {
    volume->ClearPreview();
  }
}
