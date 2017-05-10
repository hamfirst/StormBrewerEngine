#pragma once

#include "Engine/EngineCommon.h"

#include <StormRefl/StormRefl.h>

struct ENGINE_EXPORT EngineSettings
{
  STORM_REFL;

  int m_AssetLoadQueueSize = 8092;
  int m_AssetLoadThreads = 2;

  int m_FontCacheSize = 256;
};

void ENGINE_EXPORT LoadEngineSettingsFile();

extern EngineSettings g_EngineSettings;


