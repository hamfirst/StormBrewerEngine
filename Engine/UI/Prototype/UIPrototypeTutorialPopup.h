#pragma once

#include "Engine/EngineCommon.h"
#include "Engine/UI/UIElementPtr.h"
#include "Engine/UI/UIElementTextureSlice.refl.h"
#include "Engine/UI/UIElementText.refl.h"
#include "Engine/UI/UIElementShape.refl.h"
#include "Engine/UI/Prototype/UIPrototypeButton.h"
#include "Engine/UI/Prototype/UISoundPrototypeEffects.h"
#include "Engine/Asset/AudioAsset.h"

#include "Foundation/Lerp/LerpVar.h"

class UIManager;

class UIPrototypeTutorialPopup
{
public:

  UIPrototypeTutorialPopup(UIManager & manager, czstr name, NullOptPtr<UIElement> parent, const Box & box, czstr prompt, NullOptPtr<UISoundPrototypeEffects> sfx = nullptr);

  void Show();
  void Hide();
  void Toggle();

  void SetOnOkayCallback(Delegate<void> && rhs);

  void SetBkgColor(const Color & color);
  void SetTextColor(const Color & color);

  void AttachText(czstr name, const UIElementTextInitData & init_data = {}, const UIElementTextData & data = {});
  void AttachImage(czstr name, const UIElementFullTextureInitData & init_data = {}, const UIElementFullTextureData & data = {});

protected:

  void Update();
private:

  UIElementPtr<UIElementTextureSlice> m_Bkg;
  UIElementPtr<UIElementShape> m_Fader;
  UIElementPtr<UIElementText> m_Text;

  std::vector<UIElementPtr<UIElementText>> m_ExtraText;
  std::vector<UIElementPtr<UIElementFullTexture>> m_ExtraImages;

  Optional<UIPrototypeButton> m_OkayButton;

  NullOptPtr<UISoundPrototypeEffects> m_Sfx;

  Delegate<void> m_OnOkay;

  Color m_BkgColor;
  Color m_TextColor;

  LerpVar m_FaderLerp;
};

