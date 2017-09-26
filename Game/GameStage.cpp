
#include "Game/GameStage.h"

#include "Foundation/BasicTypes/BasicTypeHash.h"
#include "Foundation/Pathfinding/Pathfinding.h"

#include "Game/Data/PlayerSpawn.refl.meta.h"

GameStage::GameStage(const Map & map) :
  m_DynamicObjectCount(127)
{
  for (auto path : map->m_Paths)
  {
    auto collision_mask = 0x1;
    auto team = -1;

    auto visitor = [&](Vector2 start, Vector2 end)
    {
      CollisionDatabaseData<GameNetVal> coll_data;
      coll_data.m_CollisionMask = collision_mask;

      Intersection<GameNetVal>::CollisionLine line(GameNetVec2(start.x, start.y), GameNetVec2(end.x, end.y));
      m_Collision.AddLine(line, coll_data, true, true);

      m_CollisionLines.emplace_back(CollisionLine{ start, end, team });
    };

    path.second.VisitLines(visitor);
  }

  for (int index = 0; index < kMaxTeams; ++index)
  {
    m_PlayerSpawns.emplace_back();
  }

  for (auto anchor : map->m_Anchors)
  {
    auto player_spawn_info = anchor.second.m_AnchorData.GetAs<PlayerSpawn>();

    if (player_spawn_info)
    {
      m_PlayerSpawns[(int)player_spawn_info->m_Team].push_back(anchor.second.GetPoint());
    }
  }

  for (auto volume : map->m_Volumes)
  {

  }
}

GameStage::~GameStage()
{

}

GameFullState GameStage::CreateDefaultGameState() const
{
  return GameFullState{ ServerObjectManager(m_StaticObjects, m_DynamicObjectCount, kMaxPlayers) };
}

const CollisionDatabase<GameNetVal> & GameStage::GetCollision() const
{
  return m_Collision;
}

const std::vector<CollisionLine> GameStage::GetCollisionLines() const
{
  return m_CollisionLines;
}

const std::vector<std::vector<Vector2>> & GameStage::GetPlayerSpawns() const
{
  return m_PlayerSpawns;
}
