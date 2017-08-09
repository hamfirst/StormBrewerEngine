
#include "MapEditorToolAnchorCreate.h"
#include "MapEditor.h"


MapEditorToolAnchorCreate::MapEditorToolAnchorCreate(MapEditor & map_editor) :
  MapEditorToolBase(map_editor)
{

}

void MapEditorToolAnchorCreate::Init()
{

}

void MapEditorToolAnchorCreate::Cleanup()
{
  m_MapEditor.GetViewer().ClearPreviewPoint();
}

void MapEditorToolAnchorCreate::RightClick()
{

}

void MapEditorToolAnchorCreate::DrawPreview(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{

}

bool MapEditorToolAnchorCreate::DrawStart(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  DrawMove(pos, alt, shift, ctrl);
  return true;
}

void MapEditorToolAnchorCreate::DrawMove(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  auto snapped_pos = pos;
  m_MapEditor.GetViewer().SnapToGrid(snapped_pos, false);
  m_MapEditor.GetViewer().SetPreviewPoint(snapped_pos);
}

void MapEditorToolAnchorCreate::DrawEnd(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  auto snapped_pos = pos;
  m_MapEditor.GetViewer().SnapToGrid(snapped_pos, false);
  m_MapEditor.GetViewer().ClearPreviewPoint();
  m_MapEditor.CreateNewAnchor(snapped_pos);
}

void MapEditorToolAnchorCreate::DrawCancel()
{
  m_MapEditor.GetViewer().ClearPreviewPoint();
}
