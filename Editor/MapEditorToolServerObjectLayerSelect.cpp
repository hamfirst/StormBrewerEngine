
#include "MapEditorToolServerObjectLayerSelect.h"
#include "MapEditorToolServerObjectLayerDraw.h"
#include "MapEditor.h"

MapEditorToolServerObjectLayerSelect::MapEditorToolServerObjectLayerSelect(MapEditor & map_editor, int layer_index) :
  MapEditorToolBase(map_editor),
  m_LayerIndex(layer_index)
{

}

void MapEditorToolServerObjectLayerSelect::Init()
{
  m_MapEditor.GetSelector().GetServerObjectSelector()->Clear();
}

void MapEditorToolServerObjectLayerSelect::Cleanup()
{
  auto layer = m_MapEditor.GetServerObjectManager().GetLayerManager(m_LayerIndex);
  if (layer)
  {
    layer->ClearSelection();
  }

  m_MapEditor.GetViewer().ClearSelectionBox();
}

void MapEditorToolServerObjectLayerSelect::Delete()
{
  auto layer = m_MapEditor.GetServerObjectManager().GetLayerManager(m_LayerIndex);
  if (layer != nullptr)
  {
    layer->DeleteSelectedServerObjects();
  }
}

bool MapEditorToolServerObjectLayerSelect::DrawStart(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  auto layer = m_MapEditor.GetServerObjectManager().GetLayerManager(m_LayerIndex);
  if (layer == nullptr)
  {
    return false;
  }

  if (alt)
  {
    auto server_object = layer->FindServerObject(pos);
    if (server_object)
    {
      m_MapEditor.SetSelectedServerObject(m_LayerIndex, server_object->data());
    }

    return false;
  }

  m_Start = pos;
  if (layer->IsOnSelectedServerObject(pos))
  {
    m_MapEditor.GetViewer().SnapToGrid(m_Start);
    m_MoveMode = true;
  }
  else
  {
    m_MoveMode = false;
    DrawMove(pos, alt, shift, ctrl);
  }

  return true;
}


void MapEditorToolServerObjectLayerSelect::DrawMove(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  if (m_MoveMode)
  {
    auto snapped_pos = pos;
    m_MapEditor.GetViewer().SnapToGrid(snapped_pos);

    auto layer = m_MapEditor.GetServerObjectManager().GetLayerManager(m_LayerIndex);
    if (layer != nullptr)
    {
      layer->MoveSelection(snapped_pos - m_Start);
    }
  }
  else
  {
    auto selection_box = Box::FromPoints(m_Start, pos);

    auto layer = m_MapEditor.GetServerObjectManager().GetLayerManager(m_LayerIndex);
    if (layer != nullptr)
    {
      layer->SelectServerObjects(selection_box);
    }

    m_MapEditor.GetViewer().SetSelectionBox(selection_box);
  }
}

void MapEditorToolServerObjectLayerSelect::DrawEnd(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  if (m_MoveMode)
  {
    auto layer = m_MapEditor.GetServerObjectManager().GetLayerManager(m_LayerIndex);
    if (layer != nullptr)
    {
      layer->DropSelection();
    }
  }
  else
  {
    m_MapEditor.GetViewer().ClearSelectionBox();

    auto layer = m_MapEditor.GetServerObjectManager().GetLayerManager(m_LayerIndex);
    if (layer != nullptr)
    {
      auto sel_index = layer->GetSingleSelectionIndex();
      if (sel_index)
      {
        MapEditorLayerSelection layer_selection;
        layer_selection.m_Type = MapEditorLayerItemType::kServerObject;
        layer_selection.m_Index = (std::size_t)m_LayerIndex;
        layer_selection.m_SubIndex = sel_index.Value();
        m_MapEditor.ChangeLayerSelection(layer_selection, false);
      }
      else
      {
        m_MapEditor.ClearPropertyPanel();
      }
    }
  }
}

void MapEditorToolServerObjectLayerSelect::DrawCancel()
{
  auto layer = m_MapEditor.GetServerObjectManager().GetLayerManager(m_LayerIndex);
  if (layer != nullptr)
  {
    if (m_MoveMode)
    {
      layer->MoveSelection(Vector2(0, 0));
    }

    layer->ClearSelection();
  }

  m_MapEditor.GetViewer().ClearSelectionBox();
}
