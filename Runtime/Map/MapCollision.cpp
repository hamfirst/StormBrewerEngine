
#include "Runtime/RuntimeCommon.h"
#include "Runtime/Map/MapCollision.h"
#include "Runtime/TileSheet/TileSheetResource.h"

std::vector<std::vector<Box>> ExtractMapCollision(const MapDef & map_def, const Vector2 & offset, const std::vector<uint32_t> & collision_type_hashes)
{
  std::vector<std::vector<Box>> collision_list;

  for (auto & coll_type : collision_type_hashes)
  {
    collision_list.emplace_back();

    auto & main_coll = collision_list[0];

    for (auto elem : map_def.m_ManualTileLayers)
    {
      if (elem.second.m_CollisionLayer == false)
      {
        continue;
      }

      auto tile_sheet = TileSheetResource::Load(elem.second.m_TileSheet.data());
      auto tile_sheet_data = tile_sheet->GetData();

      std::vector<Box> default_tile_collision;
      for (auto elem : tile_sheet_data->m_InstanceData.m_MultiBoxData)
      {
        if (crc32(elem.second.m_FrameDataName) == coll_type)
        {
          for (auto b : *elem.second.m_Data.GetPtr())
          {
            default_tile_collision.emplace_back(b);
          }
        }
      }

      for (auto tile : elem.second.m_Tiles)
      {
        Vector2 tile_pos = Vector2{ tile.second->x, tile.second->y } + offset;
        auto frame_data = tile_sheet_data->m_FrameData.TryGet(tile.second->GetTileId());

        bool got_collision_data = false;

        if (frame_data)
        {
          for (auto elem : frame_data->m_MultiBoxData)
          {
            if (crc32(elem.second.m_FrameDataName) == coll_type)
            {
              for (auto & b : *elem.second.m_Data.GetPtr())
              {
                auto box = b;
                box.m_Start += tile_pos;
                box.m_End += tile_pos;
                main_coll.emplace_back(box);
              }

              got_collision_data = true;
              break;
            }
          }
        }

        if (got_collision_data == false)
        {
          for (auto & b : default_tile_collision)
          {
            auto box = b;
            box.m_Start += tile_pos;
            box.m_End += tile_pos;
            main_coll.emplace_back(box);
          }
        }
      }
    }
  }

  return collision_list;
}
