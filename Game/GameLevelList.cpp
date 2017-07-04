
#include "Game/GameLevelList.h"
#include "Game/GameLevelListAsset.refl.meta.h"

#include "Runtime/GenericResource.h"

#include "StormData/StormDataJson.h"

using LevelList = GenericResource<GameLevelListAsset>;
using LevelListPtr = GenericResourcePtr<GameLevelListAsset>;

GameLevelList::GameLevelList()
{
  m_LevelListResource = Any(LevelList::Load("./LevelList.txt"));
}

bool GameLevelList::IsLevelListLoaded()
{
  auto level_list_asset = m_LevelListResource.Get<LevelListPtr>();
  return level_list_asset->GetResource()->IsLoaded();
}

void GameLevelList::PreloadAllLevels()
{
  auto level_list_asset = m_LevelListResource.Get<LevelListPtr>();
  auto level_list = level_list_asset->GetData();

  for (auto & level : level_list->m_Levels)
  {
    m_PreloadedAssets.LoadAsset<MapResource>(level.data());
  }
}

bool GameLevelList::IsPreloadComplete()
{
  return m_PreloadedAssets.AllLoadedSuccessfully();
}

Map GameLevelList::LoadLevel(std::size_t stage_index)
{
  auto level_list_asset = m_LevelListResource.Get<LevelListPtr>();
  auto level_list = level_list_asset->GetData();

  if (stage_index >= level_list->m_Levels.size())
  {
    return{};
  }

  return MapResource::Load(level_list->m_Levels[stage_index].data());
}

std::size_t GameLevelList::GetNumLevels()
{
  auto level_list_asset = m_LevelListResource.Get<LevelListPtr>();
  auto level_list = level_list_asset->GetData();

  return level_list->m_Levels.size();
}
