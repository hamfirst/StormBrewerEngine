#pragma once

#include "Runtime/RuntimeCommon.h"

#include "ProjectSettings/ProjectNetworkSettings.h"

#include <StormData/StormData.h>
#include <StormData/StormDataTypes.h>

class RUNTIME_EXPORT MapPropertiesDef
{
public:
  STORM_DATA_DEFAULT_CONSTRUCTION(MapPropertiesDef);

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
