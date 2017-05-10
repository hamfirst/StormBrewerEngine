
#include "MapEditorToolManualTileLayerSelect.h"
#include "MapEditorToolManualTileLayerDraw.h"
#include "MapEditor.h"

MapEditorToolManualTileLayerSelect::MapEditorToolManualTileLayerSelect(MapEditor & map_editor, int layer_index) :
  MapEditorToolBase(map_editor),
  m_LayerIndex(layer_index)
{

}

void MapEditorToolManualTileLayerSelect::Init()
{
  m_MapEditor.GetSelector().GetTileSelector()->SetSelectedTile(kInvalidFrameId);
}

void MapEditorToolManualTileLayerSelect::Cleanup()
{
  auto layer = m_MapEditor.GetManualTileManager().GetLayerManager(m_LayerIndex);
  if (layer)
  {
    layer->ClearSelection();
  }

  m_MapEditor.GetViewer().ClearSelectionBox();
}

void MapEditorToolManualTileLayerSelect::Delete()
{
  auto layer = m_MapEditor.GetManualTileManager().GetLayerManager(m_LayerIndex);
  if (layer != nullptr)
  {
    layer->DeleteSelectedTiles();
  }
}

bool MapEditorToolManualTileLayerSelect::DrawStart(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  auto layer = m_MapEditor.GetManualTileManager().GetLayerManager(m_LayerIndex);
  if (layer == nullptr)
  {
    return false;
  }

  if (alt)
  {
    auto tile = layer->FindTile(pos);
    if (tile)
    {
      auto frame_id = m_MapEditor.GetViewer().GetFrameIdForMapTile(tile.Value());
      m_MapEditor.SelectManualTile(m_LayerIndex, frame_id);
    }

    return false;
  }

  m_Start = pos;

  if (layer->IsOnSelectedTile(pos))
  {
    m_MoveMode = true;
    m_MapEditor.GetViewer().SnapToGrid(m_Start);
  }
  else
  {
    m_MoveMode = false;
    DrawMove(pos, alt, shift, ctrl);
  }
  return true;
}


void MapEditorToolManualTileLayerSelect::DrawMove(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  if (m_MoveMode)
  {
    auto snapped_pos = pos;
    m_MapEditor.GetViewer().SnapToGrid(snapped_pos);

    auto layer = m_MapEditor.GetManualTileManager().GetLayerManager(m_LayerIndex);
    if (layer != nullptr)
    {
      layer->SetSelectedTileOffset(snapped_pos - m_Start);
    }
  }
  else
  {
    auto selection_box = Box::FromPoints(m_Start, pos);

    auto layer = m_MapEditor.GetManualTileManager().GetLayerManager(m_LayerIndex);
    if (layer != nullptr)
    {
      layer->SelectTiles(selection_box);
    }

    m_MapEditor.GetViewer().SetSelectionBox(selection_box);
  }
}

void MapEditorToolManualTileLayerSelect::DrawEnd(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  if (m_MoveMode)
  {
    auto layer = m_MapEditor.GetManualTileManager().GetLayerManager(m_LayerIndex);
    if (layer != nullptr)
    {
      layer->CommitSelectedTileOffset();
    }
  }
  else
  {
    m_MapEditor.GetViewer().ClearSelectionBox();
  }
}

void MapEditorToolManualTileLayerSelect::DrawCancel()
{
  auto layer = m_MapEditor.GetManualTileManager().GetLayerManager(m_LayerIndex);
  if (layer != nullptr)
  {
    if (m_MoveMode)
    {
      layer->SetSelectedTileOffset(Vector2(0, 0));
    }
    else
    {
      layer->ClearSelection();
    }
  }

  m_MapEditor.GetViewer().ClearSelectionBox();
}
