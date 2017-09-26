
#include "GameClient/GameGlobalResources.h"

#include "Engine/Asset/TextureAsset.h"

GameGlobalResources::GameGlobalResources()
{
  m_AssetBundle.LoadAsset<TextureAsset>("./Images/stormbrewers_logo.png");
}

bool GameGlobalResources::AreAllAssetsLoaded()
{
  return true;
  //return m_AssetBundle.AllLoadedSuccessfully();
}

