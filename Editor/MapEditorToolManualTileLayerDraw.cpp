
#include "MapEditorToolManualTileLayerDraw.h"
#include "MapEditorToolManualTileLayerSelect.h"
#include "MapEditor.h"

MapEditorToolManualTileLayerDraw::MapEditorToolManualTileLayerDraw(MapEditor & map_editor, int layer_index, bool animation, uint64_t frame_id) :
  MapEditorToolBase(map_editor),
  m_LayerIndex(layer_index),
  m_Animation(animation),
  m_FrameId(frame_id)
{

}

void MapEditorToolManualTileLayerDraw::Init()
{
  m_MapEditor.GetSelector().GetTileSelector()->SetSelectedTile(kInvalidFrameId);
}

void MapEditorToolManualTileLayerDraw::Cleanup()
{
  auto layer = m_MapEditor.GetManualTileManager().GetLayerManager(m_LayerIndex);
  if (layer)
  {
    layer->ClearPreviewTiles();
  }
}

void MapEditorToolManualTileLayerDraw::RightClick()
{
  m_MapEditor.GetViewer().SetTool(MapEditorTool<MapEditorToolManualTileLayerSelect>{}, m_LayerIndex);
}

void MapEditorToolManualTileLayerDraw::DrawPreview(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  auto layer = m_MapEditor.GetManualTileManager().GetLayerManager(m_LayerIndex);
  if (layer == nullptr)
  {
    m_LastPreview.Clear();
    return;
  }

  if (alt)
  {
    m_LastPreview.Clear();
    layer->ClearPreviewTiles();
    return;
  }

  auto snapped_pos = pos;
  m_MapEditor.GetViewer().SnapToGrid(snapped_pos);

  if (m_LastPreview && m_LastPreview.Value() == snapped_pos)
  {
    return;
  }

  auto preview_tile = GetPreviewTile(snapped_pos);
  if (preview_tile)
  {
    std::vector<MapTile> map_tile_list;
    map_tile_list.push_back(preview_tile.Value());

    layer->SetPreviewTiles(map_tile_list);
    layer->SetPreviewAnimations({});
  }

  auto preview_anim = GetPreviewAnimation(snapped_pos);
  if (preview_anim)
  {
    std::vector<MapAnimatedTile> map_tile_list;
    map_tile_list.push_back(preview_anim.Value());

    layer->SetPreviewTiles({});
    layer->SetPreviewAnimations(map_tile_list);
  }

  m_LastPreview = snapped_pos;
}

bool MapEditorToolManualTileLayerDraw::DrawStart(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  if (alt)
  {
    auto layer = m_MapEditor.GetManualTileManager().GetLayerManager(m_LayerIndex);
    if (layer)
    {
      auto tile = layer->FindTile(pos);
      if (tile)
      {       
        auto frame_id = m_MapEditor.GetViewer().GetFrameIdForMapTile(tile.Value());
        m_MapEditor.SelectManualTile(m_LayerIndex, frame_id);
      }

      layer->ClearPreviewTiles();
    }

    return false;
  }

  auto snapped_pos = pos;
  m_MapEditor.GetViewer().SnapToGrid(snapped_pos);

  m_DrawStart = snapped_pos;
  m_LastDraw = snapped_pos;
  m_DrawPositions.clear();
  m_DrawTiles.clear();
  m_DrawAnims.clear();

  DrawMove(pos, alt, shift, ctrl);
  return true;
}

void MapEditorToolManualTileLayerDraw::DrawMove(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  auto snapped_pos = pos;
  m_MapEditor.GetViewer().SnapToGrid(snapped_pos);

  if (vfind(m_DrawPositions, snapped_pos))
  {
    return;
  }

  m_DrawPositions.push_back(snapped_pos);

  auto preview_tile = GetPreviewTile(snapped_pos);
  if (preview_tile)
  {
    m_DrawTiles.push_back(preview_tile.Value());

    auto layer = m_MapEditor.GetManualTileManager().GetLayerManager(m_LayerIndex);
    if (layer)
    {
      layer->SetPreviewTiles(m_DrawTiles);
    }
  }

  auto preview_anim = GetPreviewAnimation(snapped_pos);
  if (preview_anim)
  {
    m_DrawAnims.push_back(preview_anim.Value());

    auto layer = m_MapEditor.GetManualTileManager().GetLayerManager(m_LayerIndex);
    if (layer)
    {
      layer->SetPreviewAnimations(m_DrawAnims);
    }
  }
}

void MapEditorToolManualTileLayerDraw::DrawEnd(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  auto layer = m_MapEditor.GetManualTileManager().GetLayerManager(m_LayerIndex);
  if (layer)
  {
    layer->CommitPreviewTiles();
    layer->CommitPreviewAnimations();
  }
}

void MapEditorToolManualTileLayerDraw::DrawCancel()
{
  m_DrawStart.Clear();

  auto layer = m_MapEditor.GetManualTileManager().GetLayerManager(m_LayerIndex);
  if (layer)
  {
    layer->ClearPreviewTiles();
  }
}

Optional<MapTile> MapEditorToolManualTileLayerDraw::GetPreviewTile(const Vector2 & pos)
{
  if (m_Animation == false)
  {
    MapTile preview_tile;
    preview_tile.x = pos.x;
    preview_tile.y = pos.y;
    m_MapEditor.GetViewer().SetTileFrameInfo(preview_tile, m_FrameId);
    return preview_tile;
  }

  return {};
}

Optional<MapAnimatedTile> MapEditorToolManualTileLayerDraw::GetPreviewAnimation(const Vector2 & pos)
{
  if (m_Animation)
  {
    MapAnimatedTile preview_tile;
    preview_tile.x = pos.x;
    preview_tile.y = pos.y;
    m_MapEditor.GetViewer().SetAnimFrameInfo(preview_tile, m_FrameId);
    return preview_tile;
  }

  return {};
}
