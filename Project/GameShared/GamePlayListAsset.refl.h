
#pragma once

#include "StormRefl/StormRefl.h"

#include "Game/GameNetworkData.refl.h"

struct PlaylistAssetElement
{
  STORM_REFL;

  std::string m_Name;
  std::vector<GameInitSettings> m_GameModes;
  int m_TeamSizes[kMaxTeams] = {};
  bool m_AllowParties = false;
  int m_TotalGameSize = 0;
};

struct PlaylistAsset
{
  STORM_REFL;
  std::vector<PlaylistAssetElement> m_Elements;
};

