

#include "StormData/StormDataJson.h"

#include "Foundation/BasicTypes/BasicTypeFuncs.h"

#include "Runtime/Map/MapTileJson.h"

#include "Engine/Rendering/VertexBufferBuilder.h"
#include "Engine/Rendering/RenderUtil.h"
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
  m_Watcher(m_Editor),
  m_LocalChange(false),
  m_Hidden(false)
{
  auto layer_path = ".m_ManualTileLayers[" + std::to_string(m_LayerIndex) + "].m_Tiles";
  m_Watcher.SetPath(layer_path.data(), false, true, [=] { return m_Map.m_ManualTileLayers.HasAt(layer_index); });
  m_Watcher.SetChangeCallback([=](const ReflectionChangeNotification & change) { HandleListChange(change); });
  m_Watcher.SetChildChangeCallback([=](const ReflectionChangeNotification & change, std::size_t index) { HandleChildChange(change, index); });

  SyncTileSheet();
}

void MapEditorTileManager::SyncTiles()
{
  m_SelectedTileOffset = {};
  m_SelectedTiles.clear();

  if (m_Map.m_ManualTileLayers.HasAt(m_LayerIndex) == false)
  {
    return;
  }

  m_TileLocations.Emplace();
  m_TileLocations->Reserve((m_Map.m_ManualTileLayers[m_LayerIndex].m_Tiles.HighestIndex() + 2) * 2);

  m_SpatialDatabase.Emplace();

  Optional<Box> map_extents;

  std::vector<std::size_t> used_indices;
  std::vector<std::pair<std::size_t, Box>> tiles;
  for (auto elem : m_Map.m_ManualTileLayers[m_LayerIndex].m_Tiles)
  {
    Box tile_box = GetTileBounds(elem.second.Value());

    if (map_extents == false)
    {
      map_extents.Emplace(tile_box);
    }
    else
    {
      BoxUnionInPlace(map_extents.Value(), tile_box);
    }

    m_TileLocations->EmplaceAt(elem.first, tile_box);
    used_indices.push_back(elem.first);
    tiles.emplace_back(std::make_pair(elem.first, tile_box));
  }

  if (map_extents)
  {
    m_SpatialDatabase->InsertBatch(map_extents.Value(), tiles);
  }

  m_IdAllocator.Emplace(used_indices.size() * 2, used_indices);

  m_DirtyGrids.Emplace();
  m_SpatialDatabase->VisitAll([&](uint32_t grid_id, auto & node) { m_DirtyGrids->push_back(grid_id); });

  m_RecreateDrawInfo = true;
  m_InitialSyncComplete = true;
}

void MapEditorTileManager::SyncTileSheet()
{
  if (m_Map.m_ManualTileLayers.HasAt(m_LayerIndex) == false)
  {
    return;
  }

  m_TileSheet = TileSheetResource::LoadWithCallback(m_Map.m_ManualTileLayers[m_LayerIndex].m_TileSheet.data(),
    [this](NotNullPtr<TileSheetResource> resource) { HandleTileSheetReload(resource); });
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
  m_SpatialDatabase->Query(check_box, existing_tiles);

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

  auto id = m_IdAllocator->Allocate();

  m_LocalChange = true;
  m_Editor->DisableChangeCallbacks();
  layer.m_Tiles.EmplaceAt(id, tile);
  m_Editor->EnableChangeCallbacks();
  m_LocalChange = false;

  m_TileLocations->EmplaceAt(id, box);

  m_SpatialDatabase->Insert(box, id);
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
  m_SpatialDatabase->Query(bounds, existing_tiles);

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
  m_SpatialDatabase->InsertBatch(bounds, new_tile_boxes);

  if (new_tiles.size() > 0)
  {
    Optional<Box> new_tile_bounds;

    for (auto tile_index : new_tiles)
    {
      auto & new_tile = m_PreviewTiles[tile_index];
      auto id = m_IdAllocator->Allocate();
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

    m_SpatialDatabase->InsertBatch(new_tile_bounds.Value(), new_tile_boxes);
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

  auto old_bounds = GetTileBounds(m_SelectedTiles);
  if (old_bounds)
  {
    AddToDirtyGridList(old_bounds.Value());
  }

  m_SelectedTiles.clear();
  m_SpatialDatabase->Query(box, m_SelectedTiles);
  m_SelectedTileOffset = {};

  if (m_SelectedTiles.size() > 0)
  {
    auto bounds = GetTileBounds(m_SelectedTiles).Value();
    if (old_bounds)
    {
      BoxUnionInPlace(bounds, old_bounds.Value());
    }

    AddToDirtyGridList(bounds);
  }
}

void MapEditorTileManager::ClearSelection()
{
  if (m_SelectedTiles.size() > 0)
  {
    auto bounds = GetTileBounds(m_SelectedTiles).Value();
    AddToDirtyGridList(bounds);

    m_SelectedTiles.clear();
    m_SelectedTileOffset = {};
  }
}

void MapEditorTileManager::DeleteSelectedTiles()
{
  if (m_Map.m_ManualTileLayers.HasAt(m_LayerIndex) == false || m_InitialSyncComplete == false)
  {
    return;
  }

  auto & layer = m_Map.m_ManualTileLayers[m_LayerIndex];
  auto bounds = GetTileBounds(m_SelectedTiles).Value();

  m_LocalChange = true;
  m_Editor->BeginTransaction();
  m_Editor->DisableChangeCallbacks();

  for (auto sel_tile : m_SelectedTiles)
  {
    layer.m_Tiles.RemoveAt(sel_tile);
    m_TileLocations->RemoveAt(sel_tile);
  }

  m_SpatialDatabase->RemoveBatch(bounds, m_SelectedTiles);
  m_SelectedTiles.clear();

  m_Editor->EnableChangeCallbacks();
  m_Editor->CommitChanges();
  m_LocalChange = false;

  AddToDirtyGridList(bounds);
}

void MapEditorTileManager::SetSelectedTileOffset(const Vector2 & offset)
{
  if (m_Map.m_ManualTileLayers.HasAt(m_LayerIndex) == false || m_InitialSyncComplete == false)
  {
    return;
  }

  m_SelectedTileOffset = offset;
}

void MapEditorTileManager::CommitSelectedTileOffset()
{
  if (m_SelectedTiles.size() == 0)
  {
    return;
  }

  if (m_Map.m_ManualTileLayers.HasAt(m_LayerIndex) == false || m_InitialSyncComplete == false)
  {
    return;
  }

  if (m_SelectedTileOffset.x == 0 && m_SelectedTileOffset.y == 0)
  {
    return;
  }

  auto & layer = m_Map.m_ManualTileLayers[m_LayerIndex];

  auto bounds = GetTileBounds(m_SelectedTiles).Value();

  std::vector<std::size_t> existing_tiles;
  m_SpatialDatabase->Query(bounds, existing_tiles);

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

  m_LocalChange = true;
  m_Editor->BeginTransaction();
  m_Editor->DisableChangeCallbacks();

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

  m_Editor->EnableChangeCallbacks();
  m_Editor->CommitChanges();
  m_LocalChange = false;

  auto new_bounds = GetTileBounds(m_SelectedTiles).Value();
  m_SpatialDatabase->RemoveBatch(bounds, removed_tiles);
  m_SpatialDatabase->RemoveBatch(bounds, m_SelectedTiles);
  m_SpatialDatabase->InsertBatch(new_bounds, tile_locations);
  BoxUnionInPlace(bounds, new_bounds);

  AddToDirtyGridList(bounds);

  m_SelectedTileOffset = {};
}

Optional<MapTile> MapEditorTileManager::FindTile(const Vector2 & pos)
{
  if (m_Map.m_ManualTileLayers.HasAt(m_LayerIndex) == false || m_InitialSyncComplete == false)
  {
    return{};
  }

  Box b = { pos, pos };

  std::size_t outp_index;
  if (m_SpatialDatabase->QueryAny(b, outp_index))
  {
    return m_Map.m_ManualTileLayers[m_LayerIndex].m_Tiles[outp_index].Value();
  }

  return{};
}

bool MapEditorTileManager::IsOnSelectedTile(const Vector2 & pos)
{
  if (m_Map.m_ManualTileLayers.HasAt(m_LayerIndex) == false || m_InitialSyncComplete == false)
  {
    return false;
  }

  if (m_SelectedTiles.size() == 0)
  {
    return false;
  }

  Box b = { pos, pos };

  std::vector<std::size_t> outp_indices;
  m_SpatialDatabase->Query(b, outp_indices);

  for (auto & index : m_SelectedTiles)
  {
    if (vfind(outp_indices, index))
    {
      return true;
    }
  }

  return false;
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
    m_SpatialDatabase->RemoveBatch(dead_tiles_box.Value(), tiles);
    m_DrawInfo->VisitGridIds(dead_tiles_box.Value(), [this](uint32_t grid_id) { AddToDirtyGridList(grid_id); return true; });
  }
}

void MapEditorTileManager::Draw(const Box & viewport_bounds, const RenderVec2 & screen_center)
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
    m_DrawInfo->VisitNode(grid_id, [&](const Box & bounding_box, std::vector<GridDrawElement> & grid_elems) {
      
      grid_elems.clear();

      std::vector<std::size_t> tile_indices;
      m_SpatialDatabase->Query(bounding_box, tile_indices);

      std::vector<MapTile> tiles;
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

        tiles.push_back(tile);
      }

      std::sort(tiles.begin(), tiles.end(), [](const MapTile & a, const MapTile & b) { return a.m_TextureHash < b.m_TextureHash; });
      std::vector<std::pair<uint32_t, std::vector<MapTile>>> draw_buckets;

      uint32_t last_texture = 0;
      for (auto & tile : tiles)
      {
        if (tile.m_TextureHash == 0)
        {
          continue;
        }

        if (tile.m_TextureHash != last_texture)
        {
          draw_buckets.emplace_back(std::make_pair(tile.m_TextureHash, std::vector<MapTile>{}));
          last_texture = tile.m_TextureHash;
        }

        draw_buckets.back().second.emplace_back(tile);
      }

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

        GridDrawElement draw_element{ texture };
        QuadVertexBufferBuilder builder;

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
          builder.AddQuad(quad);
        }

        builder.SliceVertexBuffer(Box{ Vector2{0, 0}, Vector2{1023, 1023} });
        builder.FillVertexBuffer(draw_element.m_VertexBuffer);

        grid_elems.emplace_back(std::move(draw_element));
      }

    }, true);
  }

  m_DirtyGrids->clear();

  m_DrawInfo->VisitGrid(viewport_bounds, [&](uint32_t grid_id, std::vector<GridDrawElement> & grid_elems)
  {
    auto & shader = g_ShaderManager.GetDefaultShader();
    auto grid_box = m_DrawInfo->GetGridBoxForGridId(grid_id);

    auto grid_start = RenderVec2{ grid_box.m_Start };
    shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Offset"), grid_start - screen_center);
    shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Matrix"), RenderVec4{ 1, 0, 0, 1 });

    for (auto & draw : grid_elems)
    {
      draw.m_Texture->GetTexture().BindTexture(0);
      draw.m_VertexBuffer.Bind();
      
      draw.m_VertexBuffer.CreateDefaultBinding(shader);
      draw.m_VertexBuffer.Draw();
      draw.m_VertexBuffer.Unbind();
    }

    return true;
  }, false);
}

void MapEditorTileManager::DrawPreviewTiles(VertexBuffer & vertex_buffer, const RenderVec2 & screen_center)
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
    auto & shader = g_ShaderManager.GetDefaultShader();
    shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Offset"), -screen_center);
    shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Matrix"), RenderVec4{ 1, 0, 0, 1 });
    texture->GetTexture().BindTexture(0);

    vertex_buffer.Bind();

    vertex_buffer.CreateDefaultBinding(shader);
    vertex_buffer.Draw();
    vertex_buffer.Unbind();
  }
}

void MapEditorTileManager::DrawSelectedTiles(VertexBuffer & vertex_buffer, const RenderVec2 & screen_center, RenderUtil & render_util)
{
  if (m_Map.m_ManualTileLayers.HasAt(m_LayerIndex) == false || m_InitialSyncComplete == false)
  {
    return;
  }

  if (m_SelectedTiles.size() == 0)
  {
    return;
  }

  auto & layer = m_Map.m_ManualTileLayers[m_LayerIndex];

  LineVertexBufferBuilder line_builder;

  QuadVertexBuilderInfo quad;

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
    auto & shader = g_ShaderManager.GetDefaultShader();
    shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Offset"), -screen_center);
    shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Matrix"), RenderVec4{ 1, 0, 0, 1 });
    shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), RenderVec4{ 1, 1, 1, 1 });
    texture->GetTexture().BindTexture(0);

    vertex_buffer.Bind();

    vertex_buffer.CreateDefaultBinding(shader);
    vertex_buffer.Draw();
    vertex_buffer.Unbind();
  }

  line_builder.FillVertexBuffer(vertex_buffer);
  auto & shader = g_ShaderManager.GetDefaultShader();
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Offset"), -screen_center);
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Matrix"), RenderVec4{ 1, 0, 0, 1 });
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), RenderVec4{ 1, 0, 1, 1 });
  render_util.GetDefaultTexture().BindTexture(0);

  vertex_buffer.Bind();

  vertex_buffer.CreateDefaultBinding(shader);
  vertex_buffer.Draw();
  vertex_buffer.Unbind();
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

void MapEditorTileManager::ClearPreviewTiles()
{
  m_PreviewTiles.clear();

  if (m_PreviewTileBounds)
  {
    auto & box = m_PreviewTileBounds.Value();
    AddToDirtyGridList(box);

    m_PreviewTileBounds.Clear();
  }
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

    m_Textures.emplace_back(TextureInfo{ crc32(elem.second.m_Filename.data()), elem.second.m_FrameWidth, elem.second.m_FrameHeight,
      TextureAsset::LoadWithCallback(elem.second.m_Filename.data(), [this, load_index](NullOptPtr<TextureAsset> tex) {HandleTextureReload(tex, load_index); }) });

    load_index++;
  }

  m_IgnoreTextureReloads = false;

  SyncTiles();
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

void MapEditorTileManager::HandleListChange(const ReflectionChangeNotification & change)
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
    m_SpatialDatabase->Insert(box, change.m_SubIndex);
    m_DrawInfo->VisitGridIds(box, [this](uint32_t grid_id) { AddToDirtyGridList(grid_id); return true; });
  }
  else if (change.m_Type == ReflectionNotifyChangeType::kRemove)
  {
    vremove_quick(m_SelectedTiles, change.m_SubIndex);

    auto box = m_TileLocations->GetAt(change.m_SubIndex);
    m_TileLocations->RemoveAt(change.m_SubIndex);
    m_SpatialDatabase->Remove(box, change.m_SubIndex);
    m_DrawInfo->VisitGridIds(box, [this](uint32_t grid_id) { AddToDirtyGridList(grid_id); return true; });
  }
  else
  {
    SyncTiles();
  }
}

void MapEditorTileManager::HandleChildChange(const ReflectionChangeNotification & change, std::size_t index)
{
  if (m_LocalChange)
  {
    return;
  }

  RefreshTile(index);
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

      m_SpatialDatabase->Remove(old_box, index);
      m_SpatialDatabase->Insert(new_box, index);

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
    m_SpatialDatabase->RemoveBatch(dead_tiles_box.Value(), dead_tiles);
    m_SpatialDatabase->InsertBatch(new_tiles_box.Value(), new_tiles);
  }
}

Optional<Box> MapEditorTileManager::GetTileBounds(const std::vector<std::size_t> & tiles)
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

void MapEditorTileManager::AddToDirtyGridList(const Box & box)
{
  if (m_Map.m_ManualTileLayers.HasAt(m_LayerIndex) == false || m_InitialSyncComplete == false)
  {
    return;
  }

  m_SpatialDatabase->VisitGridIds(box, [&](uint32_t grid_id) { AddToDirtyGridList(grid_id); return true; });
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
  m_SpatialDatabase->VisitAll([&](uint32_t grid_id, auto & node) { m_DirtyGrids->push_back(grid_id); });
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
