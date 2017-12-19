

#include <QApplication>
#include <QClipboard>

#include "StormRefl/StormReflJsonStd.h"
#include "StormData/StormDataJson.h"

#include "Foundation/BasicTypes/BasicTypeFuncs.h"

#include "Runtime/Map/MapTileJson.h"

#include "Engine/Rendering/VertexBufferBuilder.h"
#include "Engine/Rendering/RenderUtil.h"
#include "Engine/Sprite/SpriteEngineData.h"
#include "Engine/Shader/ShaderManager.h"

#include "MapEditorTileManager.h"
#include "MapEditor.h"


MapEditorTileManager::MapEditorTileManager(NotNullPtr<MapEditor> editor, MapDef & map, int layer_index) :
  m_Editor(editor),
  m_Map(map),
  m_LayerIndex(layer_index),
  m_InitialSyncComplete(false),
  m_RecreateDrawInfo(false),
  m_IgnoreTextureReloads(false),
  m_TileWatcher(m_Editor),
  m_AnimWatcher(m_Editor),
  m_LocalChange(false),
  m_Hidden(false)
{
  auto layer_tile_path = ".m_ManualTileLayers[" + std::to_string(m_LayerIndex) + "].m_Tiles";
  m_TileWatcher.SetPath(layer_tile_path.data(), false, true, [=] { return m_Map.m_ManualTileLayers.HasAt(layer_index); });
  m_TileWatcher.SetChangeCallback([=](const ReflectionChangeNotification & change) { HandleTileListChange(change); });
  m_TileWatcher.SetChildChangeCallback([=](const ReflectionChangeNotification & change, std::size_t index) { HandleTileChildChange(change, index); });

  auto layer_anim_path = ".m_ManualTileLayers[" + std::to_string(m_LayerIndex) + "].m_Animations";
  m_AnimWatcher.SetPath(layer_anim_path.data(), false, true, [=] { return m_Map.m_ManualTileLayers.HasAt(layer_index); });
  m_AnimWatcher.SetChangeCallback([=](const ReflectionChangeNotification & change) { HandleAnimListChange(change); });
  m_AnimWatcher.SetChildChangeCallback([=](const ReflectionChangeNotification & change, std::size_t index) { HandleAnimChildChange(change, index); });

  SyncTileSheet();
}

void MapEditorTileManager::Update()
{
  auto tile_sheet = m_TileSheet.GetResource();
  if (tile_sheet == nullptr)
  {
    return;
  }

  if (m_Map.m_ManualTileLayers.HasAt(m_LayerIndex) == false || m_InitialSyncComplete == false)
  {
    return;
  }

  m_NumFrames++;
  for (auto & elem : m_AnimInfo.Value())
  {
    tile_sheet->FrameAdvance(elem.second.m_State);
  }
}

void MapEditorTileManager::SyncTiles(NotNullPtr<TileSheetResource> tile_sheet)
{
  m_SelectedTileOffset = {};
  m_SelectedAnimOffset = {};
  m_SelectedTiles.clear();
  m_SelectedAnimations.clear();

  if (m_Map.m_ManualTileLayers.HasAt(m_LayerIndex) == false)
  {
    return;
  }

  m_TileLocations.Emplace();
  m_TileLocations->Reserve((m_Map.m_ManualTileLayers[m_LayerIndex].m_Tiles.HighestIndex() + 2) * 2);

  m_TileSpatialDatabase.Emplace();

  m_AnimInfo.Emplace();
  m_AnimInfo->Reserve((m_Map.m_ManualTileLayers[m_LayerIndex].m_Animations.HighestIndex() + 2) * 2);
  m_AnimSpatialDatabase.Emplace();

  Optional<Box> tile_map_extents;

  std::vector<std::size_t> used_tile_indices;
  std::vector<std::pair<std::size_t, Box>> tiles;
  for (auto elem : m_Map.m_ManualTileLayers[m_LayerIndex].m_Tiles)
  {
    Box tile_box = GetTileBounds(elem.second.Value());

    if (tile_map_extents == false)
    {
      tile_map_extents.Emplace(tile_box);
    }
    else
    {
      BoxUnionInPlace(tile_map_extents.Value(), tile_box);
    }

    m_TileLocations->EmplaceAt(elem.first, tile_box);
    used_tile_indices.push_back(elem.first);
    tiles.emplace_back(std::make_pair(elem.first, tile_box));
  }

  Optional<Box> anim_map_extents;

  std::vector<std::size_t> used_anim_indices;
  std::vector<std::pair<std::size_t, Box>> anims;
  for (auto elem : m_Map.m_ManualTileLayers[m_LayerIndex].m_Animations)
  {
    Box tile_box = GetAnimBounds(elem.second.Value());

    if (anim_map_extents == false)
    {
      anim_map_extents.Emplace(tile_box);
    }
    else
    {
      BoxUnionInPlace(anim_map_extents.Value(), tile_box);
    }

    AnimationInfo anim_info;
    anim_info.m_Position = Vector2(elem.second->x, elem.second->y);
    anim_info.m_Bounds = tile_box;
    tile_sheet->InitAnimation(elem.second->m_Animation, elem.second->m_FrameOffset + m_NumFrames, anim_info.m_State);

    m_AnimInfo->EmplaceAt(elem.first, anim_info);
    used_anim_indices.push_back(elem.first);
    anims.emplace_back(std::make_pair(elem.first, tile_box));
  }

  if (tile_map_extents)
  {
    m_TileSpatialDatabase->InsertBatch(tile_map_extents.Value(), tiles);
  }

  if (anim_map_extents)
  {
    m_AnimSpatialDatabase->InsertBatch(anim_map_extents.Value(), anims);
  }

  m_TileIdAllocator.Emplace(used_tile_indices.size() * 2, used_tile_indices);
  m_AnimIdAllocator.Emplace(used_anim_indices.size() * 2, used_anim_indices);

  m_DirtyGrids.Emplace();
  m_TileSpatialDatabase->VisitAll([&](uint32_t grid_id, auto & node) { m_DirtyGrids->push_back(grid_id); });

  m_RecreateDrawInfo = true;
  m_InitialSyncComplete = true;
}

void MapEditorTileManager::SyncTileSheet()
{
  if (m_Map.m_ManualTileLayers.HasAt(m_LayerIndex) == false)
  {
    return;
  }

  TileSheetResource::LoadWithCallback(m_Map.m_ManualTileLayers[m_LayerIndex].m_TileSheet.data(),
    [this](NotNullPtr<TileSheetResource> resource) { HandleTileSheetReload(resource); }, m_TileSheet);
}

void MapEditorTileManager::InsertTile(const MapTile & tile)
{
  if (m_Map.m_ManualTileLayers.HasAt(m_LayerIndex) == false || m_InitialSyncComplete == false)
  {
    return;
  }

  auto & layer = m_Map.m_ManualTileLayers[m_LayerIndex];
  auto box = GetTileBounds(tile);

  std::vector<std::size_t> existing_tiles;
  Box check_box = { {tile.x, tile.y}, {tile.x, tile.y} };
  m_TileSpatialDatabase->Query(check_box, existing_tiles);

  for (auto tile_index : existing_tiles)
  {
    if (m_TileLocations->GetAt(tile_index) == box)
    {
      if (layer.m_Tiles[tile_index]->m_FrameId == tile.m_FrameId &&
          layer.m_Tiles[tile_index]->m_TextureHash == tile.m_TextureHash)
      {
        return;
      }

      m_LocalChange = true;
      m_Editor->DisableChangeCallbacks();
      layer.m_Tiles[tile_index] = tile;
      m_Editor->EnableChangeCallbacks();
      m_LocalChange = false;

      RefreshTile(tile_index);
      return;
    }
  }

  auto id = m_TileIdAllocator->Allocate();

  m_LocalChange = true;
  m_Editor->DisableChangeCallbacks();
  layer.m_Tiles.EmplaceAt(id, tile);
  m_Editor->EnableChangeCallbacks();
  m_LocalChange = false;

  m_TileLocations->EmplaceAt(id, box);

  m_TileSpatialDatabase->Insert(box, id);
  m_DrawInfo->VisitGridIds(box, [this](uint32_t grid_id) { AddToDirtyGridList(grid_id); return true; });
}

void MapEditorTileManager::CommitPreviewTiles()
{
  if (m_PreviewTiles.size() == 0)
  {
    return;
  }

  if (m_Map.m_ManualTileLayers.HasAt(m_LayerIndex) == false || m_InitialSyncComplete == false)
  {
    return;
  }

  Box bounds = Box::FromPoint(Vector2(m_PreviewTiles[0].x, m_PreviewTiles[0].y));

  for (auto & tile : m_PreviewTiles)
  {
    BoxUnionInPlace(bounds, Box::FromPoint(Vector2(tile.x, tile.y)));
  }

  std::vector<std::size_t> existing_tiles;
  m_TileSpatialDatabase->Query(bounds, existing_tiles);

  auto & layer = m_Map.m_ManualTileLayers[m_LayerIndex];

  std::vector<std::size_t> new_tiles;
  std::vector<std::pair<std::size_t, std::size_t>> replace_tiles;

  for (std::size_t preview_index = 0, preview_end = m_PreviewTiles.size(); preview_index < preview_end; ++preview_index)
  {
    bool found = false;

    auto & preview = m_PreviewTiles[preview_index];
    for (std::size_t existing_index = 0, existing_end = existing_tiles.size(); existing_index < existing_end; ++existing_index)
    {
      auto & existing = layer.m_Tiles[existing_tiles[existing_index]].Value();

      if (existing.x == preview.x && existing.y == preview.y && existing.m_TextureHash == preview.m_TextureHash)
      {
        found = true;
        if (existing.m_FrameId == preview.m_FrameId)
        {
          break;
        }

        replace_tiles.push_back(std::make_pair(preview_index, existing_index));
        break;
      }
    }

    if (found == false)
    {
      new_tiles.push_back(preview_index);
    }
  }

  if (replace_tiles.size() == 0 && new_tiles.size() == 0)
  {
    return;
  }

  m_LocalChange = true;
  m_Editor->BeginTransaction();
  m_Editor->DisableChangeCallbacks();

  if (replace_tiles.size() > 0)
  {
    Optional<Box> replace_tile_bounds;
    for (auto & replace_tile : replace_tiles)
    {
      auto & tile = m_PreviewTiles[replace_tile.first];
      layer.m_Tiles[existing_tiles[replace_tile.second]] = tile;

      auto box = GetTileBounds(tile);
      if (replace_tile_bounds)
      {
        BoxUnionInPlace(replace_tile_bounds.Value(), box);
      }
      else
      {
        replace_tile_bounds = box;
      }
    }

    AddToDirtyGridList(replace_tile_bounds);
  }

  std::vector<std::pair<std::size_t, Box>> new_tile_boxes;

  if (new_tiles.size() > 0)
  {
    Optional<Box> new_tile_bounds;

    for (auto tile_index : new_tiles)
    {
      auto & new_tile = m_PreviewTiles[tile_index];
      auto id = m_TileIdAllocator->Allocate();
      layer.m_Tiles.EmplaceAt(id, new_tile);

      auto box = GetTileBounds(new_tile);
      m_TileLocations->EmplaceAt(id, box);

      new_tile_boxes.emplace_back(std::make_pair(id, box));

      if (new_tile_bounds)
      {
        BoxUnionInPlace(new_tile_bounds.Value(), box);
      }
      else
      {
        new_tile_bounds = box;
      }
    }

    m_TileSpatialDatabase->InsertBatch(new_tile_bounds.Value(), new_tile_boxes);
    AddToDirtyGridList(new_tile_bounds);
  }

  m_Editor->EnableChangeCallbacks();
  m_Editor->CommitChanges();
  m_LocalChange = false;
}

void MapEditorTileManager::SelectTiles(const Box & box)
{
  if (m_Map.m_ManualTileLayers.HasAt(m_LayerIndex) == false || m_InitialSyncComplete == false)
  {
    return;
  }

  auto old_bounds = GetMultiTileBounds(m_SelectedTiles);
  if (old_bounds)
  {
    AddToDirtyGridList(old_bounds.Value());
  }

  m_SelectedTiles.clear();
  m_TileSpatialDatabase->Query(box, m_SelectedTiles);
  m_SelectedTileOffset = {};

  if (m_SelectedTiles.size() > 0)
  {
    auto bounds = GetMultiTileBounds(m_SelectedTiles).Value();
    if (old_bounds)
    {
      BoxUnionInPlace(bounds, old_bounds.Value());
    }

    AddToDirtyGridList(bounds);
  }
}

void MapEditorTileManager::RemoveTiles(const std::vector<std::size_t> & tiles)
{
  if (m_Map.m_ManualTileLayers.HasAt(m_LayerIndex) == false || m_InitialSyncComplete == false)
  {
    return;
  }

  Optional<Box> dead_tiles_box;

  m_LocalChange = true;
  m_Editor->DisableChangeCallbacks();
  m_Editor->BeginTransaction();
  for (auto tile_index : tiles)
  {
    auto & old_box = m_TileLocations->GetAt(tile_index);

    if (!dead_tiles_box)
    {
      dead_tiles_box = old_box;
    }
    else
    {
      BoxUnionInPlace(dead_tiles_box.Value(), old_box);
    }

    m_Map.m_ManualTileLayers[m_LayerIndex].m_Tiles.RemoveAt(tile_index);
    m_TileLocations->RemoveAt(tile_index);
  }
  m_Editor->EnableChangeCallbacks();
  m_Editor->CommitChanges();
  m_LocalChange = false;

  if (dead_tiles_box)
  {
    m_TileSpatialDatabase->RemoveBatch(dead_tiles_box.Value(), tiles);
    m_DrawInfo->VisitGridIds(dead_tiles_box.Value(), [this](uint32_t grid_id) { AddToDirtyGridList(grid_id); return true; });
  }
}

Optional<MapTile> MapEditorTileManager::FindTile(const Vector2 & pos)
{
  if (m_Map.m_ManualTileLayers.HasAt(m_LayerIndex) == false || m_InitialSyncComplete == false)
  {
    return{};
  }

  Box b = { pos, pos };

  std::size_t outp_index;
  if (m_TileSpatialDatabase->QueryAny(b, outp_index))
  {
    return m_Map.m_ManualTileLayers[m_LayerIndex].m_Tiles[outp_index].Value();
  }

  return{};
}

void MapEditorTileManager::InsertAnimation(const MapAnimatedTile & anim)
{
  if (m_Map.m_ManualTileLayers.HasAt(m_LayerIndex) == false || m_InitialSyncComplete == false)
  {
    return;
  }

  auto & layer = m_Map.m_ManualTileLayers[m_LayerIndex];
  auto box = GetAnimBounds(anim);

  std::vector<std::size_t> existing_tiles;
  Box check_box = { { anim.x, anim.y },{ anim.x, anim.y } };
  m_AnimSpatialDatabase->Query(check_box, existing_tiles);

  for (auto tile_index : existing_tiles)
  {
    if (m_AnimInfo->GetAt(tile_index).m_Bounds == box)
    {
      if (layer.m_Animations[tile_index]->m_Animation == anim.m_Animation)
      {
        return;
      }

      m_LocalChange = true;
      m_Editor->DisableChangeCallbacks();
      layer.m_Animations[tile_index] = anim;
      m_Editor->EnableChangeCallbacks();
      m_LocalChange = false;

      RefreshAnimation(tile_index);
      return;
    }
  }

  auto id = m_AnimIdAllocator->Allocate();

  m_LocalChange = true;
  m_Editor->DisableChangeCallbacks();
  layer.m_Animations.EmplaceAt(id, anim);
  m_Editor->EnableChangeCallbacks();
  m_LocalChange = false;

  AnimationInfo anim_info;
  anim_info.m_Bounds = box;
  anim_info.m_Position = Vector2(anim.x, anim.y);
  m_TileSheet.GetResource()->InitAnimation(anim.m_Animation, anim.m_FrameOffset + m_NumFrames, anim_info.m_State);

  m_AnimInfo->EmplaceAt(id, anim_info);
  m_AnimSpatialDatabase->Insert(box, id);
}

void MapEditorTileManager::CommitPreviewAnimations()
{
  if (m_PreviewAnims.size() == 0)
  {
    return;
  }

  if (m_Map.m_ManualTileLayers.HasAt(m_LayerIndex) == false || m_InitialSyncComplete == false)
  {
    return;
  }

  Box bounds = Box::FromPoint(Vector2(m_PreviewAnims[0].x, m_PreviewAnims[0].y));

  for (auto & tile : m_PreviewAnims)
  {
    BoxUnionInPlace(bounds, Box::FromPoint(Vector2(tile.x, tile.y)));
  }

  std::vector<std::size_t> existing_tiles;
  m_AnimSpatialDatabase->Query(bounds, existing_tiles);

  auto & layer = m_Map.m_ManualTileLayers[m_LayerIndex];

  std::vector<std::size_t> new_tiles;
  std::vector<std::pair<std::size_t, std::size_t>> replace_tiles;

  for (std::size_t preview_index = 0, preview_end = m_PreviewAnims.size(); preview_index < preview_end; ++preview_index)
  {
    bool found = false;

    auto & preview = m_PreviewAnims[preview_index];
    for (std::size_t existing_index = 0, existing_end = existing_tiles.size(); existing_index < existing_end; ++existing_index)
    {
      auto & existing = layer.m_Animations[existing_tiles[existing_index]].Value();

      if (existing.x == preview.x && existing.y == preview.y && existing.m_Animation == preview.m_Animation)
      {
        found = true;
        replace_tiles.push_back(std::make_pair(preview_index, existing_index));
        break;
      }
    }

    if (found == false)
    {
      new_tiles.push_back(preview_index);
    }
  }

  if (replace_tiles.size() == 0 && new_tiles.size() == 0)
  {
    return;
  }

  m_LocalChange = true;
  m_Editor->BeginTransaction();
  m_Editor->DisableChangeCallbacks();

  if (replace_tiles.size() > 0)
  {
    for (auto & replace_tile : replace_tiles)
    {
      auto & tile = m_PreviewAnims[replace_tile.first];
      layer.m_Animations[existing_tiles[replace_tile.second]] = tile;
    }
  }

  std::vector<std::pair<std::size_t, Box>> new_tile_boxes;

  if (new_tiles.size() > 0)
  {
    Optional<Box> new_tile_bounds;

    for (auto tile_index : new_tiles)
    {
      auto & new_tile = m_PreviewAnims[tile_index];
      auto id = m_AnimIdAllocator->Allocate();
      layer.m_Animations.EmplaceAt(id, new_tile);

      auto box = GetAnimBounds(new_tile);

      AnimationInfo anim_info;
      anim_info.m_Bounds = box;
      anim_info.m_Position = Vector2(new_tile.x, new_tile.y);
      m_TileSheet.GetResource()->InitAnimation(new_tile.m_Animation, new_tile.m_FrameOffset + m_NumFrames, anim_info.m_State);

      m_AnimInfo->EmplaceAt(id, anim_info);

      new_tile_boxes.emplace_back(std::make_pair(id, box));

      if (new_tile_bounds)
      {
        BoxUnionInPlace(new_tile_bounds.Value(), box);
      }
      else
      {
        new_tile_bounds = box;
      }
    }

    m_AnimSpatialDatabase->InsertBatch(new_tile_bounds.Value(), new_tile_boxes);
  }

  m_Editor->EnableChangeCallbacks();
  m_Editor->CommitChanges();
  m_LocalChange = false;
}

void MapEditorTileManager::SelectAnimations(const Box & box)
{
  if (m_Map.m_ManualTileLayers.HasAt(m_LayerIndex) == false || m_InitialSyncComplete == false)
  {
    return;
  }

  m_SelectedAnimations.clear();
  m_AnimSpatialDatabase->Query(box, m_SelectedAnimations);
  m_SelectedAnimOffset = {};
}

void MapEditorTileManager::RemoveAnimations(const std::vector<std::size_t> & anims)
{
  if (m_Map.m_ManualTileLayers.HasAt(m_LayerIndex) == false || m_InitialSyncComplete == false)
  {
    return;
  }

  m_LocalChange = true;
  m_Editor->DisableChangeCallbacks();
  m_Editor->BeginTransaction();
  for (auto tile_index : anims)
  {
    m_Map.m_ManualTileLayers[m_LayerIndex].m_Animations.RemoveAt(tile_index);
    m_AnimInfo->RemoveAt(tile_index);
  }
  m_Editor->EnableChangeCallbacks();
  m_Editor->CommitChanges();
  m_LocalChange = false;
}

Optional<MapAnimatedTile> MapEditorTileManager::FindAnim(const Vector2 & pos)
{
  if (m_Map.m_ManualTileLayers.HasAt(m_LayerIndex) == false || m_InitialSyncComplete == false)
  {
    return{};
  }

  Box b = { pos, pos };

  std::size_t outp_index;
  if (m_AnimSpatialDatabase->QueryAny(b, outp_index))
  {
    return m_Map.m_ManualTileLayers[m_LayerIndex].m_Animations[outp_index].Value();
  }

  return{};
}

bool MapEditorTileManager::HasSelection()
{
  return m_SelectedTiles.size() > 0 || m_SelectedAnimations.size() > 0;
}

void MapEditorTileManager::ClearSelection()
{
  if (m_SelectedTiles.size() > 0)
  {
    auto bounds = GetMultiTileBounds(m_SelectedTiles).Value();
    AddToDirtyGridList(bounds);

    m_SelectedTiles.clear();
    m_SelectedTileOffset = {};
  }

  m_SelectedAnimations.clear();
  m_SelectedAnimOffset = {};
}

void MapEditorTileManager::DeleteSelection()
{
  if (m_Map.m_ManualTileLayers.HasAt(m_LayerIndex) == false || m_InitialSyncComplete == false)
  {
    return;
  }

  if (m_SelectedTiles.size() == 0 && m_SelectedAnimations.size() == 0)
  {
    return;
  }

  auto & layer = m_Map.m_ManualTileLayers[m_LayerIndex];

  m_LocalChange = true;
  m_Editor->BeginTransaction();
  m_Editor->DisableChangeCallbacks();

  if (m_SelectedTiles.size() > 0)
  {
    auto bounds = GetMultiTileBounds(m_SelectedTiles).Value();

    for (auto sel_tile : m_SelectedTiles)
    {
      layer.m_Tiles.RemoveAt(sel_tile);
      m_TileLocations->RemoveAt(sel_tile);
    }

    m_TileSpatialDatabase->RemoveBatch(bounds, m_SelectedTiles);
    m_SelectedTiles.clear();

    AddToDirtyGridList(bounds);
  }

  if (m_SelectedAnimations.size() > 0)
  {
    auto bounds = GetMultiAnimBounds(m_SelectedAnimations).Value();

    for (auto sel_tile : m_SelectedAnimations)
    {
      layer.m_Animations.RemoveAt(sel_tile);
      m_AnimInfo->RemoveAt(sel_tile);
    }

    m_AnimSpatialDatabase->RemoveBatch(bounds, m_SelectedAnimations);
    m_SelectedAnimations.clear();
  }

  m_Editor->EnableChangeCallbacks();
  m_Editor->CommitChanges();
  m_LocalChange = false;
}

void MapEditorTileManager::SetSelectionOffset(const Vector2 & offset)
{
  if (m_Map.m_ManualTileLayers.HasAt(m_LayerIndex) == false || m_InitialSyncComplete == false)
  {
    return;
  }

  m_SelectedTileOffset = offset;
  m_SelectedAnimOffset = offset;
}

void MapEditorTileManager::CommitSelectedOffset()
{
  if (m_SelectedTiles.size() == 0 && m_SelectedAnimations.size() == 0)
  {
    return;
  }

  if (m_Map.m_ManualTileLayers.HasAt(m_LayerIndex) == false || m_InitialSyncComplete == false)
  {
    return;
  }

  m_LocalChange = true;
  m_Editor->BeginTransaction();
  m_Editor->DisableChangeCallbacks();

  if ((m_SelectedTileOffset.x != 0 || m_SelectedTileOffset.y != 0) && m_SelectedTiles.size() != 0)
  {
    auto & layer = m_Map.m_ManualTileLayers[m_LayerIndex];

    auto bounds = GetMultiTileBounds(m_SelectedTiles).Value();

    std::vector<std::size_t> existing_tiles;
    m_TileSpatialDatabase->Query(bounds, existing_tiles);

    std::sort(m_SelectedTiles.begin(), m_SelectedTiles.end());
    std::sort(existing_tiles.begin(), existing_tiles.end());

    std::vector<std::size_t> non_selected;
    std::set_difference(existing_tiles.begin(), existing_tiles.end(), m_SelectedTiles.begin(), m_SelectedTiles.end(),
      std::inserter(non_selected, non_selected.begin()));

    std::vector<MapTile> non_selected_tiles;
    non_selected_tiles.reserve(non_selected.size());

    for (auto index : non_selected)
    {
      non_selected_tiles.push_back(layer.m_Tiles[index].Value());
    }

    std::vector<std::pair<std::size_t, Box>> tile_locations;
    std::vector<std::size_t> removed_tiles;

    for (auto index : m_SelectedTiles)
    {
      auto tile = layer.m_Tiles[index].Value();

      for (std::size_t non_selected_index = 0, end = non_selected_tiles.size(); non_selected_index < end; ++non_selected_index)
      {
        auto & non_selected_tile = non_selected_tiles[non_selected_index];
        if (tile.x == non_selected_tile.x && tile.y == non_selected_tile.y && tile.m_TextureHash == non_selected_tile.m_TextureHash)
        {
          layer.m_Tiles.RemoveAt(non_selected[non_selected_index]);
          m_TileLocations->RemoveAt(non_selected[non_selected_index]);

          removed_tiles.push_back(non_selected[non_selected_index]);
        }
      }

      tile.x += m_SelectedTileOffset.x;
      tile.y += m_SelectedTileOffset.y;

      layer.m_Tiles[index] = tile;

      auto box = GetTileBounds(tile);
      tile_locations.push_back(std::make_pair(index, box));

      (*m_TileLocations)[index] = box;
    }

    auto new_bounds = GetMultiTileBounds(m_SelectedTiles).Value();
    m_TileSpatialDatabase->RemoveBatch(bounds, removed_tiles);
    m_TileSpatialDatabase->RemoveBatch(bounds, m_SelectedTiles);
    m_TileSpatialDatabase->InsertBatch(new_bounds, tile_locations);
    BoxUnionInPlace(bounds, new_bounds);

    AddToDirtyGridList(bounds);

    m_SelectedTileOffset = {};
  }

  if ((m_SelectedAnimOffset.x != 0 || m_SelectedAnimOffset.y != 0) && m_SelectedAnimations.size() != 0)
  {
    auto & layer = m_Map.m_ManualTileLayers[m_LayerIndex];

    auto bounds = GetMultiAnimBounds(m_SelectedAnimations).Value();

    std::vector<std::size_t> existing_tiles;
    m_TileSpatialDatabase->Query(bounds, existing_tiles);

    std::sort(m_SelectedAnimations.begin(), m_SelectedAnimations.end());
    std::sort(existing_tiles.begin(), existing_tiles.end());

    std::vector<std::size_t> non_selected;
    std::set_difference(existing_tiles.begin(), existing_tiles.end(), m_SelectedTiles.begin(), m_SelectedTiles.end(),
      std::inserter(non_selected, non_selected.begin()));

    std::vector<MapAnimatedTile> non_selected_tiles;
    non_selected_tiles.reserve(non_selected.size());

    for (auto index : non_selected)
    {
      non_selected_tiles.push_back(layer.m_Animations[index].Value());
    }

    std::vector<std::pair<std::size_t, Box>> tile_locations;
    std::vector<std::size_t> removed_tiles;

    for (auto index : m_SelectedAnimations)
    {
      auto tile = layer.m_Animations[index].Value();

      for (std::size_t non_selected_index = 0, end = non_selected_tiles.size(); non_selected_index < end; ++non_selected_index)
      {
        auto & non_selected_tile = non_selected_tiles[non_selected_index];
        if (tile.x == non_selected_tile.x && tile.y == non_selected_tile.y && tile.m_Animation == non_selected_tile.m_Animation)
        {
          layer.m_Animations.RemoveAt(non_selected[non_selected_index]);
          m_AnimInfo->RemoveAt(non_selected[non_selected_index]);

          removed_tiles.push_back(non_selected[non_selected_index]);
        }
      }

      tile.x += m_SelectedAnimOffset.x;
      tile.y += m_SelectedAnimOffset.y;

      layer.m_Animations[index] = tile;

      auto box = GetAnimBounds(tile);
      tile_locations.push_back(std::make_pair(index, box));

      AnimationInfo anim_info;
      anim_info.m_Bounds = box;
      anim_info.m_Position = Vector2(tile.x, tile.y);
      m_TileSheet.GetResource()->InitAnimation(tile.m_Animation, tile.m_FrameOffset + m_NumFrames, anim_info.m_State);

      (*m_AnimInfo)[index] = anim_info;
    }

    auto new_bounds = GetMultiAnimBounds(m_SelectedAnimations).Value();
    m_AnimSpatialDatabase->RemoveBatch(bounds, removed_tiles);
    m_AnimSpatialDatabase->RemoveBatch(bounds, m_SelectedAnimations);
    m_AnimSpatialDatabase->InsertBatch(new_bounds, tile_locations);

    m_SelectedAnimOffset = {};
  }

  m_Editor->EnableChangeCallbacks();
  m_Editor->CommitChanges();
  m_LocalChange = false;
}

bool MapEditorTileManager::IsOnSelectedTile(const Vector2 & pos)
{
  if (m_Map.m_ManualTileLayers.HasAt(m_LayerIndex) == false || m_InitialSyncComplete == false)
  {
    return false;
  }

  if (m_SelectedTiles.size() != 0)
  {
    Box b = { pos, pos };

    std::vector<std::size_t> outp_indices;
    m_TileSpatialDatabase->Query(b, outp_indices);

    for (auto & index : m_SelectedTiles)
    {
      if (vfind(outp_indices, index))
      {
        return true;
      }
    }
  }

  if (m_SelectedAnimations.size() != 0)
  {
    Box b = { pos, pos };

    std::vector<std::size_t> outp_indices;
    m_AnimSpatialDatabase->Query(b, outp_indices);

    for (auto & index : m_SelectedAnimations)
    {
      if (vfind(outp_indices, index))
      {
        return true;
      }
    }
  }

  return false;
}

bool MapEditorTileManager::IsOnPreviewTile(const Vector2 & pos)
{
  if (m_Map.m_ManualTileLayers.HasAt(m_LayerIndex) == false || m_InitialSyncComplete == false)
  {
    return false;
  }

  if (m_PreviewTiles.size() != 0)
  {
    for (auto & tile : m_PreviewTiles)
    {
      auto box = GetTileBounds(tile);
      if (PointInBox(box, pos))
      {
        return true;
      }
    }
  }

  if (m_PreviewAnims.size() != 0)
  {
    for (auto & tile : m_PreviewAnims)
    {
      auto box = GetAnimBounds(tile);
      if (PointInBox(box, pos))
      {
        return true;
      }
    }
  }

  return false;
}

void MapEditorTileManager::DuplicateSelectedToPreview()
{
  if (m_Map.m_ManualTileLayers.HasAt(m_LayerIndex) == false || m_InitialSyncComplete == false)
  {
    return;
  }

  auto bounds = m_PreviewTileBounds;

  m_PreviewTiles.clear();
  m_PreviewTileBounds.Clear();

  m_PreviewAnims.clear();
  m_PreviewAnimBounds.Clear();

  auto & layer = m_Map.m_ManualTileLayers[m_LayerIndex];

  for (auto tile_index : m_SelectedTiles)
  {
    auto & tile = layer.m_Tiles[tile_index].Value();
    m_PreviewTiles.push_back(tile);

    if (bounds)
    {
      BoxUnionInPlace(bounds.Value(), m_TileLocations->GetAt(tile_index));
    }
    else
    {
      bounds = m_TileLocations->GetAt(tile_index);
    }
  }


  for (auto tile_index : m_SelectedAnimations)
  {
    auto & tile = layer.m_Animations[tile_index].Value();
    m_PreviewAnims.push_back(tile);

    if (m_PreviewAnimBounds)
    {
      BoxUnionInPlace(bounds.Value(), GetAnimBounds(tile));
    }
    else
    {
      m_PreviewAnimBounds = GetAnimBounds(tile);
    }
  }

  if (bounds)
  {
    m_PreviewTileBounds = bounds;
    AddToDirtyGridList(bounds.Value());
  }
}

void MapEditorTileManager::CopySelection()
{
  if (m_Map.m_ManualTileLayers.HasAt(m_LayerIndex) == false || m_InitialSyncComplete == false)
  {
    return;
  }

  if (m_SelectedTiles.size() == 0 && m_SelectedAnimations.size() == 0)
  {
    return;
  }

  auto & layer = m_Map.m_ManualTileLayers[m_LayerIndex];

  int64_t avg_x = 0;
  int64_t avg_y = 0;
  int64_t avg_num = 0;

  for (auto tile_index : m_SelectedTiles)
  {
    auto & tile = layer.m_Tiles[tile_index].Value();
    avg_x += tile.x;
    avg_y += tile.y;
    avg_num++;
  }

  for (auto tile_index : m_SelectedAnimations)
  {
    auto & tile = layer.m_Animations[tile_index].Value();
    avg_x += tile.x;
    avg_y += tile.y;
    avg_num++;
  }

  avg_x /= avg_num;
  avg_y /= avg_num;

  Vector2 avg_pos = Vector2((int)avg_x, (int)avg_y);
  m_Editor->GetViewer().SnapToGrid(avg_pos, false, true);

  std::pair<std::vector<MapTile>, std::vector<MapAnimatedTile>> clipboard_info;

  for (auto tile_index : m_SelectedTiles)
  {
    auto tile = layer.m_Tiles[tile_index].Value();
    tile.x -= avg_pos.x;
    tile.y -= avg_pos.y;

    clipboard_info.first.push_back(tile);
  }

  for (auto tile_index : m_SelectedAnimations)
  {
    auto tile = layer.m_Animations[tile_index].Value();
    tile.x -= avg_pos.x;
    tile.y -= avg_pos.y;

    clipboard_info.second.push_back(tile);
  }

  QString clipboard_data;
  StormReflEncodeJson(clipboard_info, clipboard_data);

  QClipboard *clipboard = QApplication::clipboard();
  clipboard->setText(clipboard_data);
}

void MapEditorTileManager::PasteSelection(const Vector2 & screen_center)
{
  auto target_pos = screen_center;
  m_Editor->GetViewer().SnapToGrid(target_pos, false, true);

  QClipboard *clipboard = QApplication::clipboard();
  auto clipboard_data = clipboard->text();

  std::pair<std::vector<MapTile>, std::vector<MapAnimatedTile>> clipboard_info;
  StormReflParseJson(clipboard_info, clipboard_data.toStdString().data());

  for (auto & tile : clipboard_info.first)
  {
    tile.x += target_pos.x;
    tile.y += target_pos.y;
  }

  for (auto & tile : clipboard_info.second)
  {
    tile.x += target_pos.x;
    tile.y += target_pos.y;
  }

  SetPreviewTiles(clipboard_info.first);
  SetPreviewAnimations(clipboard_info.second);
}

void MapEditorTileManager::Draw(const Box & viewport_bounds, const RenderVec2 & screen_center, RenderState & render_state, RenderUtil & render_util)
{
  if (m_InitialSyncComplete == false)
  {
    return;
  }

  if (m_Map.m_ManualTileLayers.HasAt(m_LayerIndex) == false || m_InitialSyncComplete == false)
  {
    return;
  }

  auto & layer = m_Map.m_ManualTileLayers[m_LayerIndex];

  if (m_RecreateDrawInfo)
  {
    m_DrawInfo.Emplace();
    m_RecreateDrawInfo = false;
  }

  std::vector<uint32_t> dead_grids;
  for (auto grid_id : m_DirtyGrids.Value())
  {
    m_DrawInfo->VisitNode(grid_id, [&](const Box & bounding_box, GridDrawList & grid_draw_elems) {
      
      grid_draw_elems.m_DrawElems.clear();

      std::vector<std::size_t> tile_indices;
      m_TileSpatialDatabase->Query(bounding_box, tile_indices);

      struct TileSortInfo
      {
        MapTile m_Tile;
        int m_LowerEdge;
        int m_X;
      };

      std::vector<TileSortInfo> tiles;
      for (auto tile_index : tile_indices)
      {
        auto & tile = layer.m_Tiles[tile_index].Value();

        if (IsTileInPreview(tile))
        {
          continue;
        }

        if (vfind(m_SelectedTiles, tile_index))
        {
          continue;
        }

        auto tile_bounds = GetTileBounds(tile);
        auto lower_edge_offset = m_TileSheet.GetResource()->GetLowerEdgeOffset(tile.GetTileId());

        tiles.push_back(TileSortInfo{ tile, tile_bounds.m_Start.y + lower_edge_offset, tile_bounds.m_Start.x });
      }

      std::sort(tiles.begin(), tiles.end(), [](const TileSortInfo & a, const TileSortInfo & b)
      { 
        if (a.m_LowerEdge < b.m_LowerEdge)
        {
          return false;
        }

        if (a.m_LowerEdge > b.m_LowerEdge)
        {
          return true;
        }

        if (a.m_X > b.m_X)
        {
          return false;
        }

        if (a.m_X < b.m_X)
        {
          return true;
        }

        return a.m_Tile.m_TextureHash < b.m_Tile.m_TextureHash;
      });

      std::vector<std::pair<uint32_t, std::vector<MapTile>>> draw_buckets;

      uint32_t last_texture = 0;
      for (auto & tile : tiles)
      {
        if (tile.m_Tile.m_TextureHash == 0)
        {
          continue;
        }

        if (tile.m_Tile.m_TextureHash != last_texture)
        {
          draw_buckets.emplace_back(std::make_pair(tile.m_Tile.m_TextureHash, std::vector<MapTile>{}));
          last_texture = tile.m_Tile.m_TextureHash;
        }

        draw_buckets.back().second.emplace_back(tile.m_Tile);
      }

      QuadVertexBufferBuilder builder;
      Box slice_box = { Vector2{ 0, 0 }, Vector2{ 1023, 1023 } };
      int start_index = 0;

      for (auto & bucket : draw_buckets)
      {
        int texture_index = -1;
        for(int index = 0, end = (int)m_Textures.size(); index < end; ++index)
        {
          if (m_Textures[index].m_TextureNameHash == bucket.first)
          {
            texture_index = index;
            break;
          }
        }

        if (texture_index == -1)
        {
          continue;
        }

        auto texture = m_Textures[texture_index].m_AssetLink.Get();
        if (texture == nullptr || texture->IsLoaded() == false || texture->GetWidth() <= 0 || texture->GetHeight() <= 0)
        {
          continue;
        }

        auto & texture_data = m_Textures[texture_index];
        int width_in_frames = (texture->GetWidth() + texture_data.m_FrameWidth - 1) / texture_data.m_FrameWidth;

        GridDrawElement draw_element{ texture, start_index };

        for (auto & tile : bucket.second)
        {
          int src_x = (tile.m_FrameId % width_in_frames) * texture_data.m_FrameWidth;
          int src_y = (tile.m_FrameId / width_in_frames) * texture_data.m_FrameHeight;

          int dst_x = tile.x - bounding_box.m_Start.x - texture_data.m_FrameWidth / 2;
          int dst_y = tile.y - bounding_box.m_Start.y - texture_data.m_FrameHeight / 2;

          QuadVertexBuilderInfo quad;
          quad.m_Position.m_Start = Vector2(dst_x, dst_y);
          quad.m_Position.m_End = quad.m_Position.m_Start + Vector2(texture_data.m_FrameWidth, texture_data.m_FrameHeight);
          quad.m_TexCoords.m_Start = Vector2(src_x, src_y);
          quad.m_TexCoords.m_End = quad.m_TexCoords.m_Start + Vector2(texture_data.m_FrameWidth, texture_data.m_FrameHeight);
          quad.m_TextureSize = Vector2(texture->GetWidth(), texture->GetHeight());
          quad.m_Color = Color(255, 255, 255, 255);
          
          if (builder.AddSlicedQuad(quad, slice_box))
          {
            start_index += 6;
          }
        }

        draw_element.m_EndIndex = start_index;
        grid_draw_elems.m_DrawElems.emplace_back(std::move(draw_element));
      }

      builder.FillVertexBuffer(grid_draw_elems.m_VertexBuffer);

    }, true);
  }

  m_DirtyGrids->clear();

  m_DrawInfo->VisitGrid(viewport_bounds, [&](uint32_t grid_id, GridDrawList & grid_draw_list)
  {
    auto & shader = g_ShaderManager.GetDefaultWorldSpaceShader();
    auto grid_box = m_DrawInfo->GetGridBoxForGridId(grid_id);

    auto grid_start = RenderVec2{ grid_box.m_Start };
    render_state.BindShader(shader);
    shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Offset"), grid_start - screen_center);
    shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Matrix"), RenderVec4{ 1, 0, 0, 1 });

    render_state.BindVertexBuffer(grid_draw_list.m_VertexBuffer);

    for (auto & draw : grid_draw_list.m_DrawElems)
    {
      render_state.BindTexture(*draw.m_Texture);
      render_state.Draw(draw.m_StartIndex, draw.m_EndIndex);
    }

    return true;
  }, false);

  std::vector<std::size_t> anim_ids;
  m_AnimSpatialDatabase->Query(viewport_bounds, anim_ids);

  for (auto id : anim_ids)
  {
    auto anim = m_AnimInfo->TryGet(id);
    if (anim && vfind(m_SelectedAnimations, id) == false)
    {
      SpriteEngineData::RenderTile(m_TileSheet, render_state, anim->m_State.m_AnimIndex, anim->m_State.m_AnimFrame, kSpriteDefaultSkin, anim->m_Position - screen_center);
    }
  }
}

void MapEditorTileManager::DrawPreviewTiles(VertexBuffer & vertex_buffer, const RenderVec2 & screen_center, RenderState & render_state, RenderUtil & render_util)
{
  for (auto & texture_data : m_Textures)
  {
    QuadVertexBufferBuilder builder;
    QuadVertexBuilderInfo quad;

    auto texture = texture_data.m_AssetLink.Get();
    if (texture == nullptr || texture->IsLoaded() == false || texture->GetWidth() <= 0 || texture->GetHeight() <= 0)
    {
      continue;
    }

    int width_in_frames = (texture->GetWidth() + texture_data.m_FrameWidth - 1) / texture_data.m_FrameWidth;

    for (auto & tile : m_PreviewTiles)
    {
      if (texture_data.m_TextureNameHash == tile.m_TextureHash)
      {
        int src_x = (tile.m_FrameId % width_in_frames) * texture_data.m_FrameWidth;
        int src_y = (tile.m_FrameId / width_in_frames) * texture_data.m_FrameHeight;

        int dst_x = tile.x - texture_data.m_FrameWidth / 2;
        int dst_y = tile.y - texture_data.m_FrameHeight / 2;

        quad.m_Position.m_Start = Vector2(dst_x, dst_y);
        quad.m_Position.m_End = quad.m_Position.m_Start + Vector2(texture_data.m_FrameWidth, texture_data.m_FrameHeight);
        quad.m_TexCoords.m_Start = Vector2(src_x, src_y);
        quad.m_TexCoords.m_End = quad.m_TexCoords.m_Start + Vector2(texture_data.m_FrameWidth, texture_data.m_FrameHeight);
        quad.m_TextureSize = Vector2(texture->GetWidth(), texture->GetHeight());
        quad.m_Color = Color(255, 255, 255, 255);
        builder.AddQuad(quad);
      }
    }

    builder.FillVertexBuffer(vertex_buffer);
    auto & shader = g_ShaderManager.GetDefaultWorldSpaceShader();
    render_state.BindShader(shader);
    shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Offset"), -screen_center);
    shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Matrix"), RenderVec4{ 1, 0, 0, 1 });
    shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), Color(255, 255, 255, 160));

    render_state.BindTexture(*texture);
    render_state.BindVertexBuffer(vertex_buffer);
    render_state.Draw();
  }

  for (auto & tile : m_PreviewAnims)
  {
    AnimationState anim_state;
    m_TileSheet.GetResource()->InitAnimation(tile.m_Animation, tile.m_FrameOffset + m_NumFrames, anim_state);

    SpriteEngineData::RenderTile(m_TileSheet, render_state, anim_state.m_AnimIndex, anim_state.m_AnimFrame, kSpriteDefaultSkin,
      Vector2(tile.x, tile.y) - screen_center, RenderVec4{ 1, 0, 0, 1 }, Color(255, 255, 255, 160));
  }
}

void MapEditorTileManager::DrawSelectedTiles(VertexBuffer & vertex_buffer, const RenderVec2 & screen_center, RenderState & render_state, RenderUtil & render_util)
{
  if (m_Map.m_ManualTileLayers.HasAt(m_LayerIndex) == false || m_InitialSyncComplete == false)
  {
    return;
  }

  LineVertexBufferBuilder line_builder;
  QuadVertexBuilderInfo quad;

  if (m_SelectedTiles.size() != 0)
  {
    auto & layer = m_Map.m_ManualTileLayers[m_LayerIndex];

    for (auto & texture_data : m_Textures)
    {
      QuadVertexBufferBuilder builder;

      auto texture = texture_data.m_AssetLink.Get();
      if (texture == nullptr || texture->IsLoaded() == false || texture->GetWidth() <= 0 || texture->GetHeight() <= 0)
      {
        continue;
      }

      int width_in_frames = (texture->GetWidth() + texture_data.m_FrameWidth - 1) / texture_data.m_FrameWidth;

      for (auto & tile_index : m_SelectedTiles)
      {
        auto & tile = layer.m_Tiles[tile_index].Value();
        if (texture_data.m_TextureNameHash == tile.m_TextureHash)
        {
          int src_x = (tile.m_FrameId % width_in_frames) * texture_data.m_FrameWidth;
          int src_y = (tile.m_FrameId / width_in_frames) * texture_data.m_FrameHeight;

          int dst_x = tile.x - texture_data.m_FrameWidth / 2 + m_SelectedTileOffset.x;
          int dst_y = tile.y - texture_data.m_FrameHeight / 2 + m_SelectedTileOffset.y;

          quad.m_Position.m_Start = Vector2(dst_x, dst_y);
          quad.m_Position.m_End = quad.m_Position.m_Start + Vector2(texture_data.m_FrameWidth, texture_data.m_FrameHeight);
          quad.m_TexCoords.m_Start = Vector2(src_x, src_y);
          quad.m_TexCoords.m_End = quad.m_TexCoords.m_Start + Vector2(texture_data.m_FrameWidth, texture_data.m_FrameHeight);
          quad.m_TextureSize = Vector2(texture->GetWidth(), texture->GetHeight());
          quad.m_Color = Color(255, 255, 255, 255);
          builder.AddQuad(quad);

          line_builder.AddBox(quad);
        }
      }

      builder.FillVertexBuffer(vertex_buffer);
      auto & shader = g_ShaderManager.GetDefaultWorldSpaceShader();
      render_state.BindShader(shader);
      shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Offset"), -screen_center);
      shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Matrix"), RenderVec4{ 1, 0, 0, 1 });
      shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), RenderVec4{ 1, 1, 1, 1 });

      render_state.BindTexture(*texture);
      render_state.BindVertexBuffer(vertex_buffer);
      render_state.Draw();
    }
  }

  if (m_SelectedAnimations.size() != 0)
  {
    for (auto id : m_SelectedAnimations)
    {
      auto anim = m_AnimInfo->TryGet(id);
      if (anim)
      {
        SpriteEngineData::RenderTile(m_TileSheet, render_state, anim->m_State.m_AnimIndex, anim->m_State.m_AnimFrame, 
          kSpriteDefaultSkin, anim->m_Position + m_SelectedAnimOffset - screen_center);

        auto anim_size = m_TileSheet.GetResource()->GetAnimationMaxSize(anim->m_State);
        auto box = Box::FromFrameCenterAndSize(anim->m_Position, anim_size);

        quad.m_Position = box;
        quad.m_Position.m_Start += m_SelectedAnimOffset;
        quad.m_Position.m_End += m_SelectedAnimOffset;
        quad.m_Color = Color(255, 255, 255, 255);
        line_builder.AddBox(quad);
      }
    }
  }

  if (line_builder.HasData())
  {
    line_builder.FillVertexBuffer(vertex_buffer);
    auto & shader = g_ShaderManager.GetDefaultWorldSpaceShader();
    render_state.BindShader(shader);
    shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Offset"), -screen_center);
    shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Matrix"), RenderVec4{ 1, 0, 0, 1 });
    shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), RenderVec4{ 1, 0, 1, 1 });

    render_state.BindTexture(render_util.GetDefaultTexture());
    render_state.BindVertexBuffer(vertex_buffer);
    render_state.Draw();
  }
}

void MapEditorTileManager::SetPreviewTiles(const std::vector<MapTile> & tiles)
{
  m_PreviewTiles = tiles;

  Optional<Box> dirty_box = m_PreviewTileBounds;

  for (auto & tile : tiles)
  {
    for (auto & tex : m_Textures)
    {
      if (tex.m_TextureNameHash == tile.m_TextureHash)
      {
        Box tile_box = Box::FromFrameCenterAndSize(Vector2(tile.x, tile.y), Vector2(tex.m_FrameWidth, tex.m_FrameHeight));

        if (dirty_box)
        {
          BoxUnionInPlace(dirty_box.Value(), tile_box);
        }
        else
        {
          dirty_box = tile_box;
        }
      }
    }
  }

  if (dirty_box)
  {
    AddToDirtyGridList(dirty_box.Value());
    m_PreviewTileBounds = dirty_box;
  }
}

void MapEditorTileManager::SetPreviewAnimations(const std::vector<MapAnimatedTile> & anims)
{
  m_PreviewAnims = anims;

  Optional<Box> dirty_box = m_PreviewAnimBounds;
  auto tile_resource = m_TileSheet.GetResource();

  for (auto & tile : anims)
  {
    auto anim_size = tile_resource->GetAnimationMaxSize(tile.m_Animation);

    Box tile_box = Box::FromFrameCenterAndSize(Vector2(tile.x, tile.y), anim_size);

    if (dirty_box)
    {
      BoxUnionInPlace(dirty_box.Value(), tile_box);
    }
    else
    {
      dirty_box = tile_box;
    }
  }

  m_PreviewAnimBounds = dirty_box;
}

void MapEditorTileManager::OffsetPreview(const Vector2 & offset)
{
  if (m_PreviewTiles.size() == 0 && m_PreviewAnims.size() == 0)
  {
    return;
  }

  for (auto & tile : m_PreviewTiles)
  {
    tile.x += offset.x;
    tile.y += offset.y;
  }

  for (auto & tile : m_PreviewAnims)
  {
    tile.x += offset.x;
    tile.y += offset.y;
  }

  if (m_PreviewTileBounds)
  {
    auto box = m_PreviewTileBounds;
    m_PreviewTileBounds->m_Start += offset;
    m_PreviewTileBounds->m_End += offset;
    BoxUnionInPlace(box.Value(), m_PreviewTileBounds.Value());

    AddToDirtyGridList(box.Value());
  }

  if (m_PreviewAnimBounds)
  {
    m_PreviewAnimBounds->m_Start += offset;
    m_PreviewAnimBounds->m_End += offset;
  }
}

void MapEditorTileManager::ClearPreviewTiles()
{
  m_PreviewTiles.clear();

  if (m_PreviewTileBounds)
  {
    auto & box = m_PreviewTileBounds.Value();
    AddToDirtyGridList(box);

    m_PreviewTileBounds.Clear();
  }

  m_PreviewAnims.clear();
  m_PreviewAnimBounds.Clear();
}

void MapEditorTileManager::ToggleHidden()
{
  m_Hidden = !m_Hidden;
}

void MapEditorTileManager::SetHidden(bool hidden)
{
  m_Hidden = hidden;
}

bool MapEditorTileManager::IsHidden()
{
  return m_Hidden;
}

void MapEditorTileManager::HandleTileSheetReload(NotNullPtr<TileSheetResource> tile_sheet)
{
  m_Textures.clear();

  m_IgnoreTextureReloads = true;

  int load_index = 0;
  for (auto elem : tile_sheet->GetData()->m_Textures)
  {
    if (elem.second.m_FrameWidth <= 0 || elem.second.m_FrameHeight <= 0)
    {
      continue;
    }

    m_Textures.emplace_back(TextureInfo{ crc32(elem.second.m_Filename.data()), elem.second.m_FrameWidth, elem.second.m_FrameHeight });

    TextureAsset::LoadWithCallback(elem.second.m_Filename.data(),
      [this, load_index](NullOptPtr<TextureAsset> tex) { HandleTextureReload(tex, load_index); }, m_Textures.back().m_AssetLink);
    
    load_index++;
  }

  m_IgnoreTextureReloads = false;

  SyncTiles(tile_sheet);
}

void MapEditorTileManager::HandleTextureReload(NullOptPtr<TextureAsset> textur, int texture_index)
{
  if (m_Map.m_ManualTileLayers.HasAt(m_LayerIndex) == false || m_InitialSyncComplete == false)
  {
    return;
  }

  if (m_IgnoreTextureReloads)
  {
    return;
  }

  RefreshTiles(m_Textures[texture_index].m_TextureNameHash);
  AddAllToDirtyGridList();
}

void MapEditorTileManager::HandleTileListChange(const ReflectionChangeNotification & change)
{
  if (m_LocalChange)
  {
    return;
  }

  auto layer = m_Map.m_ManualTileLayers.TryGet(m_LayerIndex);
  if (layer == nullptr || m_InitialSyncComplete == false)
  {
    return;
  }

  if (change.m_Type == ReflectionNotifyChangeType::kInsert)
  {
    if (layer->m_Tiles.HasAt(change.m_SubIndex) == false)
    {
      return;
    }

    auto & tile = layer->m_Tiles[change.m_SubIndex];
    auto box = GetTileBounds(tile.Value());

    m_TileLocations->EmplaceAt(change.m_SubIndex, box);
    m_TileSpatialDatabase->Insert(box, change.m_SubIndex);
    m_DrawInfo->VisitGridIds(box, [this](uint32_t grid_id) { AddToDirtyGridList(grid_id); return true; });
  }
  else if (change.m_Type == ReflectionNotifyChangeType::kRemove)
  {
    vremove_quick(m_SelectedTiles, change.m_SubIndex);

    auto box = m_TileLocations->GetAt(change.m_SubIndex);
    m_TileLocations->RemoveAt(change.m_SubIndex);
    m_TileSpatialDatabase->Remove(box, change.m_SubIndex);
    m_DrawInfo->VisitGridIds(box, [this](uint32_t grid_id) { AddToDirtyGridList(grid_id); return true; });
  }
  else
  {
    SyncTiles(m_TileSheet.GetResource());
  }
}

void MapEditorTileManager::HandleTileChildChange(const ReflectionChangeNotification & change, std::size_t index)
{
  if (m_LocalChange)
  {
    return;
  }

  RefreshTile(index);
}

void MapEditorTileManager::HandleAnimListChange(const ReflectionChangeNotification & change)
{
  if (m_LocalChange)
  {
    return;
  }

  auto layer = m_Map.m_ManualTileLayers.TryGet(m_LayerIndex);
  if (layer == nullptr || m_InitialSyncComplete == false)
  {
    return;
  }

  if (change.m_Type == ReflectionNotifyChangeType::kInsert)
  {
    if (layer->m_Animations.HasAt(change.m_SubIndex) == false)
    {
      return;
    }

    auto & tile = layer->m_Animations[change.m_SubIndex];
    auto box = GetAnimBounds(tile.Value());

    AnimationInfo anim_info;
    anim_info.m_Bounds = box;
    anim_info.m_Position = Vector2(tile->x, tile->y);
    m_TileSheet.GetResource()->InitAnimation(tile->m_Animation, tile->m_FrameOffset + m_NumFrames, anim_info.m_State);

    m_AnimInfo->EmplaceAt(change.m_SubIndex, anim_info);
    m_AnimSpatialDatabase->Insert(box, change.m_SubIndex);
  }
  else if (change.m_Type == ReflectionNotifyChangeType::kRemove)
  {
    vremove_quick(m_SelectedAnimations, change.m_SubIndex);

    auto box = m_AnimInfo->GetAt(change.m_SubIndex).m_Bounds;
    m_AnimInfo->RemoveAt(change.m_SubIndex);
    m_AnimSpatialDatabase->Remove(box, change.m_SubIndex);
  }
  else
  {
    SyncTiles(m_TileSheet.GetResource());
  }
}

void MapEditorTileManager::HandleAnimChildChange(const ReflectionChangeNotification & change, std::size_t index)
{
  if (m_LocalChange)
  {
    return;
  }

  RefreshAnimation(index);
}

void MapEditorTileManager::RefreshTile(std::size_t index)
{
  if (m_Map.m_ManualTileLayers[m_LayerIndex].m_Tiles.HasAt(index) == false || m_InitialSyncComplete == false)
  {
    return;
  }

  auto & tile = m_Map.m_ManualTileLayers[m_LayerIndex].m_Tiles[index];
  for (auto & tex : m_Textures)
  {
    if (tex.m_TextureNameHash == tile->m_TextureHash)
    {
      auto tile_size = Vector2(tex.m_FrameWidth, tex.m_FrameHeight);

      Box new_box = GetTileBounds(tile.Value(), tex);

      auto & old_box = m_TileLocations->GetAt(index);
      if (new_box == old_box)
      {
        m_DrawInfo->VisitGridIds(old_box, [this](uint32_t grid_id) { AddToDirtyGridList(grid_id); return true; });
        return;
      }

      m_TileSpatialDatabase->Remove(old_box, index);
      m_TileSpatialDatabase->Insert(new_box, index);

      m_TileLocations->GetAt(index) = new_box;

      Box combined_box = old_box;
      BoxUnionInPlace(combined_box, new_box);

      m_DrawInfo->VisitGridIds(combined_box, [this](uint32_t grid_id) { AddToDirtyGridList(grid_id); return true; });
      return;
    }
  }
}

void MapEditorTileManager::RefreshTiles(uint32_t texture_hash)
{
  if (m_Map.m_ManualTileLayers.HasAt(m_LayerIndex) == false || m_InitialSyncComplete == false)
  {
    return;
  }

  std::vector<std::size_t> dead_tiles;
  std::vector<std::pair<std::size_t, Box>> new_tiles;

  Optional<Box> new_tiles_box;
  Optional<Box> dead_tiles_box;

  for (auto & tex : m_Textures)
  {
    if (tex.m_TextureNameHash == texture_hash)
    {
      auto tile_size = Vector2(tex.m_FrameWidth, tex.m_FrameHeight);

      for (auto elem : m_Map.m_ManualTileLayers[m_LayerIndex].m_Tiles)
      {
        auto & tile = elem.second.Value();

        if (tile.m_TextureHash == texture_hash)
        {
          Box new_box = GetTileBounds(tile, tex);

          auto & old_box = m_TileLocations->GetAt(elem.first);
          if (new_box == old_box)
          {
            continue;
          }

          if (!new_tiles_box)
          {
            new_tiles_box = new_box;
          }
          else
          {
            BoxUnionInPlace(new_tiles_box.Value(), new_box);
          }

          if (!dead_tiles_box)
          {
            dead_tiles_box = old_box;
          }
          else
          {
            BoxUnionInPlace(dead_tiles_box.Value(), old_box);
          }

          dead_tiles.emplace_back(elem.first);
          new_tiles.emplace_back(std::make_pair(elem.first, new_box));

          old_box = new_box;
        }
      }
    }
  }

  if (dead_tiles.size() > 0)
  {
    m_TileSpatialDatabase->RemoveBatch(dead_tiles_box.Value(), dead_tiles);
    m_TileSpatialDatabase->InsertBatch(new_tiles_box.Value(), new_tiles);
  }
}

void MapEditorTileManager::RefreshAnimation(std::size_t index)
{
  if (m_Map.m_ManualTileLayers[m_LayerIndex].m_Animations.HasAt(index) == false || m_InitialSyncComplete == false)
  {
    return;
  }

  auto & tile = m_Map.m_ManualTileLayers[m_LayerIndex].m_Animations[index];
  Box new_box = GetAnimBounds(tile.Value());

  auto & tile_info = m_AnimInfo->GetAt(index);
  m_TileSheet.GetResource()->InitAnimation(tile->m_Animation, tile->m_FrameOffset, tile_info.m_State);

  m_AnimSpatialDatabase->Remove(tile_info.m_Bounds, index);
  m_AnimSpatialDatabase->Insert(new_box, index);

  tile_info.m_Bounds = new_box;
}

Optional<Box> MapEditorTileManager::GetMultiTileBounds(const std::vector<std::size_t> & tiles)
{
  if (m_Map.m_ManualTileLayers.HasAt(m_LayerIndex) == false || m_InitialSyncComplete == false)
  {
    return{};
  }

  Optional<Box> bounds;

  for (auto index : tiles)
  {
    auto & tile = m_Map.m_ManualTileLayers[m_LayerIndex].m_Tiles[index].Value();
    Box tile_box = GetTileBounds(tile);

    if (bounds == false)
    {
      bounds.Emplace(tile_box);
    }
    else
    {
      BoxUnionInPlace(bounds.Value(), tile_box);
    }
  }

  return bounds;
}

Optional<Box> MapEditorTileManager::GetMultiAnimBounds(const std::vector<std::size_t> & tiles)
{
  if (m_Map.m_ManualTileLayers.HasAt(m_LayerIndex) == false || m_InitialSyncComplete == false)
  {
    return{};
  }

  Optional<Box> bounds;

  for (auto index : tiles)
  {
    auto & tile = m_Map.m_ManualTileLayers[m_LayerIndex].m_Animations[index].Value();
    Box tile_box = GetAnimBounds(tile);

    if (bounds == false)
    {
      bounds.Emplace(tile_box);
    }
    else
    {
      BoxUnionInPlace(bounds.Value(), tile_box);
    }
  }

  return bounds;
}

void MapEditorTileManager::AddToDirtyGridList(const Box & box)
{
  if (m_Map.m_ManualTileLayers.HasAt(m_LayerIndex) == false || m_InitialSyncComplete == false)
  {
    return;
  }

  m_TileSpatialDatabase->VisitGridIds(box, [&](uint32_t grid_id) { AddToDirtyGridList(grid_id); return true; });
}

void MapEditorTileManager::AddToDirtyGridList(uint32_t grid_id)
{
  if (m_Map.m_ManualTileLayers.HasAt(m_LayerIndex) == false || m_InitialSyncComplete == false)
  {
    return;
  }

  if (vfind(m_DirtyGrids.Value(), grid_id) == false)
  {
    m_DirtyGrids->push_back(grid_id);
  }
}

void MapEditorTileManager::AddAllToDirtyGridList()
{
  if (m_Map.m_ManualTileLayers.HasAt(m_LayerIndex) == false || m_InitialSyncComplete == false)
  {
    return;
  }

  m_DirtyGrids->clear();
  m_TileSpatialDatabase->VisitAll([&](uint32_t grid_id, auto & node) { m_DirtyGrids->push_back(grid_id); });
}

bool MapEditorTileManager::IsTileInPreview(const MapTile & tile)
{
  for (auto & preview_tile : m_PreviewTiles)
  {
    if (preview_tile.x == tile.x && preview_tile.y == tile.y && preview_tile.m_TextureHash == tile.m_TextureHash)
    {
      return true;
    }
  }

  return false;
}

Box MapEditorTileManager::GetTileBounds(const MapTile & tile)
{
  for (auto & tex : m_Textures)
  {
    if (tex.m_TextureNameHash == tile.m_TextureHash)
    {
      return GetTileBounds(tile, tex);
    }
  }

  return Box::FromPoint(Vector2(tile.x, tile.y));
}

Box MapEditorTileManager::GetTileBounds(const MapTile & tile, TextureInfo & tex)
{
  return Box::FromFrameCenterAndSize(Vector2(tile.x, tile.y), Vector2(tex.m_FrameWidth, tex.m_FrameHeight));
}

Box MapEditorTileManager::GetAnimBounds(const MapAnimatedTile & tile)
{
  return Box::FromFrameCenterAndSize(Vector2(tile.x, tile.y), m_TileSheet.GetResource()->GetAnimationMaxSize(tile.m_Animation));
}
