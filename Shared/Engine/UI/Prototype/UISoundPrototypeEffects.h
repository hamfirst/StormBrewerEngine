#pragma once

#include "Engine/Asset/AudioAsset.h"
#include "Runtime/Asset/Asset.h"

EXTERN_GLOBAL_ASSET(AssetReference<AudioAsset>, g_UIButtonClickSFX);
EXTERN_GLOBAL_ASSET(AssetReference<AudioAsset>, g_UIButtonHoverSFX);
EXTERN_GLOBAL_ASSET(AssetReference<AudioAsset>, g_UIButtonBackSFX);

struct UISoundPrototypeEffects
{
  AssetReference<AudioAsset> m_ButtonHoverSfx;
  AssetReference<AudioAsset> m_ButtonPressedSfx;
  AssetReference<AudioAsset> m_MenuBackSfx;
};
