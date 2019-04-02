
#include "MapEditorToolParallaxObjectLayerDraw.h"
#include "MapEditorToolParallaxObjectLayerSelect.h"
#include "MapEditor.h"

MapEditorToolParallaxObjectLayerDraw::MapEditorToolParallaxObjectLayerDraw(MapEditor & map_editor, int layer_index) :
  MapEditorToolBase(map_editor),
  m_LayerIndex(layer_index)
{

}

void MapEditorToolParallaxObjectLayerDraw::Init()
{
  auto layer = m_MapEditor.GetParallaxManager().GetLayerManager(m_LayerIndex);
  if (layer)
  {
    layer->SetPreviewParallaxObjectPosition({});
  }
}

void MapEditorToolParallaxObjectLayerDraw::Cleanup()
{
  auto layer = m_MapEditor.GetParallaxManager().GetLayerManager(m_LayerIndex);
  if (layer)
  {
    layer->ClearPreviewParallaxObject();
  }
}

void MapEditorToolParallaxObjectLayerDraw::RightClick()
{
  m_MapEditor.GetViewer().SetTool(MapEditorTool<MapEditorToolParallaxObjectLayerSelect>{}, m_LayerIndex);
}

void MapEditorToolParallaxObjectLayerDraw::DrawPreview(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  auto layer = m_MapEditor.GetParallaxManager().GetLayerManager(m_LayerIndex);
  if (layer == nullptr)
  {
    return;
  }

  auto snapped_pos = pos;
  m_MapEditor.GetViewer().SnapToGrid(snapped_pos);
  layer->SetPreviewParallaxObjectPosition(snapped_pos);
}

bool MapEditorToolParallaxObjectLayerDraw::DrawStart(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  auto layer = m_MapEditor.GetParallaxManager().GetLayerManager(m_LayerIndex);
  if (layer == nullptr)
  {
    return false;
  }

  layer->CommitPreviewParallaxObject();
  return true;
}
