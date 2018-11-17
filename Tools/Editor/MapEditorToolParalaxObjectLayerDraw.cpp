
#include "MapEditorToolParalaxObjectLayerDraw.h"
#include "MapEditorToolParalaxObjectLayerSelect.h"
#include "MapEditor.h"

MapEditorToolParalaxObjectLayerDraw::MapEditorToolParalaxObjectLayerDraw(MapEditor & map_editor, int layer_index) :
  MapEditorToolBase(map_editor),
  m_LayerIndex(layer_index)
{

}

void MapEditorToolParalaxObjectLayerDraw::Init()
{
  auto layer = m_MapEditor.GetParalaxManager().GetLayerManager(m_LayerIndex);
  if (layer)
  {
    layer->SetPreviewParalaxObjectPosition({});
  }
}

void MapEditorToolParalaxObjectLayerDraw::Cleanup()
{
  auto layer = m_MapEditor.GetParalaxManager().GetLayerManager(m_LayerIndex);
  if (layer)
  {
    layer->ClearPreviewParalaxObject();
  }
}

void MapEditorToolParalaxObjectLayerDraw::RightClick()
{
  m_MapEditor.GetViewer().SetTool(MapEditorTool<MapEditorToolParalaxObjectLayerSelect>{}, m_LayerIndex);
}

void MapEditorToolParalaxObjectLayerDraw::DrawPreview(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  auto layer = m_MapEditor.GetParalaxManager().GetLayerManager(m_LayerIndex);
  if (layer == nullptr)
  {
    return;
  }

  auto snapped_pos = pos;
  m_MapEditor.GetViewer().SnapToGrid(snapped_pos);
  layer->SetPreviewParalaxObjectPosition(snapped_pos);
}

bool MapEditorToolParalaxObjectLayerDraw::DrawStart(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  auto layer = m_MapEditor.GetParalaxManager().GetLayerManager(m_LayerIndex);
  if (layer == nullptr)
  {
    return false;
  }

  layer->CommitPreviewParalaxObject();
  return true;
}
