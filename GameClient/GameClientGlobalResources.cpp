
#include "GameClient/GameClientGlobalResources.h"
#include "Engine/UI/Prototype/UISoundPrototypeEffects.h"
#include "Runtime/Entity/EntityResource.h"

GameClientGlobalResources::GameClientGlobalResources()
{
  TitleImage = TextureAsset::Load("./Images/GameTitle.png");

  UISoundEffects.m_ButtonHoverSfx = AudioAsset::Load("./Sounds/ButtonHover.wav");
  UISoundEffects.m_ButtonPressedSfx = AudioAsset::Load("./Sounds/ButtonClick.wav");
  UISoundEffects.m_MenuBackSfx = AudioAsset::Load("./Sounds/MenuBack.wav");

  Staging = UIResource::Load("./UIs/Staging.ui");
  Tutorial = UIResource::Load("./UIs/Tutorial.ui");

  PlayerEntity = EntityResource::Load("./Entities/Player.entity");

  MainMenuMusic = MusicAsset::Load("./Music/Menu.ogg");
  GameplayStart = MusicAsset::Load("./Music/Battle.ogg");
  GameplayLoop = MusicAsset::Load("./Music/Gameplay.ogg");
  VictoryMusic = MusicAsset::Load("./Music/Victory.ogg");
  DefeatMusic = MusicAsset::Load("./Music/Defeat.ogg");
}

bool GameClientGlobalResources::IsLoaded() const
{
  return
    m_Assets.AllLoadedSuccessfully() &&
    TitleImage->IsLoaded() &&
    PlayerEntity.IsLoaded() &&
    Staging.IsLoaded() &&
    Tutorial.IsLoaded() &&
    (MainMenuMusic->IsLoaded() || MainMenuMusic->IsError()) &&
    UISoundEffects.m_ButtonHoverSfx->IsLoaded() &&
    UISoundEffects.m_ButtonPressedSfx->IsLoaded() &&
    UISoundEffects.m_MenuBackSfx->IsLoaded();
}
