
#pragma once

#include "Game/GameCommon.h"
#include "Game/GameServerTypes.h"
#include "Game/GameNetworkData.refl.h"

struct PlayerConfig
{
public:
  STORM_DATA_DEFAULT_CONSTRUCTION(PlayerConfig);

  RString STORM_REFL_ATTR_VAL(file, sprite) m_EntityFile = "./Entities/Player.entity";

  RDeterministicFloat<GameNetVal> m_MoveSpeed = "2.0";
  RDeterministicFloat<GameNetVal> m_MoveAccel = "5.0";

#ifdef PLATFORMER_MOVEMENT
  RDeterministicFloat<GameNetVal> m_AirControlAccel = "0.5";
  RDeterministicFloat<GameNetVal> m_JumpSpeed = "3.5";
  RDeterministicFloat<GameNetVal> m_Gravity = "0.1";
  RDeterministicFloat<GameNetVal> m_GravityJumpReduce = "0.2";
  RDeterministicFloat<GameNetVal> m_FallthroughThreshold = "0.5";

#endif
};
