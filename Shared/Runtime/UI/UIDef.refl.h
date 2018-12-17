#pragma once

#include "StormRefl/StormRefl.h"
#include "StormData/StormData.h"
#include "StormData/StormDataTypes.h"

#include "Runtime/RuntimeCommon.h"

struct RUNTIME_EXPORT UIDefDebugData
{
  STORM_DATA_DEFAULT_CONSTRUCTION(UIDefDebugData);
  RString m_Name;
  RString m_Value;
};

struct RUNTIME_EXPORT UIDef
{
  STORM_DATA_DEFAULT_CONSTRUCTION(UIDef);

  RString m_InitFunction = "InitMenu";
  RString m_CleanupFunction = "CleanupMenu";

  RMergeList<UIDefDebugData> m_Variables;
  RMergeList<UIDefDebugData> m_Functions;
};

