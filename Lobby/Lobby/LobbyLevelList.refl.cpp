
#include "Lobby/LobbyLevelList.refl.meta.h"

#include "Foundation/Document/Document.h"
#include "Foundation/Document/DocumentCompiler.h"
#include "Foundation/Document/DocumentDefaultLoader.h"

#include "Runtime/Map/MapDef.refl.meta.h"

#include "GameShared/GameLevelListAsset.refl.meta.h"

#include "StormRefl/StormReflJsonStd.h"

#include "ProjectSettings/ProjectNetworkSettings.h"

LobbyLevelList g_LobbyLevelList;

LobbyLevelList::LobbyLevelList()
{
  DocumentDefaultLoader loader;
  DocumentCompiler document_compiler(&loader);

  auto document = document_compiler.GetDocument("LevelList.txt");
  auto document_json = document->GetDocumentJson();

  GameLevelListAsset level_list;
  StormReflParseJson(level_list, document_json.c_str());

  for(auto & level : level_list.m_Levels)
  {
    auto level_document = document_compiler.GetDocument(level.m_Path.c_str());
    auto level_document_json = level_document->GetDocumentJson();

    MapDefPropertiesOnly map_info;
    StormReflParseJson(map_info, level_document_json.c_str());

    if(map_info.m_PropertiesInfo.m_MapProperties.GetValue())
    {
      m_Levels.emplace_back(*map_info.m_PropertiesInfo.m_MapProperties.GetValue());
    }
    else
    {
      m_Levels.emplace_back();
    }

    m_LevelNames.emplace_back(level.m_Name);
  }
}

int LobbyLevelList::GetNumLevels() const
{
  return (int)m_Levels.size();
}

const std::string & LobbyLevelList::GetLevelName(int level_index) const
{
  return m_LevelNames[level_index];
}

const MapPropertiesDef & LobbyLevelList::GetLevelInfo(int level_index) const
{
  return m_Levels[level_index];
}
