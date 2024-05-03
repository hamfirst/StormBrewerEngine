
#pragma once

#include <string>
#include <string_view>
#include <vector>

#include "StormRefl/StormRefl.h"

#include "Game/NetworkEvents/GameNetworkData.refl.h"
#include "Runtime/Map/MapDef.refl.h"

#include "ProjectSettings/ProjectNetworkSettings.h"

class LobbyLevelList
{
public:
  LobbyLevelList();

  int GetNumLevels() const;
  const std::string & GetLevelName(int level_index) const;
  const MapPropertiesDef & GetLevelInfo(int level_index) const;

private:
  std::vector<MapPropertiesDef> m_Levels;
  std::vector<std::string> m_LevelNames;
};

extern LobbyLevelList g_LobbyLevelList;
