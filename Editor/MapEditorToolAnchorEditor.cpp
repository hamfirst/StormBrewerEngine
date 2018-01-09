
#include "Foundation/Math/Util.h"
#include "Foundation/Math/Intersection.h"

#include "MapEditorToolAnchorEditor.h"
#include "MapEditor.h"


MapEditorToolAnchorEditor::MapEditorToolAnchorEditor(MapEditor & map_editor, int layer_index) :
  MapEditorToolBase(map_editor),
  m_LayerIndex(layer_index)
{

}

void MapEditorToolAnchorEditor::Init()
{
  auto anchor = m_MapEditor.GetAnchorManager().GetLayerManager(m_LayerIndex);
  if (anchor)
  {
    anchor->SetSelected();
  }
}

void MapEditorToolAnchorEditor::Cleanup()
{
  auto anchor = m_MapEditor.GetAnchorManager().GetLayerManager(m_LayerIndex);
  if (anchor)
  {
    anchor->ClearPreview();
    anchor->ClearSelected();
    anchor->ClearHighlighted();
  }

  m_MapEditor.GetViewer().ClearSelectionBox();
}

void MapEditorToolAnchorEditor::Delete()
{
  m_MapEditor.GetMapDef().m_Anchors.RemoveAt(m_LayerIndex);
}

void MapEditorToolAnchorEditor::DrawPreview(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  auto anchor = m_MapEditor.GetAnchorManager().GetLayerManager(m_LayerIndex);
  if (anchor)
  {
    anchor->ClearPreview();
    anchor->ClearHighlighted();

    auto screen_space_pos = (Vector2)m_MapEditor.GetViewer().TransformFromMapSpaceToScreenSpace(pos);

    auto point_pos = anchor->GetPreviewAnchor();
    if (point_pos)
    {
      auto screen_space = (Vector2)m_MapEditor.GetViewer().TransformFromMapSpaceToScreenSpace(point_pos.Value());

      auto dist = ManhattanDist(screen_space, screen_space_pos);
      if (dist < 40)
      {
        anchor->SetHighlighted();
      }
    }
  }
}

bool MapEditorToolAnchorEditor::DrawStart(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  auto anchor = m_MapEditor.GetAnchorManager().GetLayerManager(m_LayerIndex);
  if (anchor)
  {
    auto snapped_pos = pos;
    m_MapEditor.GetViewer().SnapToGrid(snapped_pos, false);

    if (anchor->IsHighlighted())
    {
      if (alt)
      {
        m_MapEditor.DuplicateAnchorData(m_LayerIndex);
      }
      else
      {
        anchor->SetSelected();
        anchor->ClearHighlighted();

        m_Start = snapped_pos;
      }

      return true;
    }
  }

  return false;
}

void MapEditorToolAnchorEditor::DrawMove(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  auto anchor = m_MapEditor.GetAnchorManager().GetLayerManager(m_LayerIndex);
  if (anchor)
  {
    if (anchor->IsSelected())
    {
      auto snapped_pos = pos;
      m_MapEditor.GetViewer().SnapToGrid(snapped_pos, false);

      auto offset = snapped_pos - m_Start;
      anchor->SetPreviewOffset(offset);
    }
  }
}

void MapEditorToolAnchorEditor::DrawEnd(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  auto anchor = m_MapEditor.GetAnchorManager().GetLayerManager(m_LayerIndex);
  if (anchor)
  {
    anchor->CommitPreview();
    DrawPreview(pos, alt, shift, ctrl);
  }
}

void MapEditorToolAnchorEditor::DrawCancel()
{
  auto anchor = m_MapEditor.GetAnchorManager().GetLayerManager(m_LayerIndex);
  if (anchor)
  {
    anchor->ClearPreview();
    anchor->ClearSelected();
  }
}
