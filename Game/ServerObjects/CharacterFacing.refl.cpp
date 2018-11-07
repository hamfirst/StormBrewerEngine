
#include "Game/GameCommon.h"
#include "Game/ServerObjects/CharacterFacing.refl.h"

std::pair<uint32_t, bool> GetAnimationInfoForFacingDirection(CharacterFacing facing)
{
  switch(facing)
  {
#ifndef PLATFORMER_MOVEMENT
    case CharacterFacing::kLeft:
      return std::make_pair(COMPILE_TIME_CRC32_STR("MoveRight"), true);
    case CharacterFacing::kRight:
      return std::make_pair(COMPILE_TIME_CRC32_STR("MoveRight"), false);
    case CharacterFacing::kDown:
      return std::make_pair(COMPILE_TIME_CRC32_STR("MoveUp"), false);
    case CharacterFacing::kUp:
      return std::make_pair(COMPILE_TIME_CRC32_STR("MoveUp"), false);
#else
    case CharacterFacing::kLeft:
      return std::make_pair(COMPILE_TIME_CRC32_STR("Move"), true);
    case CharacterFacing::kRight:
      return std::make_pair(COMPILE_TIME_CRC32_STR("Move"), false);
#endif
  }

  return std::make_pair(0, false);
}

Optional<CharacterFacing> GetFacingForDirection(const GameNetVec2 & dir)
{
  if(dir.x == GameNetVal(0) && dir.y == GameNetVal(0))
  {
    return {};
  }

#ifdef PLATFORMER_MOVEMENT
  if(dir.x > GameNetVal(0))
  {
    return CharacterFacing::kRight;
  }
  else
  {
    return CharacterFacing::kLeft;
  }
#else
  if(dir.x.Abs() > dir.y.Abs())
  {
    if(dir.x > GameNetVal(0))
    {
      return CharacterFacing::kRight;
    }
    else
    {
      return CharacterFacing::kLeft;
    }
  }
  else
  {
    if(dir.y > GameNetVal(0))
    {
      return CharacterFacing::kUp;
    }
    else
    {
      return CharacterFacing::kDown;
    }
  }
#endif
}

GameNetVec2 GetDirectionForFacing(const CharacterFacing & facing)
{
  switch(facing)
  {
    case CharacterFacing::kLeft:
      return GameNetVec2(GameNetVal(-1), GameNetVal(0));
    case CharacterFacing::kRight:
      return GameNetVec2(GameNetVal(1), GameNetVal(0));
#ifndef PLATFORMER_MOVEMENT
    case CharacterFacing::kUp:
      return GameNetVec2(GameNetVal(0), GameNetVal(1));
    case CharacterFacing::kDown:
      return GameNetVec2(GameNetVal(0), GameNetVal(-1));
#endif
    default:
      return GameNetVec2(GameNetVal(0), GameNetVal(0));
  }
}