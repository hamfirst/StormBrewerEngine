
#pragma once

#include "StormRefl/StormRefl.h"

#include <string>

struct GameClientUIData
{
  STORM_REFL;

  bool timer_pre_round = false;
  float timer_scale = 0.0f;
  std::string timer;

  std::string tutorial_hint;
  int tutorial_hint_x = 0;
  int tutorial_hint_y = 0;
};
