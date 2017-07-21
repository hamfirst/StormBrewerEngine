#pragma once

#include "Engine/EngineCommon.h"
#include "Engine/UI/UIElementPtr.h"
#include "Engine/UI/UIElementGradient.refl.h"
#include "Engine/UI/UIElementText.refl.h"
#include "Engine/UI/UIElementShape.refl.h"
#include "Engine/UI/Prototype/UISoundPrototypeEffects.h"
#include "Engine/Asset/AudioAsset.h"
#include "Engine/Input/TextInputContext.h"
#include "Engine/Window/Window.h"

#include "Foundation/Lerp/LerpVar.h"

class UIManager;

class UIPrototypeTextInput
{
public:

  UIPrototypeTextInput(UIManager & manager, std::shared_ptr<TextInputContext> && input_contex, czstr name, NullOptPtr<UIElement> parent, const Box & box, czstr prompt, NullOptPtr<UISoundPrototypeEffects> sfx = nullptr);

  void SetOnClickCallback(Delegate<void> && rhs);
  void MakeCurrent();

  TextInputContext & GetInputContext();

  void SetBkgColor(const Color & color);
  void SetBorderColor(const Color & color);
  void SetTextColor(const Color & color);

  void SetBkgHoverColor(const Color & color);
  void SetBorderHoverColor(const Color & color);
  void SetTextHoverColor(const Color & color);

  void SetBkgPressedColor(const Color & color);
  void SetBorderPressedColor(const Color & color);
  void SetTextPressedColor(const Color & color);

protected:

  void Update();
  void Clicked();
  void HandleStateChange(UIElementState prev_state, UIElementState new_state);

private:

  UIElementPtr<UIElementGradient> m_Bkg;
  UIElementPtr<UIElementShape> m_Border;
  UIElementPtr<UIElementTextInput> m_Text;

  NullOptPtr<UISoundPrototypeEffects> m_Sfx;

  Delegate<void> m_OnClick;
  LerpVar m_PressedVal;
  LerpVar m_HoverVal;

  Color m_BkgColor;
  Color m_BorderColor;
  Color m_TextColor;

  Color m_BkgHoverColor;
  Color m_BorderHoverColor;
  Color m_TextHoverColor;

  Color m_BkgPressedColor;
  Color m_BorderPressedColor;
  Color m_TextPressedColor;
};

