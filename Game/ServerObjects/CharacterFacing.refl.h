
#pragma once

#include "Game/GameCommon.h"
#include "Game/GameServerTypes.h"

enum STORM_REFL_ENUM class CharacterFacing
{
  kLeft,
  kRight,
#ifndef PLATFORMER_MOVEMENT
  kDown,
  kUp,
#endif
  kNone,
};

