

#include "GameClient/GameMode.h"
#include "GameClient/GameContainer.h"

#include "Engine/Shader/ShaderManager.h"

GameMode::GameMode() :
  m_Loaded(false)
{

}

GameMode::~GameMode()
{

}

void GameMode::Initialize(GameContainer & container)
{

}

void GameMode::OnAssetsLoaded(GameContainer & container)
{

}

void GameMode::Update(GameContainer & container)
{

}

void GameMode::Render(GameContainer & container)
{

}

bool GameMode::IsLoaded()
{
  return m_Loaded;
}

void GameMode::Step(GameContainer & container)
{
  if (m_Loaded == false)
  {
    if (m_Assets.LoadingComplete())
    {
      OnAssetsLoaded(container);
      m_Loaded = true;
    }
  }

  Update(container);
}

AssetBundle & GameMode::GetAssets()
{
  return m_Assets;
}
