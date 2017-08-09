#pragma once

#include "Engine/Asset/AssetBundle.h"
#include "Engine/Asset/TextureAsset.h"
#include "Engine/Asset/AudioAsset.h"
#include "Runtime/Sprite/SpriteResource.h"
#include "Runtime/Entity/EntityResource.h"
#include "Engine/UI/Prototype/UISoundPrototypeEffects.h"

class GameClientGlobalResources
{
public:

  GameClientGlobalResources();
  bool IsLoaded() const;

  AssetReference<TextureAsset> TitleImage;
  UISoundPrototypeEffects UISoundEffects;

private:

  AssetBundle m_Assets;
};

