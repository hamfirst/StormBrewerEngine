
#include "MapEditorToolManualTileLayerPreview.h"
#include "MapEditorToolManualTileLayerSelect.h"
#include "MapEditor.h"

MapEditorToolManualTileLayerPreview::MapEditorToolManualTileLayerPreview(MapEditor & map_editor, int layer_index) :
  MapEditorToolBase(map_editor),
  m_LayerIndex(layer_index)
{

}

void MapEditorToolManualTileLayerPreview::Init()
{
  m_MapEditor.GetSelector().GetTileSelector()->SetSelectedTile(kInvalidFrameId);
}

void MapEditorToolManualTileLayerPreview::Cleanup()
{

}

void MapEditorToolManualTileLayerPreview::Delete()
{
  auto layer = m_MapEditor.GetManualTileManager().GetLayerManager(m_LayerIndex);
  if (layer != nullptr)
  {
    layer->ClearPreviewTiles();
  }

  m_MapEditor.GetViewer().SetTool(MapEditorTool<MapEditorToolManualTileLayerSelect>{}, m_LayerIndex);
}

bool MapEditorToolManualTileLayerPreview::DrawStart(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  auto layer = m_MapEditor.GetManualTileManager().GetLayerManager(m_LayerIndex);
  if (layer != nullptr)
  {
    if (layer->IsOnPreviewTile(pos))
    {
      m_Start = pos;
      m_MapEditor.GetViewer().SnapToGrid(m_Start);
      return true;
    }

    layer->CommitPreviewAnimations();
    layer->CommitPreviewTiles();
    layer->ClearPreviewTiles();
    m_MapEditor.GetViewer().SetTool(MapEditorTool<MapEditorToolManualTileLayerSelect>{}, m_LayerIndex);
  }

  return false;
}

void MapEditorToolManualTileLayerPreview::DrawMove(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  auto layer = m_MapEditor.GetManualTileManager().GetLayerManager(m_LayerIndex);
  if (layer != nullptr)
  {
    auto snapped_pos = pos;
    m_MapEditor.GetViewer().SnapToGrid(snapped_pos);

    auto diff = snapped_pos - m_Start;
    layer->OffsetPreview(diff);

    m_Start = snapped_pos;
  }
}

void MapEditorToolManualTileLayerPreview::DrawEnd(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{

}

void MapEditorToolManualTileLayerPreview::DrawCancel()
{
  auto layer = m_MapEditor.GetManualTileManager().GetLayerManager(m_LayerIndex);
  if (layer)
  {
    layer->ClearPreviewTiles();
  }

  m_MapEditor.GetViewer().SetTool(MapEditorTool<MapEditorToolManualTileLayerSelect>{}, m_LayerIndex);
}
