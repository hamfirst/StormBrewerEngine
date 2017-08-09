
#include "Engine/EngineCommon.h"

#include "Runtime/TileSheet/TileSheetResource.h"
#include "Runtime/Collision/CollisionSystem.h"

#include "Engine/EngineState.h"
#include "Engine/Map/MapInstance.h"
#include "Engine/Entity/Entity.h"
#include "Engine/Entity/EntityHandle.h"
#include "Engine/Entity/EntitySystem.h"
#include "Engine/Rendering/RenderSettings.h"

MapInstance::MapInstance(NotNullPtr<EngineState> engine_state, MapDef & map_def, std::size_t map_id) :
  m_MapId(map_id)
{
  for (auto elem : map_def.m_ManualTileLayers)
  {
    m_ManualTileLayers.emplace_back(map_def, elem.first);
  }

  for (auto elem : map_def.m_EffectLayers)
  {
    m_EffectLayers.emplace_back(map_def, elem.first);
  }

  for (auto elem : map_def.m_ParalaxLayers)
  {
    m_ParalaxLayers.emplace_back(map_def, elem.first);
  }

  std::vector<std::vector<Box>> collision_list;
  collision_list.emplace_back();

  auto & main_coll = collision_list[0];

  for (auto elem : map_def.m_ManualTileLayers)
  {
    if (elem.second.m_CollisionLayer == false)
    {
      continue;
    }

    auto tile_sheet = TileSheetResource::Load(elem.second.m_TileSheet.data());

    std::vector<std::pair<uint32_t, Vector2>> textures;
    for (auto tex : tile_sheet->m_Textures)
    {
      textures.emplace_back(std::make_pair(crc32(tex.second.m_Filename.data()), Vector2(tex.second.m_FrameWidth, tex.second.m_FrameHeight)));
    }

    for (auto tile : elem.second.m_Tiles)
    {
      int texture_index = -1;
      for(std::size_t index = 0; index < textures.size(); ++index)
      {
        auto & tex = textures[index];
        if (tex.first == tile.second->m_TextureHash)
        {
          texture_index = (int)index;
        }
      }

      if (texture_index == -1)
      {
        continue;
      }

      auto & texture_data = textures[texture_index];
      Box b;
      b.m_Start = Vector2(tile.second->x, tile.second->y) - texture_data.second / 2;
      b.m_End = b.m_Start + texture_data.second - Vector2(1, 1);

      main_coll.emplace_back(b);
    }
  }

  engine_state->m_CollisionSystem->PushMapCollision(m_MapId, collision_list);

  std::vector<Entity *> entities;
  for (auto elem : map_def.m_EntityLayers)
  {
    for (auto entity : elem.second.m_Entities)
    {
      auto new_entity = engine_state->m_EntitySystem->CreateEntity(&entity.second.m_EntityDef, false);
      new_entity->GetPosition() = Vector2(entity.second.m_XPosition, entity.second.m_YPosition);
      new_entity->GetLayer() = elem.second.m_LayerOrder;
      entities.push_back(new_entity);
    }
  }

  for (auto entity : entities)
  {
    m_MapEntities.push_back(entity->GetHandle());
  }
}

void MapInstance::Update(GameContainer & game_container)
{

}

void MapInstance::Draw(const Box & viewport_bounds, DrawList & draw_list)
{
  for (auto & layer : m_ParalaxLayers)
  {
    draw_list.PushDraw(layer.GetLayerOrder(), INT_MAX, [&](GameContainer & game_container, const Box & viewport_bounds, const RenderVec2 & screen_center, RenderState & render_state, RenderUtil & render_util)
    {
      layer.Draw(viewport_bounds, screen_center, render_state, render_util);
    });
  }

  for (auto & layer : m_ManualTileLayers)
  {
    draw_list.PushDraw(layer.GetLayerOrder(), INT_MAX, [&](GameContainer & game_container, const Box & viewport_bounds, const RenderVec2 & screen_center, RenderState & render_state, RenderUtil & render_util)
    {
      layer.Draw(viewport_bounds, screen_center);
    });

#ifdef USE_Z_ORDERING
    layer.DrawDynamic(viewport_bounds, draw_list);
#endif
  }

  for (auto & layer : m_EffectLayers)
  {
    draw_list.PushDraw(layer.GetLayerOrder(), INT_MAX, [&](GameContainer & game_container, const Box & viewport_bounds, const RenderVec2 & screen_center, RenderState & render_state, RenderUtil & render_util)
    {
      layer.Draw(game_container, viewport_bounds, screen_center, render_state, render_util);
    });
  }
}


void MapInstance::ActivateEntities()
{
  for (auto & elem : m_MapEntities)
  {
    auto entity = elem.Resolve();
    if (entity)
    {
      entity->Activate();
    }
  }
}

void MapInstance::RemoveCollision(NotNullPtr<EngineState> engine_state)
{
  engine_state->m_CollisionSystem->RemoveMapCollision(m_MapId);
}
