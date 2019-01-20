#include "GameClient/GameClientCommon.h"
#include "GameClient/GameClientLevelLoader.h"

#include "GameClient/GameContainer.h"

#include "Engine/Map/MapInstance.h"

GameClientLevelLoader::GameClientLevelLoader(GameContainer & game) :
  m_GameContainer(game),
  m_LoadComplete(false)
{
  
}

GameClientLevelLoader::~GameClientLevelLoader()
{
  if (m_LoadedMapId)
  {
    m_GameContainer.GetEngineState().UnloadMap(m_LoadedMapId.Value());
  }
}

void GameClientLevelLoader::LoadLevel(const GameInitSettings & init_settings, uint64_t load_token, LevelLoadCallback && load_complete)
{
  if (m_LoadedMapId)
  {
    m_GameContainer.GetEngineState().UnloadMap(m_LoadedMapId.Value());
  }

  m_LoadComplete = false;
  m_LoadCallback = std::move(load_complete);
  m_LoadToken = load_token;
  m_PendingLoadLevel = m_GameContainer.GetLevelList().LoadLevel(init_settings.m_StageIndex);
  m_PendingLoadLink = m_PendingLoadLevel.GetResource()->AddLoadCallback(
      [this](NotNullPtr<MapResource> map_resource) { HandleLevelLoadComplete(); });
}

void GameClientLevelLoader::FinalizeLevel()
{
  auto map_instance = m_GameContainer.GetEngineState().GetMapInstance(m_LoadedMapId.Value());
  if (map_instance)
  {
    map_instance->Init(m_GameContainer);
  }
}

void GameClientLevelLoader::CancelLoading()
{
  m_PendingLoadLevel = {};
  m_PendingLoadLink = {};

  m_LoadCallback.Clear();
}

void GameClientLevelLoader::HandleLevelLoadComplete()
{
  if (m_LoadComplete)
  {
    return;
  }

  m_LoadCallback(m_LoadToken, m_PendingLoadLevel);
  m_LoadedMapId = m_GameContainer.GetEngineState().LoadMap(m_PendingLoadLevel.GetResource());
  m_LoadComplete = true;
}

