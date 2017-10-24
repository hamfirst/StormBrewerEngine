
#include "MapEditorToolBase.h"
#include "MapEditor.h"


MapEditorToolBase::MapEditorToolBase(MapEditor & map_editor) :
  m_MapEditor(map_editor)
{

}

void MapEditorToolBase::Init()
{

}

void MapEditorToolBase::Cleanup()
{

}


void MapEditorToolBase::DrawPreview(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{

}

void MapEditorToolBase::RightClick()
{

}

void MapEditorToolBase::Delete()
{

}

void MapEditorToolBase::Copy()
{

}

void MapEditorToolBase::Cut()
{

}

void MapEditorToolBase::Paste(const Vector2 & pos)
{

}

bool MapEditorToolBase::DrawStart(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  return true;
}

void MapEditorToolBase::DrawMove(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{

}

void MapEditorToolBase::DrawEnd(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{

}

void MapEditorToolBase::DrawCancel()
{

}

void MapEditorToolBase::Snap(Vector2 & pos)
{
  m_MapEditor.GetViewer().SnapToGrid(pos);
}

