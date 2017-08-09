
#include "Foundation/Math/Util.h"
#include "Foundation/Math/Intersection.h"

#include "MapEditorToolPathMultiEditor.h"
#include "MapEditor.h"


MapEditorToolPathMultiEditor::MapEditorToolPathMultiEditor(MapEditor & map_editor) :
  MapEditorToolBase(map_editor)
{

}

void MapEditorToolPathMultiEditor::Init()
{

}

void MapEditorToolPathMultiEditor::Cleanup()
{
  auto visitor = [&](auto path_index, auto & path)
  {
    path->ClearPreview();
    path->ClearSelectedPoints();
  };

  m_MapEditor.GetPathManager().VisitLayers(visitor);
  m_MapEditor.GetViewer().ClearSelectionBox();
}

void MapEditorToolPathMultiEditor::DrawPreview(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  int best_index = -1;
  float best_dist = 40;
  NullOptPtr<MapEditorPath> best_path = nullptr;

  auto screen_space_pos = (Vector2)m_MapEditor.GetViewer().TransformFromMapSpaceToScreenSpace(pos);

  auto visitor = [&](auto path_index, auto & path)
  {
    path->ClearPreview();

    auto points = path->GetPreviewPath();

    if (points && points->size() > 0)
    {
      for (int point = 0; point < points->size(); point++)
      {
        auto point_pos = points->at(point);
        auto screen_space = (Vector2)m_MapEditor.GetViewer().TransformFromMapSpaceToScreenSpace(point_pos);

        auto dist = ManhattanDist(screen_space, screen_space_pos);
        if (dist < best_dist)
        {
          best_dist = dist;
          best_index = point;
          best_path = path.get();
        }
      }
    }
  };

  m_MapEditor.GetPathManager().VisitLayers(visitor);

  if (best_path)
  {
    best_path->SetPreviewPoint(best_index);
  }
  else
  {
    auto visitor = [&](auto path_index, auto & path)
    {
      auto points = path->GetPreviewPath();

      if (points && points->size() > 0)
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
            best_path = path.get();
            break;
          }
        }
      }
    };

    m_MapEditor.GetPathManager().VisitLayers(visitor);

    if (best_path)
    {
      best_path->SetPreviewEdge(best_index);
    }
  }
}

bool MapEditorToolPathMultiEditor::DrawStart(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  int num_selected = 0;
  int selected_index = 0;
  m_SelectMode = false;
  m_SelectElem = -1;

  auto visitor = [&](auto path_index, auto & path)
  {
    if (path->GetPreviewPoint() || path->GetPreviewEdge())
    {
      num_selected++;
      selected_index = (int)path_index;
    }
  };

  m_MapEditor.GetPathManager().VisitLayers(visitor);

  if (num_selected > 0)
  {
    if (num_selected == 1)
    {
      m_SelectElem = selected_index;
    }

    auto snapped_pos = pos;
    m_MapEditor.GetViewer().SnapToGrid(snapped_pos, false);

    m_Start = snapped_pos;
  }
  else
  {
    auto visitor = [&](auto path_index, auto & path)
    {
      path->ClearSelectedPoints();
    };

    m_MapEditor.GetPathManager().VisitLayers(visitor);


    m_SelectMode = true;
    m_Start = pos;
  }

  return true;
}

void MapEditorToolPathMultiEditor::DrawMove(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  auto visitor = [&](auto path_index, auto & path)
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
      if (offset.x != 0 || offset.y != 0)
      {
        m_SelectElem = -1;
      }

      path->SetPreviewOffset(offset);
    }
  };

  m_MapEditor.GetPathManager().VisitLayers(visitor);
}

void MapEditorToolPathMultiEditor::DrawEnd(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  m_MapEditor.GetViewer().ClearSelectionBox();

  if (m_SelectElem != -1)
  {
    MapEditorLayerSelection layer_selection = { MapEditorLayerItemType::kPath, (std::size_t)m_SelectElem };
    m_MapEditor.ChangeLayerSelection(layer_selection, false);
  }
  else if (m_SelectMode == false)
  {
    m_MapEditor.BeginTransaction();

    auto visitor = [&](auto path_index, auto & path)
    {
      path->CommitPreview();
    };

    m_MapEditor.GetPathManager().VisitLayers(visitor);
    m_MapEditor.CommitChanges();
  }
}

void MapEditorToolPathMultiEditor::DrawCancel()
{
  auto visitor = [&](auto path_index, auto & path)
  {
    path->ClearPreview();
  };

  m_MapEditor.GetPathManager().VisitLayers(visitor);
  m_MapEditor.GetViewer().ClearSelectionBox();
}
