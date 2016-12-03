#pragma once

#include <StormRefl/StormRefl.h>
#include <StormData/StormDataTypes.h>

struct SubType
{
  STORM_REFL;
  RSparseList<RInt> m_List;
};

struct TestType
{
  STORM_REFL;

  RInt m_Int;
  RFloat m_Float;
  RMergeList<RInt> m_List;

  SubType m_Sub;
};
