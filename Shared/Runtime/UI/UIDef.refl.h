#pragma once

#include "StormRefl/StormRefl.h"
#include "StormData/StormData.h"
#include "StormData/StormDataTypes.h"

#include "Runtime/RuntimeCommon.h"

struct RUNTIME_EXPORT UIDefDebugVariable
{
  STORM_DATA_DEFAULT_CONSTRUCTION(UIDefDebugVariable);
  RString m_Name;
  RString m_Value;
};


struct RUNTIME_EXPORT UIDefDebugFunction
{
  STORM_DATA_DEFAULT_CONSTRUCTION(UIDefDebugFunction);
  RString m_Name;
  RString m_Value;
  RBool m_DebugOutput = true;
};

struct RUNTIME_EXPORT UIDef
{
  STORM_DATA_DEFAULT_CONSTRUCTION(UIDef);

  RString m_InitFunction = "InitMenu";
  RString m_CleanupFunction = "CleanupMenu";

  RMergeList<UIDefDebugVariable> m_Variables;
  RMergeList<UIDefDebugFunction> m_Functions;
};

