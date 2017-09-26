#pragma once

#include "Engine/EngineCommon.h"

enum STORM_REFL_ENUM class UICustomPropertyDataType
{
  kNumber,
  kString,
};

struct UICustomProperty
{
  STORM_REFL;
  UICustomPropertyDataType m_Type;
  std::string m_Data;
};

struct UIElementDataBase
{
  STORM_REFL;
  float m_Enabled = true;
  float m_Active = false;

  float m_ColorR = 1.0f;
  float m_ColorG = 1.0f;
  float m_ColorB = 1.0f;
  float m_ColorA = 1.0f;

  void SetColor(const Color & c)
  {
    m_ColorR = c.r;
    m_ColorG = c.g;
    m_ColorB = c.b;
    m_ColorA = c.a;
  }
};

struct UIElementDataFrameCenter : public UIElementDataBase
{
  STORM_REFL;
  float m_PositionX;
  float m_PositionY;
};

struct UIElementDataStartEnd : public UIElementDataBase
{
  STORM_REFL;
  float m_StartX;
  float m_StartY;
  float m_EndX;
  float m_EndY;

  void SetBounds(const Box & b)
  {
    m_StartX = (float)b.m_Start.x;
    m_StartY = (float)b.m_Start.y;
    m_EndX = (float)b.m_End.x;
    m_EndY = (float)b.m_End.y;
  }
};
