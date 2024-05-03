
#include "MapEditorToolEntityLayerSelect.h"
#include "MapEditorToolEntityLayerDraw.h"
#include "MapEditor.h"

MapEditorToolEntityLayerSelect::MapEditorToolEntityLayerSelect(MapEditor & map_editor, int layer_index) :
  MapEditorToolBase(map_editor),
  m_LayerIndex(layer_index)
{

}

void MapEditorToolEntityLayerSelect::Init()
{
  m_MapEditor.GetSelector().GetEntitySelector()->Clear();
}

void MapEditorToolEntityLayerSelect::Cleanup()
{
  auto layer = m_MapEditor.GetEntityManager().GetLayerManager(m_LayerIndex);
  if (layer)
  {
    layer->ClearSelection();
  }

  m_MapEditor.GetViewer().ClearSelectionBox();
}

void MapEditorToolEntityLayerSelect::Delete()
{
  auto layer = m_MapEditor.GetEntityManager().GetLayerManager(m_LayerIndex);
  if (layer != nullptr)
  {
    layer->DeleteSelectedEntities();
  }
}

bool MapEditorToolEntityLayerSelect::DrawStart(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  auto layer = m_MapEditor.GetEntityManager().GetLayerManager(m_LayerIndex);
  if (layer == nullptr)
  {
    return false;
  }

  if (alt)
  {
    auto entity = layer->FindEntity(pos);
    if (entity)
    {
      m_MapEditor.SetSelectedEntity(m_LayerIndex, entity->data());
    }

    return false;
  }

  m_Start = pos;
  if (layer->IsOnSelectedEntity(pos))
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


void MapEditorToolEntityLayerSelect::DrawMove(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  if (m_MoveMode)
  {
    auto snapped_pos = pos;
    m_MapEditor.GetViewer().SnapToGrid(snapped_pos);

    auto layer = m_MapEditor.GetEntityManager().GetLayerManager(m_LayerIndex);
    if (layer != nullptr)
    {
      layer->MoveSelection(snapped_pos - m_Start);
    }
  }
  else
  {
    auto selection_box = Box::FromPoints(m_Start, pos);

    auto layer = m_MapEditor.GetEntityManager().GetLayerManager(m_LayerIndex);
    if (layer != nullptr)
    {
      layer->SelectEntities(selection_box);
    }

    m_MapEditor.GetViewer().SetSelectionBox(selection_box);
  }
}

void MapEditorToolEntityLayerSelect::DrawEnd(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  if (m_MoveMode)
  {
    auto layer = m_MapEditor.GetEntityManager().GetLayerManager(m_LayerIndex);
    if (layer != nullptr)
    {
      layer->DropSelection();
    }
  }
  else
  {
    m_MapEditor.GetViewer().ClearSelectionBox();

    auto layer = m_MapEditor.GetEntityManager().GetLayerManager(m_LayerIndex);
    if (layer != nullptr)
    {
      auto sel_index = layer->GetSingleSelectionIndex();
      if (sel_index)
      {
        MapEditorLayerSelection layer_selection;
        layer_selection.m_Type = MapEditorLayerItemType::kEntity;
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

void MapEditorToolEntityLayerSelect::DrawCancel()
{
  auto layer = m_MapEditor.GetEntityManager().GetLayerManager(m_LayerIndex);
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
