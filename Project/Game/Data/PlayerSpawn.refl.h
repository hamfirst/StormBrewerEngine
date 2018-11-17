
#pragma once

#include "Foundation/Common.h"

#include "Runtime/Anchor/AnchorDef.refl.h"
#include "Game/GameNetworkData.refl.h"

struct PlayerSpawn : public AnchorDataBase
{
public:
  STORM_DATA_DEFAULT_CONSTRUCTION_DERIVED(PlayerSpawn);
  RInt m_Team;
};
