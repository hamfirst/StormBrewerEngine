#include "Game/GameCommon.h"
#include "Game/GameStage.h"

#include "Foundation/BasicTypes/BasicTypeHash.h"
#include "Foundation/Pathfinding/Pathfinding.h"

#include "Runtime/Map/MapCollision.h"
#include "Runtime/ServerObject/ServerObjectSystem.h"

#include "Game/Data/PlayerSpawn.refl.meta.h"

GameStage::GameStage(const Map & map) :
  m_DynamicObjectCount(127),
  m_CollisionDatabase(2)
{
  auto map_data = map.GetData();
  m_CollisionDatabase.PushMapCollision(0, ExtractMapCollision(*map_data, {}, { COMPILE_TIME_CRC32_STR("Collision"), COMPILE_TIME_CRC32_STR("OneWay") }));

  if (map_data->m_PathfingindInfo.m_Valid)
  {
    auto & calc_info = map_data->m_PathfingindInfo.m_CalculatedInfo;

#ifndef MAP_PLATFORMER_PATHFINDING
    if (map_data->m_PathfingindInfo.m_GridWidth > 0 && map_data->m_PathfingindInfo.m_GridHeight > 0)
    {
      m_PathfindingElementSize = Vector2(map_data->m_PathfingindInfo.m_GridWidth, map_data->m_PathfingindInfo.m_GridHeight);
      m_PathfindingGridSize = Vector2(calc_info->m_SizeX, calc_info->m_SizeY);

      m_PathfindingBounds.m_Start = Vector2(calc_info->m_StartX, calc_info->m_StartY);
      m_PathfindingBounds.m_End = m_PathfindingBounds.m_Start + Vector2(calc_info->m_SizeX, calc_info->m_SizeY) * m_PathfindingElementSize;

      m_Pathfinding.Emplace(m_PathfindingGridSize, GameNetVal("1.41421356237f"));
      int grid_index = 0;
      for (int y = 0; y < m_PathfindingGridSize.y; ++y)
      {
        for (int x = 0; x < m_PathfindingGridSize.x; ++x)
        {
          GamePathfindingGridElement grid_element;
          grid_element.m_Passable = std::get<0>(calc_info->m_GridInfo[grid_index]) == 0;

          m_Pathfinding->SetGridData(x, y, grid_element);
          grid_index++;
        }
      }
    }
#else

#endif
  }

  for (auto path : map_data->m_Paths)
  {
    auto collision_mask = 0x1;
    auto team = -1;

    auto visitor = [&](Vector2 start, Vector2 end)
    {
      CollisionDatabaseData<GameNetVal> coll_data;
      coll_data.m_CollisionMask = collision_mask;

      Intersection<GameNetVal>::CollisionLine line(GameNetVec2(start.x, start.y), GameNetVec2(end.x, end.y));
      m_IntersectionDatabase.AddLine(line, coll_data, true, true);

      m_CollisionLines.emplace_back(GameCollisionLine{ start, end, team });
    };

    path.second.VisitLines(visitor);
  }

  for (int index = 0; index < kMaxTeams; ++index)
  {
    m_PlayerSpawns.emplace_back();
  }

  for (auto anchor : map_data->m_Anchors)
  {
    auto player_spawn_info = anchor.second.m_AnchorData.GetAs<PlayerSpawn>();

    if (player_spawn_info)
    {
      m_PlayerSpawns[(int)player_spawn_info->m_Team].push_back(anchor.second.GetPoint());
      continue;
    }
  }

  for (auto volume : map_data->m_Volumes)
  {

  }

  for (auto layer : map_data->m_ServerObjectLayers)
  {
    for (auto obj : layer.second.m_Objects)
    {
      auto type_index = g_ServerObjectSystem.GetTypeIndexForInitDataTypeNameHash(obj.second.m_ServerObject.m_InitData.GetTypeNameHash());
      if (type_index)
      {
        Vector2 pos = Vector2((int)obj.second.m_XPosition, obj.second.m_YPosition);
        ServerObjectStaticInitData init_data{ type_index.Value(), obj.second.m_ServerObject.m_InitData, pos };
        if (obj.second.m_ServerObject.m_IsStatic)
        {
          m_StaticObjLookup.insert(std::make_pair(crc32(obj.second.m_Name.data()), ServerObjectHandle::ConstructFromStaticIndex((int)m_StaticObjects.size())));
          m_StaticObjects.emplace_back(std::move(init_data));
        }
        else
        {
          m_DynamicObjects.emplace_back(std::move(init_data));
        }
      }
    }
  }
}

GameStage::~GameStage()
{

}

GameFullState GameStage::CreateDefaultGameState() const
{
  return GameFullState{ ServerObjectManager(m_StaticObjects, m_DynamicObjects, m_DynamicObjectCount, kMaxPlayers) };
}

const StaticCollisionDatabase & GameStage::GetCollisionDatabase() const
{
  return m_CollisionDatabase;
}

std::vector<Vector2> GameStage::FindPath(const Vector2 & start, const Vector2 & end, int max_iterations) const
{
#ifndef MAP_PLATFORMER_PATHFINDING
  auto s = start - m_PathfindingBounds.m_Start;
  auto e = end - m_PathfindingBounds.m_Start;

  s /= m_PathfindingElementSize;
  e /= m_PathfindingElementSize;

  if (m_Pathfinding->GetGridData(e.x, e.y).m_Passable == false)
  {
    return {};
  }

  if (s.x < 0 || s.x >= m_PathfindingGridSize.x || s.y < 0 || s.y >= m_PathfindingGridSize.y)
  {
    return {};
  }

  if (e.x < 0 || e.x >= m_PathfindingGridSize.x || e.y < 0 || e.y >= m_PathfindingGridSize.y)
  {
    return {};
  }

  auto s_node = m_Pathfinding->LocationToNodeId(s);
  auto e_node = m_Pathfinding->LocationToNodeId(e);

  PathfindingDatabaseType::ScratchData scratch_data = m_Pathfinding->CreateScratchData();

  GamePathfindingEvalInfo eval_info;
  auto path_nodes = Pathfinding<PathfindingDatabaseType>::FindPath(s_node, e_node, *m_Pathfinding, scratch_data, eval_info, max_iterations);
  if (path_nodes.size() == 0)
  {
    return {};
  }

  std::vector<Vector2> path;
  for (auto & elem : path_nodes)
  {
    path.push_back(m_Pathfinding->NodeIdToLocation(elem) * m_PathfindingElementSize + m_PathfindingBounds.m_Start + m_PathfindingElementSize / 2);
  }

  return path;

#endif
}

const IntersectionDatabase<GameNetVal> & GameStage::GetIntersectionDatabase() const
{
  return m_IntersectionDatabase;
}

const std::vector<GameCollisionLine> GameStage::GetCollisionLines() const
{
  return m_CollisionLines;
}

const std::vector<std::vector<Vector2>> & GameStage::GetPlayerSpawns() const
{
  return m_PlayerSpawns;
}

Optional<ServerObjectHandle> GameStage::FindStaticObject(uint32_t obj_name_hash) const
{
  auto itr = m_StaticObjLookup.find(obj_name_hash);
  if (itr == m_StaticObjLookup.end())
  {
    return {};
  }

  return itr->second;
}
