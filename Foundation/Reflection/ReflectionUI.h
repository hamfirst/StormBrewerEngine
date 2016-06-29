#pragma once

#include "Foundation\Common.h"

enum class RPropertyType
{
  kInteger,
  kFloat,
  kBoolean,
  kEnum,
  kPolymorphic,
  kString,
  kObject,
  kArray,
};

struct RPropertyInfo final
{
  RPropertyType m_Type;

  int m_MinInt;
  int m_MaxInt;
  float m_MinFloat;
  float m_MaxFloat;

  uint32_t m_AgregateType;
};
