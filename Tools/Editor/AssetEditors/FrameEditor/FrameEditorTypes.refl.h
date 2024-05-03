#pragma once

#include "StormTech/StormRefl/StormRefl.h"

#include "Runtime/FrameData/FrameData.refl.h"

struct FrameCopyData
{
  STORM_REFL;

  bool m_Valid = false;
  FrameDataDefType m_Type;
  std::string m_Data;
};
