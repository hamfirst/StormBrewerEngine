#pragma once

#include "Engine/EngineCommon.h"
#include "Engine/UI/UIElementPtr.h"
#include "Engine/UI/UIElementFullTexture.refl.h"
#include "Engine/UI/Prototype/UISoundPrototypeEffects.h"
#include "Engine/Asset/AudioAsset.h"
#include "Engine/Window/Window.h"

#include "Foundation/Lerp/LerpVar.h"

class UIManager;

class UIPrototypeFullscreenButton
{
public:

  UIPrototypeFullscreenButton(UIManager & manager, czstr name, NullOptPtr<UIElement> parent, const Vector2 & pos, const Window & window, NullOptPtr<UISoundPrototypeEffects> sfx = nullptr);

  void SetAlpha(float alpha);

protected:

  void Update();
  void HandleStateChange(UIElementState prev_state, UIElementState new_state);
  void HandleClick();

private:
  const Window & m_Window;

  UIElementPtr<UIElementFullTexture> m_ImgEnabled;
  NullOptPtr<UISoundPrototypeEffects> m_Sfx;

  float m_Alpha;
};

