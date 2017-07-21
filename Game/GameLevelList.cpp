
#include "Game/GameLevelList.h"
#include "Game/GameLevelListAsset.refl.meta.h"

#include "Runtime/GenericResource/GenericResource.h"

#include "StormData/StormDataJson.h"

using LevelList = GenericResource<GameLevelListAsset>;
using LevelListPtr = GenericResourcePtr<GameLevelListAsset>;

GameLevelList::GameLevelList()
{
  m_LevelListResource = LevelList::Load("./LevelList.txt");
}

bool GameLevelList::IsLevelListLoaded()
{
  return m_LevelListResource.IsLoaded();
}

void GameLevelList::PreloadAllLevels()
{
  auto level_list = m_LevelListResource.GetData();

  for (auto & level : level_list->m_Levels)
  {
    m_PreloadedMaps.emplace_back(MapResource::Load(level.data()));
  }
}

bool GameLevelList::IsPreloadComplete()
{
  return std::all_of(m_PreloadedMaps.begin(), m_PreloadedMaps.end(), [](const Map & elem) { return elem.IsLoaded(); });
}

Map GameLevelList::LoadLevel(std::size_t stage_index)
{
  auto level_list = m_LevelListResource.GetData();

  if (stage_index >= level_list->m_Levels.size())
  {
    return{};
  }

  return MapResource::Load(level_list->m_Levels[stage_index].data());
}

std::size_t GameLevelList::GetNumLevels()
{
  auto level_list = m_LevelListResource.GetData();
  return level_list->m_Levels.size();
}
