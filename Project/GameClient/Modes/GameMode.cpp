#include "GameClient/GameClientCommon.h"
#include "GameClient/Modes/GameMode.h"
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

void GameMode::Deinit()
{

}

void GameMode::OnAssetsLoaded()
{

}

void GameMode::InputEvent()
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
  return m_Assets.LoadingComplete();
}

void GameMode::Step()
{
  if (m_Loaded == false)
  {
    if (IsLoaded())
    {
      OnAssetsLoaded();
      m_Loaded = true;
    }
  }

  Update();
}

bool GameMode::AssetLoadingComplete()
{
  return m_Loaded;
}

GameContainer & GameMode::GetContainer()
{
  return m_GameContainer;
}

AssetBundle & GameMode::GetAssets()
{
  return m_Assets;
}
