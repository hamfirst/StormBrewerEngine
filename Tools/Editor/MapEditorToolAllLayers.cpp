
#include "Foundation/Math/Util.h"
#include "Foundation/Math/Intersection.h"

#include "MapEditorToolAllLayers.h"
#include "MapEditor.h"

MapEditorToolAllLayers::MapEditorToolAllLayers(MapEditor & map_editor) :
  MapEditorToolBase(map_editor)
{

}

void MapEditorToolAllLayers::Init()
{

}

void MapEditorToolAllLayers::Cleanup()
{
  auto layer_visitor = [&](auto index, auto & layer)
  {
    layer->ClearSelection();
  };

  m_MapEditor.GetEntityManager().VisitLayers(layer_visitor);
  m_MapEditor.GetServerObjectManager().VisitLayers(layer_visitor);
  m_MapEditor.GetParallaxManager().VisitLayers(layer_visitor);

  m_MapEditor.GetViewer().ClearSelectionBox();
}

void MapEditorToolAllLayers::Delete()
{
  auto entity_visitor = [&](auto index, auto & layer)
  {
    layer->DeleteSelectedEntities();
  };

  m_MapEditor.GetEntityManager().VisitLayers(entity_visitor);
}

void MapEditorToolAllLayers::DrawPreview(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{

}

bool MapEditorToolAllLayers::DrawStart(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  return true;
}


void MapEditorToolAllLayers::DrawMove(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{

}

void MapEditorToolAllLayers::DrawEnd(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{

}

void MapEditorToolAllLayers::DrawCancel()
{

}

Optional<MapEditorLayerSelection> MapEditorToolAllLayers::PickLayer(const Vector2 & pos)
{
  float best_dist = 10000000;
  Optional<MapEditorLayerSelection> layer_selection;

  auto screen_space_pos = (Vector2)m_MapEditor.GetViewer().TransformFromMapSpaceToScreenSpace(pos);

  auto anchor_visitor = [&](auto index, auto & layer)
  {
    auto point_pos = layer->GetPreviewAnchor();

    if (point_pos)
    {
      auto screen_space = (Vector2)m_MapEditor.GetViewer().TransformFromMapSpaceToScreenSpace(point_pos.Value());

      auto dist = DistEstimate(screen_space, screen_space_pos);
      if (dist < best_dist && dist < 40)
      {
        best_dist = dist;
        layer_selection = { MapEditorLayerItemType::kAnchor, (std::size_t)index };
      }
    }
  };

  m_MapEditor.GetAnchorManager().VisitLayers(anchor_visitor);
  return layer_selection;
}



