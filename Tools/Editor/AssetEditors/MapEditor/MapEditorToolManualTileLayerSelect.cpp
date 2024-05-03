
#include "MapEditorToolManualTileLayerSelect.h"
#include "MapEditorToolManualTileLayerDraw.h"
#include "MapEditorToolManualTileLayerPreview.h"
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
    layer->DeleteSelection();
  }
}

void MapEditorToolManualTileLayerSelect::Copy()
{
  auto layer = m_MapEditor.GetManualTileManager().GetLayerManager(m_LayerIndex);
  if (layer != nullptr)
  {
    layer->CopySelection();
  }
}

void MapEditorToolManualTileLayerSelect::Cut()
{
  auto layer = m_MapEditor.GetManualTileManager().GetLayerManager(m_LayerIndex);
  if (layer != nullptr)
  {
    layer->CopySelection();
    layer->DeleteSelection();
  }
}

void MapEditorToolManualTileLayerSelect::Paste(const Vector2 & pos)
{
  auto layer = m_MapEditor.GetManualTileManager().GetLayerManager(m_LayerIndex);
  if (layer != nullptr)
  {
    layer->ClearSelection();
    layer->PasteSelection(pos);

    m_MapEditor.GetViewer().SetTool(MapEditorTool<MapEditorToolManualTileLayerPreview>{}, m_LayerIndex);
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
    if (layer->IsOnSelectedTile(pos))
    {
      layer->CommitPreviewTiles();
      layer->CommitPreviewAnimations();

      layer->DuplicateSelectedToPreview();
      layer->ClearSelection();
      m_MapEditor.GetViewer().SetToolMidDraw(MapEditorTool<MapEditorToolManualTileLayerPreview>{}, m_LayerIndex);
    }
    else
    {
      auto anim = layer->FindAnim(pos);
      if (anim)
      {
        auto frame_id = m_MapEditor.GetViewer().GetFrameIdForMapAnimation(anim.Value());
        m_MapEditor.SelectManualAnimation(m_LayerIndex, frame_id);
      }
      else
      {
        auto tile = layer->FindTile(pos);
        if (tile)
        {
          auto frame_id = m_MapEditor.GetViewer().GetFrameIdForMapTile(tile.Value());
          m_MapEditor.SelectManualTile(m_LayerIndex, frame_id);
        }
      }
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
      layer->SetSelectionOffset(snapped_pos - m_Start);
    }
  }
  else
  {
    auto selection_box = Box::FromPoints(m_Start, pos);

    auto layer = m_MapEditor.GetManualTileManager().GetLayerManager(m_LayerIndex);
    if (layer != nullptr)
    {
      layer->SelectTiles(selection_box);
      layer->SelectAnimations(selection_box);
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
      layer->CommitSelectedOffset();
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
      layer->SetSelectionOffset(Vector2(0, 0));
    }
    else
    {
      layer->ClearSelection();
    }
  }

  m_MapEditor.GetViewer().ClearSelectionBox();
}
