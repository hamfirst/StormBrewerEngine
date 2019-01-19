#pragma once

#include "Foundation/Common.h"

#include "StormRefl/StormRefl.h"

#include "Game/GameNetworkData.refl.h"

struct GameLevelInfo
{
    STORM_REFL;
    std::string m_Path = "./Maps/Test.map";
    std::string m_Name = "Test Map";
    std::string m_Description = "Test Map";
    std::string m_MapImage = "./Images/UI/DefaultMapImage.png";

    int m_MaxPlayers = kMaxPlayers;

#ifdef NET_USE_ROUND_TIMER
    int m_MaxTime = kMaxRoundTimer;
#endif

#ifdef NET_USE_SCORE
    int m_MaxScore = kMaxScore;
#endif
};

struct GameLevelListAsset
{
  STORM_REFL;
  std::vector<GameLevelInfo> m_Levels;
};
