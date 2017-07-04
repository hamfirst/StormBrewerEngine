
#include "GameClient/GameClientLevelLoader.h"

#include "GameClient/GameContainer.h"

GameClientLevelLoader::GameClientLevelLoader(GameContainer & game) :
  m_GameContainer(game)
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
  m_LoadCallback = std::move(load_complete);
  m_LoadToken = load_token;
  m_PendingLoadLevel = m_GameContainer.GetLevelList().LoadLevel(init_settings.m_StageIndex);
  m_PendingLoadLink = m_PendingLoadLevel.GetResource()->AddLoadCallback([this](NotNullPtr<MapResource> map_resource) { HandleLevelLoadComplete(); });
}

void GameClientLevelLoader::CancelLoading()
{
  m_PendingLoadLevel = {};
  m_PendingLoadLink = {};

  m_LoadCallback.Clear();
}

void GameClientLevelLoader::HandleLevelLoadComplete()
{
  m_LoadCallback(m_LoadToken, m_PendingLoadLevel);
  m_LoadedMapId = m_GameContainer.GetEngineState().LoadMap(m_PendingLoadLevel.GetResource());
}

