#pragma once

#include "Engine/EngineCommon.h"
#include "Engine/UI/UIElementPtr.h"
#include "Engine/UI/UIElementGradient.refl.h"
#include "Engine/UI/UIElementText.refl.h"
#include "Engine/UI/UIElementShape.refl.h"
#include "Engine/UI/Prototype/UIPrototypeButton.h"
#include "Engine/UI/Prototype/UISoundPrototypeEffects.h"
#include "Engine/Asset/AudioAsset.h"

#include "Foundation/Lerp/LerpVar.h"

class UIManager;

class UIPrototypeConfirmPopup
{
public:

  UIPrototypeConfirmPopup(UIManager & manager, czstr name, NullOptPtr<UIElement> parent, const Box & box, czstr prompt, NullOptPtr<UISoundPrototypeEffects> sfx = nullptr);

  void Show();
  void Hide();
  void Toggle();
  void Cancel();
  bool IsShown() const;

  void SetOnOkayCallback(Delegate<void> && rhs);
  void SetOnCancelCallback(Delegate<void> && rhs);

  void SetBkgColor(const Color & color);
  void SetBorderColor(const Color & color);
  void SetTextColor(const Color & color);

protected:

  void Update();
private:

  UIElementPtr<UIElementGradient> m_Bkg;
  UIElementPtr<UIElementShape> m_Fader;
  UIElementPtr<UIElementShape> m_Border;
  UIElementPtr<UIElementText> m_Text;

  Optional<UIPrototypeButton> m_OkayButton;
  Optional<UIPrototypeButton> m_CancelButton;

  NullOptPtr<UISoundPrototypeEffects> m_Sfx;

  Delegate<void> m_OnOkay;
  Delegate<void> m_OnCancel;

  Color m_BkgColor;
  Color m_BorderColor;
  Color m_TextColor;

  LerpVar m_FaderLerp;
};

