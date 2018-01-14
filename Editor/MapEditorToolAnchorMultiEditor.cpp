
#include "Foundation/Math/Util.h"
#include "Foundation/Math/Intersection.h"

#include "MapEditorToolAnchorMultiEditor.h"
#include "MapEditor.h"


MapEditorToolAnchorMultiEditor::MapEditorToolAnchorMultiEditor(MapEditor & map_editor, int layer_index) :
  MapEditorToolBase(map_editor)
{
  if (layer_index != -1)
  {
    auto anchor = m_MapEditor.GetAnchorManager().GetLayerManager(layer_index);
    anchor->SetSelected();
  }
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

void MapEditorToolAnchorMultiEditor::Delete()
{
  std::vector<std::size_t> dead_indices;
  auto visitor = [&](auto anchor_index, auto & anchor)
  {
    if (anchor->IsHighlighted() || anchor->IsSelected())
    {
      dead_indices.push_back(anchor_index);
    }
  };

  m_MapEditor.GetAnchorManager().VisitLayers(visitor);
  m_MapEditor.BeginTransaction();

  for (auto & elem : dead_indices)
  {
    m_MapEditor.GetMapDef().m_Anchors.RemoveAt(elem);
  }

  m_MapEditor.CommitChanges();
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
  int selected_index = -1;
  int highlighted_index = -1;
  bool is_highlight_selected = false;

  m_SelectElem = -1;
  m_SelectMode = false;

  auto visitor = [&](auto anchor_index, auto & anchor)
  {
    if(anchor->IsHighlighted())
    {
      if (anchor->IsSelected())
      {
        is_highlight_selected = true;
      }

      highlighted_index = anchor_index;
    }

    if (anchor->IsSelected())
    {
      num_selected++;
      selected_index = anchor_index;
    }
  };

  m_MapEditor.GetAnchorManager().VisitLayers(visitor);

  if (alt)
  {
    if (highlighted_index != -1)
    {
      m_MapEditor.DuplicateAnchorData(highlighted_index);
    }

    return false;
  }

  if (shift)
  {
    if (highlighted_index != -1)
    {
      m_MapEditor.GetAnchorManager().GetLayerManager(highlighted_index)->SetSelected();
    }

    return false;
  }

  if (is_highlight_selected == false && highlighted_index != -1)
  {
    auto visitor = [&](auto anchor_index, auto & anchor)
    {
      anchor->ClearSelected();
    };

    m_MapEditor.GetAnchorManager().VisitLayers(visitor);

    m_MapEditor.GetAnchorManager().GetLayerManager(highlighted_index)->SetSelected();
    num_selected = 1;
    is_highlight_selected = true;

    m_SelectElem = highlighted_index;
  }

  if (num_selected > 0 && is_highlight_selected)
  {
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
    m_SelectElem = highlighted_index;
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

      if (m_SelectElem != -1)
      {
        auto anchor = m_MapEditor.GetAnchorManager().GetLayerManager(m_SelectElem);
        if (anchor)
        {
          anchor->SetSelected();
        }
      }
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

  if (m_SelectMode)
  {
    if (m_SelectElem != -1)
    {
      auto anchor = m_MapEditor.GetAnchorManager().GetLayerManager(m_SelectElem);
      if (anchor)
      {
        anchor->SetSelected();
      }
    }
  }
  else
  {
    m_MapEditor.BeginTransaction();

    auto visitor = [&](auto anchor_index, auto & anchor)
    {
      anchor->CommitPreview();
    };

    m_MapEditor.GetAnchorManager().VisitLayers(visitor);
    m_MapEditor.CommitChanges();
  }

  int num_selected = 0;
  int selected_index = -1;

  auto visitor = [&](auto anchor_index, auto & anchor)
  {
    if (anchor->IsSelected())
    {
      num_selected++;
      selected_index = anchor_index;
    }
  };

  m_MapEditor.GetAnchorManager().VisitLayers(visitor);
  if (num_selected == 1)
  {
    MapEditorLayerSelection layer_selection = { MapEditorLayerItemType::kAnchor, (std::size_t)selected_index };
    m_MapEditor.ChangeLayerSelection(layer_selection, false);
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
