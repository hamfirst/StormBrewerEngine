#pragma once

#include "Engine/Asset/AssetBundle.h"
#include "Engine/Asset/TextureAsset.h"
#include "Engine/Asset/AudioAsset.h"
#include "Engine/Asset/MusicAsset.h"
#include "Engine/UI/Prototype/UISoundPrototypeEffects.h"

#include "Runtime/Sprite/SpriteResource.h"
#include "Runtime/Entity/EntityResource.h"
#include "Runtime/UI/UIResource.h"
#include "Runtime/VisualEffect/VisualEffectResource.h"

class GameClientGlobalResources
{
public:

  GameClientGlobalResources();
  bool IsLoaded() const;

  AssetReference<TextureAsset> TitleImage;
  UISoundPrototypeEffects UISoundEffects;

  UIResourcePtr Staging;
  UIResourcePtr Tutorial;

  EntityResourcePtr PlayerEntity;

  AssetReference<MusicAsset> MainMenuMusic;
  AssetReference<MusicAsset> GameplayStart;
  AssetReference<MusicAsset> GameplayLoop;
  AssetReference<MusicAsset> VictoryMusic;
  AssetReference<MusicAsset> DefeatMusic;

private:

  AssetBundle m_Assets;
};

