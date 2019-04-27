#include "GameShared/GameSharedCommon.h"
#include "GameShared/GameLevelList.h"
#include "GameShared/GameLevelListAsset.refl.meta.h"

#include "Runtime/GenericResource/GenericResource.h"

#include "StormData/StormDataJson.h"

using LevelList = GenericResource<GameLevelListAsset>;
using LevelListPtr = GenericResourcePtr<GameLevelListAsset>;

GameLevelList::GameLevelList()
{
  m_LevelListResource = LevelList::Load("./LevelList.txt");
}

bool GameLevelList::IsLevelListLoaded() const
{
  return m_LevelListResource.IsLoaded();
}

void GameLevelList::PreloadAllLevels()
{
  auto level_list = m_LevelListResource.GetData();

  for (auto & level : level_list->m_Levels)
  {
    m_PreloadedMaps.emplace_back(MapResource::Load(level.m_Path.data()));
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
    ASSERT(false, "Invalid level index");
    return{};
  }

  return MapResource::Load(level_list->m_Levels[stage_index].m_Path.data());
}

const MapDef & GameLevelList::GetPreloadedMap(std::size_t stage_index) const
{
  return *m_PreloadedMaps[stage_index].GetData();
}

const MapPropertiesDef & GameLevelList::GetPreloadedMapProperties(std::size_t stage_index) const
{
  auto props = m_PreloadedMaps[stage_index].GetData()->m_PropertiesInfo.m_MapProperties.GetValue();
  if(props)
  {
    return *props;
  }

  static MapPropertiesDef default_props;
  return default_props;
}

const LevelListPtr & GameLevelList::GetLevelListAsset() const
{
  return m_LevelListResource;
}

std::size_t GameLevelList::GetNumLevels()
{
  auto level_list = m_LevelListResource.GetData();
  return level_list->m_Levels.size();
}
