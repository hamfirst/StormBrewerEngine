
#include "Engine/EngineCommon.h"
#include "Engine/UI/UIManager.h"
#include "Engine/UI/Prototype/UIPrototypeConfirmPopup.h"
#include "Engine/Audio/AudioManager.h"

UIPrototypeConfirmPopup::UIPrototypeConfirmPopup(UIManager & manager, czstr name, NullOptPtr<UIElement> parent, const Box & box, czstr prompt, NullOptPtr<UISoundPrototypeEffects> sfx) :
  m_Sfx(sfx),
  m_BkgColor(210, 210, 210, 255),
  m_BorderColor(150, 150, 150, 255),
  m_TextColor(255, 255, 255, 255)
{
  auto size = box.Size();

  m_Fader = manager.AllocateShape(name, parent);
  m_Fader->SetOnUpdateHandler([this](NotNullPtr<UIElement>) { Update(); });
  m_Fader->SetActive();
  auto & fader_data = m_Fader->GetData();
  fader_data.SetColor(Color(255, 255, 255, 0));
  fader_data.m_StartX = 0;
  fader_data.m_StartY = 0;
  fader_data.m_EndX = 10000;
  fader_data.m_EndY = 10000;
  fader_data.m_Shape = kUIElementShapeFilledRectangle;

  m_Bkg = manager.AllocateGradient("bkg", m_Fader, {}, {});

  auto bkg = m_Bkg.Get();
  auto & bkg_data = bkg->GetData();
  bkg_data.SetColor(m_BkgColor);
  bkg_data.SetBounds(box);

  m_Border = manager.AllocateShape("border", bkg, {}, {});
  auto border = m_Border.Get();
  auto & border_data = border->GetData();
  border_data.SetBounds(Box{ Vector2{ 0, 0 }, size });
  border_data.SetColor(m_BorderColor);
  border_data.m_Shape = kUIElementShapeRectangle;

  m_Text = manager.AllocateText("caption", bkg, {}, {});
  auto text = m_Text.Get();
  auto & text_data = text->GetData();
  text_data.m_Text = prompt;
  text_data.m_Centered = 1.0f;
  text_data.m_TextMode = 2.0f;
  text_data.m_PositionX = (float)(size.x / 2);
  text_data.m_PositionY = (float)(size.y / 2) + 20;
  text_data.m_FontId = -1;
  text_data.SetColor(m_TextColor);

  //UIManager & manager, czstr name, NullOptPtr<UIElement> parent, const Box & box, czstr caption, NullOptPtr<UISoundPrototypeEffects> sfx = nullptr

  m_OkayButton.Emplace(manager, "okay", bkg, Box{ Vector2(20, 10), Vector2(90, 35) }, "Okay", sfx);
  m_OkayButton->SetOnClickCallback([this]() { m_OnOkay(); });
  m_CancelButton.Emplace(manager, "cancel", bkg, Box{ Vector2(size.x - 90, 10), Vector2(size.x - 20, 35) }, "Cancel", sfx, true);
  m_CancelButton->SetOnClickCallback([this]() { Cancel(); });

  Hide();
}

void UIPrototypeConfirmPopup::Show()
{
  m_FaderLerp.LerpTo(0.9f, 0.3f);
}

void UIPrototypeConfirmPopup::Hide()
{
  m_FaderLerp.LerpTo(0.0f, 0.3f);
}

void UIPrototypeConfirmPopup::Toggle()
{
  if (m_FaderLerp.GetTarget() != 0)
  {
    Hide();
  }
  else
  {
    Show();
  }
}

void UIPrototypeConfirmPopup::Cancel()
{
  m_OnCancel();
  Hide();
}

bool UIPrototypeConfirmPopup::IsShown() const
{
  return m_FaderLerp.GetTarget() != 0;
}

void UIPrototypeConfirmPopup::Update()
{
  float fade_val = m_FaderLerp;
  
  if (fade_val == 0)
  {
    m_Fader->SetDisabled();
  }
  else
  {
    m_Fader->SetEnabled();
    m_Fader->GetData().m_ColorA = fade_val;

    auto bkg_color = m_BkgColor;
    bkg_color.a *= fade_val;
    m_Bkg->GetData().SetColor(bkg_color);

    auto border_color = m_BorderColor;
    border_color.a *= fade_val;
    m_Border->GetData().SetColor(border_color);

    auto text_color = m_TextColor;
    text_color.a *= powf(fade_val, 1.0f);
    m_Text->GetData().SetColor(text_color);
    m_Text->GetData().SetSecondaryColor(Color(0.0f, 0.0f, 0.0f, powf(fade_val, 5.0f)));

    m_OkayButton->SetAlpha(fade_val);
    m_CancelButton->SetAlpha(fade_val);
  }

  bool active = m_FaderLerp.GetTarget() != 0;
  m_OkayButton->SetActive(active);
  m_CancelButton->SetActive(active);
}

void UIPrototypeConfirmPopup::SetOnOkayCallback(Delegate<void> && rhs)
{
  m_OnOkay = std::move(rhs);
}

void UIPrototypeConfirmPopup::SetOnCancelCallback(Delegate<void> && rhs)
{
  m_OnCancel = std::move(rhs);
}

void UIPrototypeConfirmPopup::SetBkgColor(const Color & color)
{
  m_BkgColor = color;
}

void UIPrototypeConfirmPopup::SetBorderColor(const Color & color)
{
  m_BorderColor = color;
}

void UIPrototypeConfirmPopup::SetTextColor(const Color & color)
{
  m_TextColor = color;
}
