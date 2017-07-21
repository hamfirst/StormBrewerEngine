#pragma once

#include "Engine/EngineCommon.h"
#include "Engine/UI/UIElementPtr.h"
#include "Engine/UI/UIElementGradient.refl.h"
#include "Engine/UI/UIElementText.refl.h"
#include "Engine/UI/UIElementShape.refl.h"
#include "Engine/UI/Prototype/UISoundPrototypeEffects.h"
#include "Engine/Asset/AudioAsset.h"

#include "Foundation/Lerp/LerpVar.h"

class UIManager;

class UIPrototypeSlider
{
public:

  UIPrototypeSlider(UIManager & manager, czstr name, NullOptPtr<UIElement> parent, const Box & box, czstr caption, NullOptPtr<UISoundPrototypeEffects> sfx = nullptr, float initial_val = 0.5f);

  void SetOnClickCallback(Delegate<void> && rhs);

  void SetValue(float val);

  void SetBkgColor(const Color & color);
  void SetBorderColor(const Color & color);

  void SetBkgHoverColor(const Color & color);
  void SetBorderHoverColor(const Color & color);

  void SetBkgPressedColor(const Color & color);
  void SetBorderPressedColor(const Color & color);

protected:

  void Update();
  void HandleStateChange(UIElementState prev_state, UIElementState new_state);

private:

  UIElementPtr<UIElementGradient> m_Bkg;
  UIElementPtr<UIElementShape> m_Border;
  UIElementPtr<UIElementShape> m_Track;
  UIElementPtr<UIElementShape> m_PipBorder;
  UIElementPtr<UIElementShape> m_PipBkg;

  NullOptPtr<UISoundPrototypeEffects> m_Sfx;

  float m_Val;
  bool m_Dragging;

  Delegate<void> m_OnClick;
  LerpVar m_PressedVal;
  LerpVar m_HoverVal;

  Color m_BkgColor;
  Color m_BorderColor;

  Color m_BkgHoverColor;
  Color m_BorderHoverColor;

  Color m_BkgPressedColor;
  Color m_BorderPressedColor;
};

