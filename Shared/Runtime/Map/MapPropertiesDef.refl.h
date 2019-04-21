#pragma once

#include "Runtime/RuntimeCommon.h"

#include "ProjectSettings/ProjectNetworkSettings.h"

#include <StormData/StormData.h>
#include <StormData/StormDataTypes.h>

struct RUNTIME_EXPORT MapPropertiesDef
{
  STORM_DATA_DEFAULT_CONSTRUCTION(MapPropertiesDef);

  int m_MaxTeams = 0;

#ifdef NET_USE_PLAYER_LIMIT
  int m_PlayerCount = 0;
#endif

#ifdef NET_USE_SCORE_LIMIT
  uint16_t m_ScoreLimit = 0;
#endif

#ifdef NET_USE_SCORE_LIMIT
  uint16_t m_TimeLimit = 0;
#endif
};
