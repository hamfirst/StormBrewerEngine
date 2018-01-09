#pragma once

#include "Runtime/Map/MapResource.h"

#include "Foundation/Pathfinding/GraphPathfinding.h"
#include "Foundation/Pathfinding/GridPathfinding.h"
#include "Foundation/Pathfinding/PathfindingPath.h"

#include "Game/GameFullState.refl.h"
#include "Game/GameServerTypes.h"

#include "Runtime/Collision/CollisionDatabase.h"
#include "Runtime/Collision/IntersectionDatabase.h"

#ifndef MAP_PLATFORMER_PATHFINDING
struct GamePathfindingGridElement
{
  bool m_Passable = true;
};

struct GamePathfindingEvalInfo
{
};

struct GamePathfindingGridEvaluator
{
  GameNetVal operator ()(const GamePathfindingGridElement & a, const GamePathfindingGridElement & b, const GamePathfindingEvalInfo & eval_info) const
  {
    return b.m_Passable ? GameNetVal(1) : GameNetVal(-1);
  }
};

using PathfindingDatabaseType = PathfindingBasicGrid2D<GamePathfindingGridElement, GameNetVal, GamePathfindingGridEvaluator, GamePathfindingEvalInfo, true, true>;
#endif

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

  const StaticCollisionDatabase & GetCollisionDatabase() const;
  std::vector<Vector2> FindPath(const Vector2 & start, const Vector2 & end, int max_iterations) const;

  const IntersectionDatabase<GameNetVal> & GetIntersectionDatabase() const;
  const std::vector<GameCollisionLine> GetCollisionLines() const;

  const std::vector<std::vector<Vector2>> & GetPlayerSpawns() const;

  Optional<ServerObjectHandle> FindStaticObject(uint32_t obj_name_hash) const;

private:
  friend class GameInstance;

  std::vector<ServerObjectStaticInitData> m_StaticObjects;
  std::vector<ServerObjectStaticInitData> m_DynamicObjects;
  int m_DynamicObjectCount;

  StaticCollisionDatabase m_CollisionDatabase;

#ifndef MAP_PLATFORMER_PATHFINDING
  Optional<PathfindingDatabaseType> m_Pathfinding;
  Box m_PathfindingBounds;
  Vector2 m_PathfindingGridSize;
  Vector2 m_PathfindingElementSize;
#endif

  IntersectionDatabase<GameNetVal> m_IntersectionDatabase;
  std::vector<GameCollisionLine> m_CollisionLines;

  std::vector<std::vector<Vector2>> m_PlayerSpawns;

  std::unordered_map<uint32_t, ServerObjectHandle> m_StaticObjLookup;
};
