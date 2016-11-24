#pragma once

#include <StormRefl/StormRefl.h>

struct EngineSettings
{
  STORM_REFL;

  int m_AssetLoadQueueSize = 8092;
  int m_AssetLoadThreads = 2;

  int m_FontCacheSize = 256;
};

void LoadEngineSettingsFile();

extern EngineSettings g_EngineSettings;


