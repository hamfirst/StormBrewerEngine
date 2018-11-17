#pragma once

#include "Engine/EngineCommon.h"

struct UIGlobalBlock
{
  STORM_REFL;
  float m_Time = 0;
  float m_ScreenWidth = 0;
  float m_ScreenHeight = 0;
};

struct UIAutoCalculatedBlock
{
  STORM_REFL;
  float m_TimeAlive = 0;
  float m_Width = 0;
  float m_Height = 0;
  float m_ScreenX = 0;
  float m_ScreenY = 0;
};
