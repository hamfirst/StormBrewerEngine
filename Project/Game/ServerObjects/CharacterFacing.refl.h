
#pragma once

#include "Game/GameCommon.h"
#include "Game/GameTypes.h"
#include "Game/NetworkEvents/GameNetworkData.refl.h"

enum class STORM_REFL_ENUM CharacterFacing
{
  kLeft,
  kRight,
#ifndef PLATFORMER_MOVEMENT
  kDown,
  kUp,
#endif
  kNone,
};


Optional<CharacterFacing> GetFacingForDirection(const GameNetVec2 & dir);
GameNetVec2 GetDirectionForFacing(const CharacterFacing & facing);
std::pair<uint32_t, bool> GetAnimationInfoForFacingDirection(CharacterFacing facing);
