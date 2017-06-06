
#include "Runtime/RuntimeCommon.h"
#include "Runtime/RuntimeState.h"
#include "Runtime/Map/MapInstance.h"
#include "Runtime/TileSheet/TileSheetResource.h"
#include "Runtime/Collision/CollisionSystem.h"
#include "Runtime/Entity/Entity.h"
#include "Runtime/Entity/EntitySystem.h"

Any CreateMapEngineData(MapDef & map_def);

MapInstance::MapInstance(NotNullPtr<RuntimeState> runtime_state, MapDef & map_def, std::size_t map_id) :
  m_EngineData(CreateMapEngineData(map_def)),
  m_MapId(map_id)
{
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

  runtime_state->m_CollisionSystem->PushMapCollision(m_MapId, collision_list);

  std::vector<Entity *> entities;
  for (auto elem : map_def.m_EntityLayers)
  {
    for (auto entity : elem.second.m_Entities)
    {
      auto new_entity = runtime_state->m_EntitySystem->CreateEntity(&entity.second.m_EntityDef, false);
      new_entity->GetPosition() = Vector2(entity.second.m_XPosition, entity.second.m_YPosition);
      new_entity->GetLayer() = elem.second.m_LayerOrder;
      entities.push_back(new_entity);
    }
  }

  for (auto entity : entities)
  {
    entity->Activate();
  }
}

void MapInstance::RemoveCollision(NotNullPtr<RuntimeState> runtime_state)
{
  runtime_state->m_CollisionSystem->RemoveMapCollision(m_MapId);
}
