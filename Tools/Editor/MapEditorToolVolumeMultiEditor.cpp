
#include "Foundation/Math/Util.h"
#include "Foundation/Math/Intersection.h"

#include "MapEditorToolVolumeMultiEditor.h"
#include "MapEditor.h"


MapEditorToolVolumeMultiEditor::MapEditorToolVolumeMultiEditor(MapEditor & map_editor) :
  MapEditorToolBase(map_editor)
{

}

void MapEditorToolVolumeMultiEditor::Init()
{

}

void MapEditorToolVolumeMultiEditor::Cleanup()
{
  auto visitor = [&](auto volume_index, auto & volume)
  {
    volume->ClearPreview();
  };

  m_MapEditor.GetVolumeManager().VisitLayers(visitor);
}

void MapEditorToolVolumeMultiEditor::DrawPreview(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  int best_index = -1;
  float best_dist = 40;
  MapEditorVolume * best_volume = nullptr;

  auto screen_space_pos = (Vector2)m_MapEditor.GetViewer().TransformFromMapSpaceToScreenSpace(pos);

  auto visitor = [&](auto volume_index, auto & volume)
  {
    volume->ClearPreview();
    auto box = volume->GetPreviewBox();

    if (box)
    {
      for (int point = 0; point < 4; point++)
      {
        auto point_pos = Box::GetPoint(box.Value(), point);
        auto screen_space = (Vector2)m_MapEditor.GetViewer().TransformFromMapSpaceToScreenSpace(point_pos);

        auto dist = ManhattanDist(screen_space, screen_space_pos);
        if (dist < best_dist)
        {
          best_dist = dist;
          best_index = point;
          best_volume = volume.get();
          break;
        }
      }
    }
  };

  m_MapEditor.GetVolumeManager().VisitLayers(visitor);

  if (best_volume)
  {
    best_volume->SetPreviewPoint(best_index);
  }
  else
  {
    auto visitor = [&](auto volume_index, auto & volume)
    {
      auto box = volume->GetPreviewBox();
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
          best_volume = volume.get();
          break;
        }
      }
    };

    m_MapEditor.GetVolumeManager().VisitLayers(visitor);

    if (best_volume)
    {
      best_volume->SetPreviewEdge(best_index);
    }
  }
}

bool MapEditorToolVolumeMultiEditor::DrawStart(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  int num_selected = 0;
  int selected_index = 0;

  m_SelectElem = -1;

  auto visitor = [&](auto volume_index, auto & volume)
  {
    if (volume->GetPreviewPoint() || volume->GetPreviewEdge())
    {
      num_selected++;
      selected_index = (int)volume_index;
    }
  };

  m_MapEditor.GetVolumeManager().VisitLayers(visitor);

  if (num_selected > 0)
  {
    if (num_selected == 1)
    {
      m_SelectElem = selected_index;
    }

    auto snapped_pos = pos;
    m_MapEditor.GetViewer().SnapToGrid(snapped_pos);

    m_Start = snapped_pos;
    return true;
  }

  return false;
}

void MapEditorToolVolumeMultiEditor::DrawMove(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  auto snapped_pos = pos;
  m_MapEditor.GetViewer().SnapToGrid(snapped_pos);

  auto visitor = [&](auto volume_index, auto & volume)
  {
    auto offset = snapped_pos - m_Start;
    if (offset.x != 0 || offset.y != 0)
    {
      m_SelectElem = -1;
    }

    if (volume->GetPreviewPoint())
    {
      volume->SetPreviewPointOffset(offset);
    }
    else if (volume->GetPreviewEdge())
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
  };

  m_MapEditor.GetVolumeManager().VisitLayers(visitor);
}

void MapEditorToolVolumeMultiEditor::DrawEnd(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  if (m_SelectElem != -1)
  {
    MapEditorLayerSelection layer_selection = { MapEditorLayerItemType::kVolume, (std::size_t)m_SelectElem };
    m_MapEditor.ChangeLayerSelection(layer_selection, false);
  }
  else
  {
    auto visitor = [&](auto volume_index, auto & volume)
    {
      volume->CommitPreview();
    };

    m_MapEditor.GetVolumeManager().VisitLayers(visitor);
  }
}

void MapEditorToolVolumeMultiEditor::DrawCancel()
{
  auto visitor = [&](auto volume_index, auto & volume)
  {
    volume->ClearPreview();
  };

  m_MapEditor.GetVolumeManager().VisitLayers(visitor);
}
