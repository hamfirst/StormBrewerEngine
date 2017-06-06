
#include "Engine/EngineCommon.h"
#include "Engine/Map/MapManualTileLayerInstance.h"
#include "Engine/Rendering/VertexBufferBuilder.h"
#include "Engine/Shader/ShaderManager.h"

#include "Runtime/TileSheet/TileSheetResource.h"

struct TextureInfo
{
  uint32_t m_TextureNameHash;
  int m_FrameWidth;
  int m_FrameHeight;
  AssetReference<TextureAsset> m_AssetRef;
};

MapManualTileLayerInstance::MapManualTileLayerInstance(MapDef & map, std::size_t layer_index)
{
  auto & layer = map.m_ManualTileLayers[(int)layer_index];
  m_LayerOrder = layer.m_LayerOrder;

  if (layer.m_TileSheet.length() == 0)
  {
    return;
  }

  TileSheet tile_sheet = TileSheetResource::Load(layer.m_TileSheet.data());
  if (tile_sheet.GetResource()->IsLoaded() == false)
  {
    return;
  }

  std::vector<TextureInfo> textures;
  for (auto elem : tile_sheet->m_Textures)
  {
    if (elem.second.m_FrameWidth <= 0 || elem.second.m_FrameHeight <= 0)
    {
      continue;
    }

    textures.emplace_back(TextureInfo{ 
      crc32(elem.second.m_Filename.data()), elem.second.m_FrameWidth, elem.second.m_FrameHeight,
      TextureAsset::Load(elem.second.m_Filename.data()) });
  }

  SpatialDatabase tile_database;
  Optional<Box> map_extents;

  std::vector<std::pair<std::size_t, Box>> tiles;
  for (auto elem : map.m_ManualTileLayers[(int)layer_index].m_Tiles)
  {
    Box tile_box;
    auto & tile = elem.second.Value();

    bool found_tex = false;
    for (auto & tex : textures)
    {
      if (tex.m_TextureNameHash == tile.m_TextureHash)
      {
        found_tex = true;
        auto tile_size = Vector2(tex.m_FrameWidth, tex.m_FrameHeight);

        tile_box.m_Start = Vector2(tile.x, tile.y) - tile_size / 2;
        tile_box.m_End = tile_box.m_Start + tile_size - Vector2(1, 1);
      }
    }

    if (found_tex == false)
    {
      tile_box = Box{ Vector2{ tile.x, tile.y }, Vector2{ tile.x, tile.y } };
    }

    if (map_extents == false)
    {
      map_extents.Emplace(tile_box);
    }
    else
    {
      BoxUnionInPlace(map_extents.Value(), tile_box);
    }

    tiles.emplace_back(std::make_pair(elem.first, tile_box));
  }

  if (map_extents)
  {
    tile_database.InsertBatch(map_extents.Value(), tiles);
  }

  tile_database.VisitAll([&](uint32_t grid_id, SpatialDatabaseNode & node) {

    auto bounding_box = tile_database.GetGridBoxForGridId(grid_id);
    auto & tile_indices = node.m_Elements;

    std::vector<MapTile> tiles;
    for (auto tile_index : tile_indices)
    {
      tiles.push_back(layer.m_Tiles[tile_index.first].Value());
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
      for (int index = 0, end = (int)textures.size(); index < end; ++index)
      {
        if (textures[index].m_TextureNameHash == bucket.first)
        {
          texture_index = index;
          break;
        }
      }

      if (texture_index == -1)
      {
        continue;
      }

      auto texture = textures[texture_index].m_AssetRef.Resolve();
      if (texture == nullptr || texture->IsLoaded() == false || texture->GetWidth() <= 0 || texture->GetHeight() <= 0)
      {
        continue;
      }

      auto & texture_data = textures[texture_index];
      int width_in_frames = (texture->GetWidth() + texture_data.m_FrameWidth - 1) / texture_data.m_FrameWidth;

      GridDrawElement draw_element{ AssetReference<TextureAsset>(texture), VertexBuffer{} };
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

      builder.SliceVertexBuffer(Box{ Vector2{ 0, 0 }, Vector2{ 1023, 1023 } });
      builder.FillVertexBuffer(draw_element.m_VertexBuffer);     

      m_DrawInfo.VisitNode(grid_id, [&](Box b, auto & elem_list)
      {
        elem_list.emplace_back(std::move(draw_element));
      }, true);
    }

  });

}

void MapManualTileLayerInstance::Draw(const Box & viewport_bounds, const RenderVec2 & screen_center)
{
  m_DrawInfo.VisitGrid(viewport_bounds, [&](uint32_t grid_id, std::vector<GridDrawElement> & grid_elems)
  {
    auto & shader = g_ShaderManager.GetDefaultShader();
    auto grid_box = m_DrawInfo.GetGridBoxForGridId(grid_id);

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

int MapManualTileLayerInstance::GetLayerOrder() const
{
  return m_LayerOrder;
}
