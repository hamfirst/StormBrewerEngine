
#include "GameClient/GameClientGlobalResources.h"
#include "Engine/UI/Prototype/UISoundPrototypeEffects.h"
#include "Runtime/Entity/EntityResource.h"

GameClientGlobalResources::GameClientGlobalResources()
{
  TitleImage = TextureAsset::Load("./Images/GameTitle.png");
  UISoundEffects.m_ButtonHoverSfx = AudioAsset::Load("./Sounds/ButtonHover.wav");
  UISoundEffects.m_ButtonPressedSfx = AudioAsset::Load("./Sounds/ButtonClick.wav");
}

bool GameClientGlobalResources::IsLoaded() const
{
  return
    m_Assets.AllLoadedSuccessfully() &&
    TitleImage->IsLoaded() &&
    UISoundEffects.m_ButtonHoverSfx->IsLoaded() &&
    UISoundEffects.m_ButtonPressedSfx->IsLoaded();
}

