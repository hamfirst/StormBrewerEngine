#pragma once

#include "Foundation/Common.h"

#include "Game/GameNetworkData.refl.h"
#include "Game/GameLevelListAsset.refl.h"
#include "Game/GameStage.h"

#include "Runtime/Map/MapResource.h"
#include "Runtime/GenericResource/GenericResource.h"

using LevelListPtr = GenericResourcePtr<GameLevelListAsset>;

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

  LevelListPtr m_LevelListResource;
  std::vector<Map> m_PreloadedMaps;
};

