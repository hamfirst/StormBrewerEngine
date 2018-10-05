#pragma once

#include "Game/GameCommon.h"
#include "Game/GameServerTypes.h"

struct ProjectileConfig
{
public:
  STORM_DATA_DEFAULT_CONSTRUCTION(ProjectileConfig);

  RUInt m_MaxDistance = 200;
};
