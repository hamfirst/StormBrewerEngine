
#include "MapEditorToolServerObjectLayerDraw.h"
#include "MapEditorToolServerObjectLayerSelect.h"
#include "MapEditor.h"

MapEditorToolServerObjectLayerDraw::MapEditorToolServerObjectLayerDraw(MapEditor & map_editor, int layer_index, czstr entity_file) :
  MapEditorToolBase(map_editor),
  m_LayerIndex(layer_index),
  m_ServerObjectFile(entity_file)
{

}

void MapEditorToolServerObjectLayerDraw::Init()
{
  auto layer = m_MapEditor.GetServerObjectManager().GetLayerManager(m_LayerIndex);
  if (layer)
  {
    layer->SetPreviewServerObject(m_ServerObjectFile.data());
  }
}

void MapEditorToolServerObjectLayerDraw::Cleanup()
{
  auto layer = m_MapEditor.GetServerObjectManager().GetLayerManager(m_LayerIndex);
  if (layer)
  {
    layer->ClearPreviewServerObject();
  }
}

void MapEditorToolServerObjectLayerDraw::RightClick()
{
  m_MapEditor.GetViewer().SetTool(MapEditorTool<MapEditorToolServerObjectLayerSelect>{}, m_LayerIndex);
}

void MapEditorToolServerObjectLayerDraw::DrawPreview(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  auto layer = m_MapEditor.GetServerObjectManager().GetLayerManager(m_LayerIndex);
  if (layer == nullptr)
  {
    return;
  }

  auto snapped_pos = pos;
  m_MapEditor.GetViewer().SnapToGrid(snapped_pos);
  layer->SetPreviewServerObjectPosition(snapped_pos);
}

bool MapEditorToolServerObjectLayerDraw::DrawStart(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  auto layer = m_MapEditor.GetServerObjectManager().GetLayerManager(m_LayerIndex);
  if (layer == nullptr)
  {
    return false;
  }

  layer->CommitPreviewServerObject();
  return true;
}
