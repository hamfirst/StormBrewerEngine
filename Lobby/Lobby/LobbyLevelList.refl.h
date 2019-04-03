
#pragma once

#include <string>
#include <string_view>
#include <vector>

#include "StormRefl/StormRefl.h"

#include "ProjectSettings/ProjectNetworkSettings.h"

struct LobbyMapProperties
{
  STORM_REFL;

#ifdef NET_USE_PLAYER_LIMIT
  int m_PlayerCount = 0;
#endif

#ifdef NET_USE_SCORE_LIMIT
  int m_ScoreLimit = 0;
#endif

#ifdef NET_USE_SCORE_LIMIT
  int m_TimeLimit = 0;
#endif
};

struct LobbyMapPropertiesContainer
{
  STORM_REFL;
  LobbyMapProperties m_MapProperties;
};

struct LobbyMapInfo
{
  STORM_REFL;
  LobbyMapPropertiesContainer m_PropertiesInfo;
};

struct LobbyMapHeaderElem
{
  STORM_REFL;
};

struct LobbyLevelListElement
{
  std::string m_Name;

#ifdef NET_USE_PLAYER_LIMIT
  int m_PlayerCount = 0;
#endif

#ifdef NET_USE_SCORE_LIMIT
  int m_ScoreLimit = 0;
#endif

#ifdef NET_USE_SCORE_LIMIT
  int m_TimeLimit = 0;
#endif
};


class LobbyLevelList
{
public:
  LobbyLevelList();

private:
  std::vector<LobbyLevelListElement> m_Levels;
};
