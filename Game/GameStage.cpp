#include "Game/GameCommon.h"
#include "Game/GameStage.h"

#include "Foundation/BasicTypes/BasicTypeHash.h"
#include "Foundation/Pathfinding/Pathfinding.h"

#include "Runtime/Map/MapCollision.h"
#include "Runtime/ServerObject/ServerObjectSystem.h"

#include "Game/Data/PlayerSpawn.refl.meta.h"

GameStage::GameStage(const Map & map) :
  m_DynamicObjectCount(127)
{
  m_CollisionDatabase.PushMapCollision(0, ExtractMapCollision(*map.GetData(), {}));

  auto map_data = map.GetData();
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
        ServerObjectStaticInitData init_data{ type_index, obj.second.m_ServerObject.m_InitData, pos };
        if (obj.second.m_ServerObject.m_IsStatic)
        {
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

const CollisionDatabase & GameStage::GetCollisionDatabase() const
{
  return m_CollisionDatabase;
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
