#pragma once

#include "Engine/EngineCommon.h"

enum STORM_REFL_ENUM class UICustomPropertyDataType
{
  kNumber,
  kString,
};

struct UICustomProperty
{
  UICustomPropertyDataType m_Type;
  std::string m_Data;
};
