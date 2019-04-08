
#pragma once

#include <string>
#include <string_view>
#include <vector>

#include "StormRefl/StormRefl.h"

#include "Game/GameNetworkData.refl.h"

#include "ProjectSettings/ProjectNetworkSettings.h"

struct LobbyMapProperties
{
  STORM_REFL;

  int m_TeamCount = kMaxTeams;

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

  int m_TeamCount = kMaxTeams;

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

  int GetNumLevels() const;
  const LobbyLevelListElement & GetLevelInfo(int level_index) const;

private:
  std::vector<LobbyLevelListElement> m_Levels;
};

extern LobbyLevelList g_LobbyLevelList;
