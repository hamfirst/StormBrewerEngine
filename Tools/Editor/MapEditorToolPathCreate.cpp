
#include "MapEditorToolPathCreate.h"
#include "MapEditor.h"


MapEditorToolPathCreate::MapEditorToolPathCreate(MapEditor & map_editor) :
  MapEditorToolBase(map_editor)
{

}

void MapEditorToolPathCreate::Init()
{

}

void MapEditorToolPathCreate::Cleanup()
{
  m_MapEditor.GetViewer().ClearPreviewLine();
}

void MapEditorToolPathCreate::RightClick()
{

}

void MapEditorToolPathCreate::DrawPreview(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{

}

bool MapEditorToolPathCreate::DrawStart(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  auto snapped_pos = pos;
  m_MapEditor.GetViewer().SnapToGrid(snapped_pos, false);

  m_Start = snapped_pos;

  DrawMove(pos, alt, shift, ctrl);
  return true;
}

void MapEditorToolPathCreate::DrawMove(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  auto snapped_pos = pos;
  m_MapEditor.GetViewer().SnapToGrid(snapped_pos, false);
  m_MapEditor.GetViewer().SetPreviewLine(Line{ m_Start, snapped_pos });
}

void MapEditorToolPathCreate::DrawEnd(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  auto snapped_pos = pos;
  m_MapEditor.GetViewer().SnapToGrid(snapped_pos, false);
  m_MapEditor.GetViewer().ClearPreviewLine();
  m_MapEditor.CreateNewPath(Line{ m_Start, snapped_pos });
}

void MapEditorToolPathCreate::DrawCancel()
{
  m_MapEditor.GetViewer().ClearPreviewLine();
}
