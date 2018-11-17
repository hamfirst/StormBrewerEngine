#pragma once

#include "Foundation/Common.h"

#include "StormRefl/StormRefl.h"

struct GameLevelListAsset
{
  STORM_REFL;
  std::vector<std::string> m_Levels;
};
