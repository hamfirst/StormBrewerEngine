#pragma once

#include <string>
#include <vector>

#include <StormRefl/StormRefl.h>
#include <StormData/StormData.h>

<<<<<<< HEAD
=======
#include "HurricaneDDS/DDSKey.h"

#include "LobbyConfig.h"

struct GamePlayerData
{
  STORM_REFL;
  DDSKey m_UserId;
  DDSKey m_EndpointId;
  std::string m_Name;

  int m_Admin;
  int m_Celebration;
  bool m_NewPlayer;

#ifdef ENABLE_SQUADS
  std::string m_Squad;
#endif
};

>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
struct GameInstanceData
{
  STORM_REFL;
  std::string m_Name;
  std::string m_Map;

  int m_TimeLimit = 0;
  int m_ScoreLimit = 0;
  int m_PlayerLimit = 0;
};

struct GameStatsData
{
  STORM_REFL;
  int m_GamesPlayed = 0;
  int m_GamesWon = 0;
<<<<<<< HEAD
  int m_UBGoals = 0;
  int m_UBAssists = 0;
  int m_DBGoals = 0;
  int m_DBAssists = 0;
  int m_TimePlayed = 0;
};

=======
  int m_TimePlayed = 0;
};

#ifdef ENABLE_REWARDS
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
struct UserXPGain
{
  STORM_DATA_DEFAULT_CONSTRUCTION(UserXPGain);

<<<<<<< HEAD
  int m_Goals;
  int m_GoalsCount;
  int m_Assists;
  int m_AssistsCount;
=======
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
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
<<<<<<< HEAD
=======

#endif
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
