
#include "MapEditorToolVolumeCreate.h"
#include "MapEditor.h"


MapEditorToolVolumeCreate::MapEditorToolVolumeCreate(MapEditor & map_editor) :
  MapEditorToolBase(map_editor)
{

}

void MapEditorToolVolumeCreate::Init()
{

}

void MapEditorToolVolumeCreate::Cleanup()
{
  m_MapEditor.GetViewer().ClearSelectionBox();
}

void MapEditorToolVolumeCreate::RightClick()
{

}

void MapEditorToolVolumeCreate::DrawPreview(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{

}

bool MapEditorToolVolumeCreate::DrawStart(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  auto snapped_pos = pos;
  m_MapEditor.GetViewer().SnapToGrid(snapped_pos);

  m_Start = snapped_pos;

  DrawMove(pos, alt, shift, ctrl);
  return true;
}

void MapEditorToolVolumeCreate::DrawMove(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  auto snapped_pos = pos;
  m_MapEditor.GetViewer().SnapToGrid(snapped_pos);

  auto selection_box = Box::FromPoints(m_Start, snapped_pos);
  m_MapEditor.GetViewer().SetSelectionBox(selection_box);
}

void MapEditorToolVolumeCreate::DrawEnd(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  auto snapped_pos = pos;
  m_MapEditor.GetViewer().SnapToGrid(snapped_pos);
  m_MapEditor.GetViewer().ClearSelectionBox();
  m_MapEditor.CreateNewVolume(Box::FromPoints(m_Start, snapped_pos));
}

void MapEditorToolVolumeCreate::DrawCancel()
{
  m_MapEditor.GetViewer().ClearSelectionBox();
}
