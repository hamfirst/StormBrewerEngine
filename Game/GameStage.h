#pragma once

#include "Runtime/Map/MapResource.h"

#include "Game/GameFullState.refl.h"


class GameStage
{
public:
  GameStage(const Map & map);

  GameFullState CreateDefaultGameState() const;

private:
  friend class GameInstance;

  std::vector<ServerObjectStaticInitData> m_StaticObjects;
  int m_DynamicObjectCount;
};
