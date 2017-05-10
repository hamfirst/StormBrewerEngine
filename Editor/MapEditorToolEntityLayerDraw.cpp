
#include "MapEditorToolEntityLayerDraw.h"
#include "MapEditorToolEntityLayerSelect.h"
#include "MapEditor.h"

MapEditorToolEntityLayerDraw::MapEditorToolEntityLayerDraw(MapEditor & map_editor, int layer_index, czstr entity_file) :
  MapEditorToolBase(map_editor),
  m_LayerIndex(layer_index),
  m_EntityFile(entity_file)
{

}

void MapEditorToolEntityLayerDraw::Init()
{
  auto layer = m_MapEditor.GetEntityManager().GetLayerManager(m_LayerIndex);
  if (layer)
  {
    layer->SetPreviewEntity(m_EntityFile.data());
  }
}

void MapEditorToolEntityLayerDraw::Cleanup()
{
  auto layer = m_MapEditor.GetEntityManager().GetLayerManager(m_LayerIndex);
  if (layer)
  {
    layer->ClearPreviewEntity();
  }
}

void MapEditorToolEntityLayerDraw::RightClick()
{
  m_MapEditor.GetViewer().SetTool(MapEditorTool<MapEditorToolEntityLayerSelect>{}, m_LayerIndex);
}

void MapEditorToolEntityLayerDraw::DrawPreview(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  auto layer = m_MapEditor.GetEntityManager().GetLayerManager(m_LayerIndex);
  if (layer == nullptr)
  {
    return;
  }

  auto snapped_pos = pos;
  m_MapEditor.GetViewer().SnapToGrid(snapped_pos);
  layer->SetPreviewEntityPosition(snapped_pos);
}

bool MapEditorToolEntityLayerDraw::DrawStart(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  auto layer = m_MapEditor.GetEntityManager().GetLayerManager(m_LayerIndex);
  if (layer == nullptr)
  {
    return false;
  }

  layer->CommitPreviewEntity();
  return true;
}
