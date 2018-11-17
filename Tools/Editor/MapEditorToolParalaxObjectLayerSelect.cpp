
#include "MapEditorToolParalaxObjectLayerSelect.h"
#include "MapEditorToolParalaxObjectLayerDraw.h"
#include "MapEditor.h"

MapEditorToolParalaxObjectLayerSelect::MapEditorToolParalaxObjectLayerSelect(MapEditor & map_editor, int layer_index) :
  MapEditorToolBase(map_editor),
  m_LayerIndex(layer_index)
{

}

void MapEditorToolParalaxObjectLayerSelect::Init()
{
  m_MapEditor.GetSelector().GetParalaxObjectSelector()->Clear();
}

void MapEditorToolParalaxObjectLayerSelect::Cleanup()
{
  auto layer = m_MapEditor.GetParalaxManager().GetLayerManager(m_LayerIndex);
  if (layer)
  {
    layer->ClearSelection();
  }

  m_MapEditor.GetViewer().ClearSelectionBox();
}

void MapEditorToolParalaxObjectLayerSelect::Delete()
{
  auto layer = m_MapEditor.GetParalaxManager().GetLayerManager(m_LayerIndex);
  if (layer != nullptr)
  {
    layer->DeleteSelectedParalaxObjects();
  }
}

bool MapEditorToolParalaxObjectLayerSelect::DrawStart(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  auto layer = m_MapEditor.GetParalaxManager().GetLayerManager(m_LayerIndex);
  if (layer == nullptr)
  {
    return false;
  }

  if (alt)
  {
    auto paralax_object = layer->FindParalaxObject(pos);
    if (paralax_object)
    {
      m_MapEditor.SetSelectedParalaxObject(m_LayerIndex, paralax_object.Value());
    }

    return false;
  }

  m_Start = pos;
  if (layer->IsOnSelectedParalaxObject(pos))
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


void MapEditorToolParalaxObjectLayerSelect::DrawMove(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  if (m_MoveMode)
  {
    auto snapped_pos = pos;
    m_MapEditor.GetViewer().SnapToGrid(snapped_pos);

    auto layer = m_MapEditor.GetParalaxManager().GetLayerManager(m_LayerIndex);
    if (layer != nullptr)
    {
      layer->MoveSelection(snapped_pos - m_Start);
    }
  }
  else
  {
    auto selection_box = Box::FromPoints(m_Start, pos);

    auto layer = m_MapEditor.GetParalaxManager().GetLayerManager(m_LayerIndex);
    if (layer != nullptr)
    {
      layer->SelectParalaxObjects(selection_box);
    }

    m_MapEditor.GetViewer().SetSelectionBox(selection_box);
  }
}

void MapEditorToolParalaxObjectLayerSelect::DrawEnd(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  if (m_MoveMode)
  {
    auto layer = m_MapEditor.GetParalaxManager().GetLayerManager(m_LayerIndex);
    if (layer != nullptr)
    {
      layer->DropSelection();
    }
  }
  else
  {
    m_MapEditor.GetViewer().ClearSelectionBox();

    auto layer = m_MapEditor.GetParalaxManager().GetLayerManager(m_LayerIndex);
    if (layer != nullptr)
    {
      auto sel_index = layer->GetSingleSelectionIndex();
      if (sel_index)
      {
        MapEditorLayerSelection layer_selection;
        layer_selection.m_Type = MapEditorLayerItemType::kParalaxObject;
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

void MapEditorToolParalaxObjectLayerSelect::DrawCancel()
{
  auto layer = m_MapEditor.GetParalaxManager().GetLayerManager(m_LayerIndex);
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
