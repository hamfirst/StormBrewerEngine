#pragma once

#include "Runtime/Map/MapResource.h"

#include "Game/GameFullState.refl.h"
#include "Game/GameServerTypes.h"

#include "Runtime/Collision/IntersectionDatabase.h"

struct GameStaticCollision : public CollisionDatabaseData<GameNetVal>
{

};

class GameStage
{
public:
  GameStage(const Map & map);
  ~GameStage();

  GameFullState CreateDefaultGameState() const;

private:
  friend class GameInstance;

  std::vector<ServerObjectStaticInitData> m_StaticObjects;
  int m_DynamicObjectCount;

};
