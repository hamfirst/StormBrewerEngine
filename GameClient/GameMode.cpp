

#include "GameClient/GameMode.h"
#include "GameClient/GameContainer.h"

#include "Engine/Shader/ShaderManager.h"

GameMode::GameMode(GameContainer & game) :
  m_GameContainer(game),
  m_Loaded(false)
{

}

GameMode::~GameMode()
{

}

void GameMode::Initialize()
{

}

void GameMode::OnAssetsLoaded()
{

}

void GameMode::Update()
{

}

void GameMode::Render()
{

}

bool GameMode::IsLoaded()
{
  return m_Loaded;
}

void GameMode::Step()
{
  if (m_Loaded == false)
  {
    if (m_Assets.LoadingComplete())
    {
      OnAssetsLoaded();
      m_Loaded = true;
    }
  }

  Update();
}

GameContainer & GameMode::GetContainer()
{
  return m_GameContainer;
}

AssetBundle & GameMode::GetAssets()
{
  return m_Assets;
}
