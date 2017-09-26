#pragma once

#include "Engine/EngineCommon.h"
#include "Engine/UI/UIElementPtr.h"
#include "Engine/UI/UIElementFullTexture.refl.h"
#include "Engine/UI/Prototype/UISoundPrototypeEffects.h"
#include "Engine/Asset/AudioAsset.h"

#include "Foundation/Lerp/LerpVar.h"

class UIManager;

class UIPrototypeMuteButton
{
public:

  UIPrototypeMuteButton(UIManager & manager, czstr name, NullOptPtr<UIElement> parent, const Vector2 & pos, bool music_only, NullOptPtr<UISoundPrototypeEffects> sfx = nullptr);

  void SetAlpha(float alpha);

protected:

  void Update();
  void HandleStateChange(UIElementState prev_state, UIElementState new_state);
  void HandleClick();

private:

  UIElementPtr<UIElementFullTexture> m_ImgEnabled;
  UIElementPtr<UIElementFullTexture> m_ImgDisabled;
  NullOptPtr<UISoundPrototypeEffects> m_Sfx;

  float m_Alpha;
  bool m_MusicOnly;
};

