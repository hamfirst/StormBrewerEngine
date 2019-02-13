
#include "Engine/EngineCommon.h"
#include "Engine/Map/MapManualTileLayerInstance.h"
#include "Engine/Rendering/VertexBufferBuilder.h"
#include "Engine/Rendering/RenderState.h"
#include "Engine/Shader/ShaderManager.h"
#include "Engine/Profiler/Profiler.h"
#include "Engine/Sprite/SpriteEngineData.h"

#include "Runtime/TileSheet/TileSheetResource.h"

MapManualTileLayerInstance::MapManualTileLayerInstance(MapDef & map, std::size_t layer_index, const Vector2 & offset)
{
  auto & layer = map.m_ManualTileLayers[(int)layer_index];
  m_LayerOrder = layer.m_LayerOrder;

  if (layer.m_TileSheet.length() == 0)
  {
    return;
  }

  auto tile_sheet = TileSheetResource::Load(layer.m_TileSheet.data());
  if (tile_sheet.GetResource()->IsLoaded() == false)
  {
    return;
  }

  for (auto tile : layer.m_Tiles)
  {
    auto tile_copy = tile.second.Value();
    tile_copy.x += offset.x;
    tile_copy.y += offset.y;

    m_Tiles.push_back(tile.second.Value());
  }

  for (auto anim : layer.m_Animations)
  {
    auto & tile_info = anim.second;
   
    AnimatedTile anim_tile;
    if (tile_sheet.GetResource()->InitAnimation(anim.second->m_Animation, anim.second->m_FrameOffset, anim_tile.m_State))
    {
      anim_tile.m_Position = Vector2(anim.second->x, anim.second->y) + offset;
      m_AnimatedTiles.push_back(anim_tile);
    }
  }

  m_TileSheet = tile_sheet.GetResource()->AddLoadCallback([this](NotNullPtr<TileSheetResource>) { CreateVertexBuffers(); });
  m_Initializing = false;

  LoadTextures();
}

void MapManualTileLayerInstance::LoadTextures()
{
  if (m_Initializing)
  {
    return;
  }

  m_Initializing = true;

  auto prev_texutres = std::move(m_Textures);
  auto tile_sheet_data = m_TileSheet->GetData();

  for (auto elem : tile_sheet_data->m_Textures)
  {
    if (elem.second.m_FrameWidth <= 0 || elem.second.m_FrameHeight <= 0)
    {
      continue;
    }

    m_Textures.emplace_back(TextureInfo{
      crc32(elem.second.m_Filename.data()), elem.second.m_FrameWidth, elem.second.m_FrameHeight,
      TextureAsset::LoadWithCallback(elem.second.m_Filename.data(), [this](NullOptPtr<TextureAsset>) { CreateVertexBuffers(); }) });
  }

  m_Initializing = false;
  CreateVertexBuffers();
}

void MapManualTileLayerInstance::CreateVertexBuffers()
{
  if (m_Initializing)
  {
    return;
  }

  m_Initializing = true;

  SpatialDatabase tile_database;
  Optional<Box> map_extents;

  std::vector<std::pair<std::size_t, Box>> tiles;
  for(std::size_t index = 0, end = m_Tiles.size(); index < end; ++index)
  {
    Box tile_box;
    auto & tile = m_Tiles[index];

    bool found_tex = false;
    for (auto & tex : m_Textures)
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
      tile_box = Box::FromPoint(Vector2(tile.x, tile.y));
    }

    if (map_extents == false)
    {
      map_extents.Emplace(tile_box);
    }
    else
    {
      BoxUnionInPlace(map_extents.Value(), tile_box);
    }

    tiles.emplace_back(std::make_pair(index, tile_box));
  }

  if (map_extents)
  {
    tile_database.InsertBatch(map_extents.Value(), tiles);
  }

  QuadVertexBufferBuilder builder;
  int start_index = 0;

  tile_database.VisitAll([&](uint32_t grid_id, SpatialDatabaseNode & node) {

    auto bounding_box = tile_database.GetGridBoxForGridId(grid_id);
    auto & tile_indices = node.m_Elements;

    struct TileSortInfo
    {
      MapTile m_Tile;
      bool m_Dynamic;
      int m_LowerEdge;
      int m_X;
    };

    std::vector<TileSortInfo> tiles;

    for (auto tile_index : tile_indices)
    {
      auto & tile = m_Tiles[tile_index.first];

      Optional<Box> tile_bounds;
      for (auto & tex : m_Textures)
      {
        if (tex.m_TextureNameHash == tile.m_TextureHash)
        {
          tile_bounds = Box::FromFrameCenterAndSize(Vector2(tile.x, tile.y), Vector2(tex.m_FrameWidth, tex.m_FrameHeight));
          break;
        }
      }

      if (tile_bounds == false)
      {
        continue;
      }

      auto lower_edge_offset = m_TileSheet.GetResource()->GetLowerEdgeOffset(tile.GetTileId());
      tiles.push_back(TileSortInfo{ tile, lower_edge_offset != 0, tile_bounds->m_End.y + lower_edge_offset, tile_bounds->m_Start.x });
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

    std::vector<std::pair<uint32_t, std::vector<TileSortInfo>>> draw_buckets;
    uint32_t last_texture = 0;

#ifdef USE_Z_ORDERING
    std::vector<std::pair<uint32_t, std::vector<TileSortInfo>>> draw_buckets_dynamic;
    uint32_t last_dynamic_texture = 0;
    int last_lower_edge = 0;
#endif

    for (auto & tile : tiles)
    {
      if (tile.m_Tile.m_TextureHash == 0)
      {
        continue;
      }

#ifdef USE_Z_ORDERING
      if (tile.m_Dynamic)
      {
        if (tile.m_Tile.m_TextureHash != last_dynamic_texture || tile.m_LowerEdge != last_lower_edge)
        {
          draw_buckets_dynamic.emplace_back(std::make_pair(tile.m_Tile.m_TextureHash, std::vector<TileSortInfo>{}));
          last_dynamic_texture = tile.m_Tile.m_TextureHash;
          last_lower_edge = tile.m_LowerEdge;
        }

        draw_buckets_dynamic.back().second.emplace_back(tile);
      }
      else
      {
        if (tile.m_Tile.m_TextureHash != last_texture)
        {
          draw_buckets.emplace_back(std::make_pair(tile.m_Tile.m_TextureHash, std::vector<TileSortInfo>{}));
          last_texture = tile.m_Tile.m_TextureHash;
        }

        draw_buckets.back().second.emplace_back(tile);
      }
#else
      if (tile.m_Tile.m_TextureHash != last_texture)
      {
        draw_buckets.emplace_back(std::make_pair(tile.m_Tile.m_TextureHash, std::vector<TileSortInfo>{}));
        last_texture = tile.m_Tile.m_TextureHash;
      }

      draw_buckets.back().second.emplace_back(tile);
#endif
    }

    auto slice_box = Box{ Vector2{ 0, 0 }, Vector2{ 1024, 1024 } };

    for (auto & bucket : draw_buckets)
    {
      auto bucket_texture_hash = bucket.first;

      int texture_index = -1;
      for (int index = 0, end = (int)m_Textures.size(); index < end; ++index)
      {
        if (m_Textures[index].m_TextureNameHash == bucket_texture_hash)
        {
          texture_index = index;
          break;
        }
      }

      if (texture_index == -1)
      {
        continue;
      }

      auto & texture_data = m_Textures[texture_index];
      auto texture = texture_data.m_Asset.Get();
      if (texture == nullptr || texture->IsLoaded() == false || texture->GetWidth() <= 0 || texture->GetHeight() <= 0)
      {
        continue;
      }

      int width_in_frames = (texture->GetWidth() + texture_data.m_FrameWidth - 1) / texture_data.m_FrameWidth;
      GridDrawElement draw_element{ AssetReference<TextureAsset>(texture), start_index };

      for (auto & tile : bucket.second)
      {
        int src_x = (tile.m_Tile.m_FrameId % width_in_frames) * texture_data.m_FrameWidth;
        int src_y = (tile.m_Tile.m_FrameId / width_in_frames) * texture_data.m_FrameHeight;

        int dst_x = tile.m_Tile.x - bounding_box.m_Start.x - texture_data.m_FrameWidth / 2;
        int dst_y = tile.m_Tile.y - bounding_box.m_Start.y - texture_data.m_FrameHeight / 2;

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

      m_DrawInfo.VisitNode(grid_id, [&](Box b, auto & elem_list)
      {
        elem_list.emplace_back(std::move(draw_element));
      }, true);
    }

#ifdef USE_Z_ORDERING
    for (auto & bucket : draw_buckets_dynamic)
    {
      auto bucket_texture_hash = bucket.first;

      int texture_index = -1;
      for (int index = 0, end = (int)m_Textures.size(); index < end; ++index)
      {
        if (m_Textures[index].m_TextureNameHash == bucket_texture_hash)
        {
          texture_index = index;
          break;
        }
      }

      if (texture_index == -1)
      {
        continue;
      }

      auto & texture_data = m_Textures[texture_index];
      auto texture = texture_data.m_Asset.Get();
      if (texture == nullptr || texture->IsLoaded() == false || texture->GetWidth() <= 0 || texture->GetHeight() <= 0)
      {
        continue;
      }

      int width_in_frames = (texture->GetWidth() + texture_data.m_FrameWidth - 1) / texture_data.m_FrameWidth;
      GridDrawDynamicElement draw_element{ AssetReference<TextureAsset>(texture), bucket.second[0].m_LowerEdge, start_index };

      for (auto & tile : bucket.second)
      {
        int src_x = (tile.m_Tile.m_FrameId % width_in_frames) * texture_data.m_FrameWidth;
        int src_y = (tile.m_Tile.m_FrameId / width_in_frames) * texture_data.m_FrameHeight;

        int dst_x = tile.m_Tile.x - bounding_box.m_Start.x - texture_data.m_FrameWidth / 2;
        int dst_y = tile.m_Tile.y - bounding_box.m_Start.y - texture_data.m_FrameHeight / 2;

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

      m_DynamicDrawInfo.VisitNode(grid_id, [&](Box b, auto & elem_list)
      {
        elem_list.emplace_back(std::move(draw_element));
      }, true);
    }
#endif

  });

  builder.FillVertexBuffer(m_VertexBuffer);
  m_Initializing = false;

}

void MapManualTileLayerInstance::Update()
{
  auto tile_sheet = m_TileSheet.GetResource();
  if (tile_sheet != nullptr)
  {
    for (auto & anim : m_AnimatedTiles)
    {
      tile_sheet->FrameAdvance(anim.m_State);
    }
  }
}

void MapManualTileLayerInstance::Draw(const Box & viewport_bounds, const RenderVec2 & screen_center, RenderState & render_state)
{
  PROFILE_SCOPE("Draw Map");



  m_DrawInfo.VisitGrid(viewport_bounds, [&](uint32_t grid_id, std::vector<GridDrawElement> & grid_elems)
  {
    auto grid_box = m_DrawInfo.GetGridBoxForGridId(grid_id);

    auto grid_start = glm::round(RenderVec2{ grid_box.m_Start });
    auto & shader = g_ShaderManager.GetDefaultWorldSpaceShader();
    render_state.BindShader(shader);
    shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Offset"), grid_start - screen_center);
    shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Matrix"), RenderVec4{ 1, 0, 0, 1 });
    shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), Color(255, 255, 255, 255));

    render_state.BindVertexBuffer(m_VertexBuffer);

    for (auto & draw : grid_elems)
    {
      render_state.BindTexture(*draw.m_Texture);
      render_state.Draw(draw.m_StartIndex, draw.m_EndIndex);
    }

    return true;
  }, false);

  for (auto & anim : m_AnimatedTiles)
  {
    auto anim_box = Box::FromFrameCenterAndSize(anim.m_Position, Vector2(anim.m_State.m_FrameWidth, anim.m_State.m_FrameHeight));
    if (BoxIntersect(viewport_bounds, anim_box))
    {
      auto pos = glm::round((RenderVec2)anim.m_Position - screen_center);
      SpriteEngineData::RenderTile(m_TileSheet, render_state, anim.m_State.m_AnimIndex, anim.m_State.m_AnimFrame, kSpriteDefaultSkin, pos);
    }
  }
}


#ifdef USE_Z_ORDERING
void MapManualTileLayerInstance::DrawDynamic(const Box & viewport_bounds, DrawList & draw_list)
{
  m_DynamicDrawInfo.VisitGrid(viewport_bounds, [&](uint32_t grid_id, std::vector<GridDrawDynamicElement> & grid_elems)
  {
    for (auto & elem : grid_elems)
    {
      draw_list.PushDraw(m_LayerOrder, elem.m_LowerEdge, [this, grid_id, elem=&elem](GameContainer &, const Box &, const RenderVec2 & screen_center, RenderState & render_state)
      {
        auto & shader = g_ShaderManager.GetDefaultWorldSpaceShader();
        auto grid_box = m_DynamicDrawInfo.GetGridBoxForGridId(grid_id);
        auto grid_start = RenderVec2{ grid_box.m_Start };
        render_state.BindShader(shader);
        shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Offset"), grid_start - screen_center);
        shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Matrix"), RenderVec4{ 1, 0, 0, 1 });
        shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), Color(255, 255, 255, 255));

        render_state.BindVertexBuffer(m_VertexBuffer);
        render_state.BindTexture(*elem->m_Texture);

        render_state.Draw(elem->m_StartIndex, elem->m_EndIndex);
      });
    }

    return true;
  }, false);
}
#endif

int MapManualTileLayerInstance::GetLayerOrder() const
{
  return m_LayerOrder;
}
