#pragma once

#include <string>
#include <vector>

#include <StormRefl/StormRefl.h>
#include <StormData/StormData.h>
#include "HurricaneDDS/DDSKey.h"

#include "LobbyConfig.h"

struct GamePlayerData
{
  STORM_REFL;
  DDSKey m_UserId;
  DDSKey m_EndpointId;
  std::string m_Name;

  int m_Admin;
  int m_Icon;
  int m_Title;
  int m_Celebration;
  bool m_NewPlayer;

#ifdef ENABLE_SQUADS
  std::string m_Squad;
#endif
};

struct GameStatsData
{
  STORM_REFL;
  int m_GamesPlayed = 0;
  int m_GamesWon = 0;
  int m_TimePlayed = 0;
};

#ifdef ENABLE_REWARDS

struct UserXPGain
{
  STORM_DATA_DEFAULT_CONSTRUCTION(UserXPGain);

  int m_GamesWon;
  int m_GamesWonCount;
  int m_GamesPlayed;
  int m_GamesPlayedCount;
  int m_Gifted;
  int m_XP;
};

struct UserRewards
{
  STORM_DATA_DEFAULT_CONSTRUCTION(UserRewards);

  std::vector<std::pair<std::string, std::string>> m_Icons;
  std::vector<std::string> m_Titles;
  std::vector<std::pair<std::string, int>> m_Celebrations;
  std::vector<std::string> m_AutoJoins;
};

#endif
