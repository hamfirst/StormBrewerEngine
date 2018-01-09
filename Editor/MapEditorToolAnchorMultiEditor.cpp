
#include "Foundation/Math/Util.h"
#include "Foundation/Math/Intersection.h"

#include "MapEditorToolAnchorMultiEditor.h"
#include "MapEditor.h"


MapEditorToolAnchorMultiEditor::MapEditorToolAnchorMultiEditor(MapEditor & map_editor) :
  MapEditorToolBase(map_editor)
{

}

void MapEditorToolAnchorMultiEditor::Init()
{

}

void MapEditorToolAnchorMultiEditor::Cleanup()
{
  auto visitor = [&](auto anchor_index, auto & anchor)
  {
    anchor->ClearPreview();
    anchor->ClearSelected();
    anchor->ClearHighlighted();
  };

  m_MapEditor.GetAnchorManager().VisitLayers(visitor);
  m_MapEditor.GetViewer().ClearSelectionBox();
}

void MapEditorToolAnchorMultiEditor::DrawPreview(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  float best_dist = 40;
  NullOptPtr<MapEditorAnchor> best_anchor = nullptr;

  auto screen_space_pos = (Vector2)m_MapEditor.GetViewer().TransformFromMapSpaceToScreenSpace(pos);

  auto visitor = [&](auto anchor_index, auto & anchor)
  {
    anchor->ClearPreview();
    anchor->ClearHighlighted();

    auto point_pos = anchor->GetPreviewAnchor();

    if (point_pos)
    {
      auto screen_space = (Vector2)m_MapEditor.GetViewer().TransformFromMapSpaceToScreenSpace(point_pos.Value());

      auto dist = ManhattanDist(screen_space, screen_space_pos);
      if (dist < best_dist)
      {
        best_dist = dist;
        best_anchor = anchor.get();
      }
    }
  };

  m_MapEditor.GetAnchorManager().VisitLayers(visitor);

  if (best_anchor)
  {
    best_anchor->SetHighlighted();
  }
}

bool MapEditorToolAnchorMultiEditor::DrawStart(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  int num_selected = 0;
  int selected_index = 0;
  bool is_highlighted = false;

  m_SelectElem = -1;
  m_SelectMode = false;

  auto visitor = [&](auto anchor_index, auto & anchor)
  {
    if (anchor->IsHighlighted() || anchor->IsSelected())
    {
      num_selected++;
      selected_index = (int)anchor_index;
    }

    if (anchor->IsHighlighted())
    {
      is_highlighted = true;
    }
  };

  m_MapEditor.GetAnchorManager().VisitLayers(visitor);

  if (is_highlighted)
  {
    if (num_selected == 1)
    {
      if (alt)
      {
        m_MapEditor.DuplicateAnchorData(selected_index);
        return false;
      }
      else
      {
        m_SelectElem = selected_index;
      }
    }

    auto snapped_pos = pos;
    m_MapEditor.GetViewer().SnapToGrid(snapped_pos, false);

    m_Start = snapped_pos;
    m_MapEditor.GetAnchorManager().VisitLayers(visitor);

  }
  else
  {
    auto visitor = [&](auto anchor_index, auto & anchor)
    {
      anchor->ClearSelected();
    };

    m_MapEditor.GetAnchorManager().VisitLayers(visitor);

    m_SelectMode = true;
    m_Start = pos;
  }

  return true;
}

void MapEditorToolAnchorMultiEditor::DrawMove(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  auto visitor = [&](auto anchor_index, auto & anchor)
  {
    if (m_SelectMode)
    {
      auto box = Box::FromPoints(m_Start, pos);
      m_MapEditor.GetViewer().SetSelectionBox(box);

      anchor->Select(box);
    }
    else if(anchor->IsSelected() || anchor->IsHighlighted())
    {
      auto snapped_pos = pos;
      m_MapEditor.GetViewer().SnapToGrid(snapped_pos, false);

      auto offset = snapped_pos - m_Start;

      if (offset.x != 0 || offset.y != 0)
      {
        m_SelectElem = -1;
      }

      anchor->SetPreviewOffset(offset);
    }
  };

  m_MapEditor.GetAnchorManager().VisitLayers(visitor);
}

void MapEditorToolAnchorMultiEditor::DrawEnd(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  m_MapEditor.GetViewer().ClearSelectionBox();

  if (m_SelectElem != -1)
  {
    MapEditorLayerSelection layer_selection = { MapEditorLayerItemType::kAnchor, (std::size_t)m_SelectElem };
    m_MapEditor.ChangeLayerSelection(layer_selection, false);
  }
  else if (m_SelectMode == false)
  {
    m_MapEditor.BeginTransaction();

    auto visitor = [&](auto anchor_index, auto & anchor)
    {
      anchor->CommitPreview();
    };

    m_MapEditor.GetAnchorManager().VisitLayers(visitor);
    m_MapEditor.CommitChanges();
  }
}

void MapEditorToolAnchorMultiEditor::DrawCancel()
{
  auto visitor = [&](auto anchor_index, auto & anchor)
  {
    anchor->ClearPreview();
  };

  m_MapEditor.GetAnchorManager().VisitLayers(visitor);
  m_MapEditor.GetViewer().ClearSelectionBox();
}
