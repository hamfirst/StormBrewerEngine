#pragma once

#include "Foundation/Common.h"

#include "Game/GameNetworkData.refl.h"
#include "Game/GameStage.h"

#include "Runtime/Map/MapResource.h"

#include "Shared/AssetBundle/AssetBundle.h"

class GameLevelList
{
public:

  GameLevelList();
  bool IsLevelListLoaded();

  void PreloadAllLevels();
  bool IsPreloadComplete();

  Map LoadLevel(std::size_t stage_index);
  std::size_t GetNumLevels();

private:

  Any m_LevelListResource;
  AssetBundle m_PreloadedAssets;
};

