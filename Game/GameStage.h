#pragma once

#include "Runtime/Map/MapResource.h"

#include "Foundation/Pathfinding/GraphPathfinding.h"
#include "Foundation/Pathfinding/PathfindingPath.h"

#include "Game/GameFullState.refl.h"
#include "Game/GameServerTypes.h"

#include "Runtime/Collision/CollisionDatabase.h"
#include "Runtime/Collision/IntersectionDatabase.h"

struct GameCollisionLine
{
  Vector2 m_Start;
  Vector2 m_End;
  int m_Team;
};

class GameStage
{
public:
  GameStage(const Map & map);
  ~GameStage();

  GameFullState CreateDefaultGameState() const;

  const CollisionDatabase & GetCollisionDatabase() const;

  const IntersectionDatabase<GameNetVal> & GetIntersectionDatabase() const;
  const std::vector<GameCollisionLine> GetCollisionLines() const;

  const std::vector<std::vector<Vector2>> & GetPlayerSpawns() const;

private:
  friend class GameInstance;

  std::vector<ServerObjectStaticInitData> m_StaticObjects;
  int m_DynamicObjectCount;

  CollisionDatabase m_CollisionDatabase;

  IntersectionDatabase<GameNetVal> m_IntersectionDatabase;
  std::vector<GameCollisionLine> m_CollisionLines;

  std::vector<std::vector<Vector2>> m_PlayerSpawns;
};
