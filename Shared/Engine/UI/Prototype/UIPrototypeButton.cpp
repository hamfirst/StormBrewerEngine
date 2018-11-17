
#include "Engine/EngineCommon.h"
#include "Engine/UI/UIManager.h"
#include "Engine/UI/Prototype/UIPrototypeButton.h"
#include "Engine/Audio/AudioManager.h"

#include "Foundation/Lerp/LerpFuncs.h"

UIPrototypeButton::UIPrototypeButton(UIManager & manager, czstr name, NullOptPtr<UIElement> parent, const Box & box,
        czstr caption, NullOptPtr<UISoundPrototypeEffects> sfx, bool back_button) :
  m_Sfx(sfx),
  m_BkgColor(200, 200, 210, 255),
  m_BorderColor(150, 150, 150, 255),
  m_TextColor(30, 35, 67, 255),
  m_BkgHoverColor(250, 255, 195, 255),
  m_BorderHoverColor(0, 0, 0, 100),
  m_TextHoverColor(60, 60, 70, 255),
  m_BkgPressedColor(160, 180, 250, 255),
  m_BorderPressedColor(0, 0, 195, 255),
  m_TextPressedColor(10, 15, 47, 255),
  m_Alpha(1.0f),
  m_BackButton(back_button)
{
  auto size = box.Size();

  m_Bkg = manager.AllocateGradient(name, parent, {}, {});

  auto bkg = m_Bkg.Get();
  bkg->SetOnClickHandler([this](NotNullPtr<UIElement>)
  {
    if (m_Sfx)
    {
      g_AudioManager.PlayAudio(m_BackButton ? m_Sfx->m_MenuBackSfx : m_Sfx->m_ButtonPressedSfx);
    }
    else
    {
      g_AudioManager.PlayAudio(m_BackButton ? g_UIButtonBackSFX : g_UIButtonClickSFX);
    }

    m_OnClick();
  });

  bkg->SetOnUpdateHandler([this](NotNullPtr<UIElement>) { Update(); });
  bkg->SetOnStateChangeHandler([this](UIElementState prev_state, UIElementState new_state) { HandleStateChange(prev_state, new_state); });
  auto & bkg_data = bkg->GetData();
  bkg_data.m_Active = true;
  bkg_data.SetColor(m_BkgColor);
  bkg_data.SetBounds(box);
  bkg->SetActive();

  m_Border = manager.AllocateShape("border", bkg, {}, {});
  auto border = m_Border.Get();
  auto & border_data = border->GetData();
  border_data.m_Shape = kUIElementShapeRectangle;
  border_data.SetBounds(Box{ Vector2{0, 0}, size });

  m_Text = manager.AllocateText("caption", bkg, {}, {});
  auto text = m_Text.Get();
  auto & text_data = text->GetData();
  text_data.m_Text = caption;
  text_data.m_PositionX = (float)(size.x / 2);
  text_data.m_PositionY = (float)(size.y / 2);
  text_data.m_FontId = -1;
}

void UIPrototypeButton::SetOnClickCallback(Delegate<void> && rhs)
{
  m_OnClick = std::move(rhs);
}

void UIPrototypeButton::Update()
{
  float hover = m_HoverVal;
  float pressed = m_PressedVal;

  if (m_Bkg->GetState() == UIElementState::kHover)
  {
    hover = Easing::EaseOut(hover, EasingType::kElastic);
  }

  auto bkg_color = LerpColor(m_BkgColor, m_BkgHoverColor, hover);
  bkg_color = LerpColor(bkg_color, m_BkgPressedColor, pressed);
  bkg_color.a *= m_Alpha;
  m_Bkg->GetData().SetColor(bkg_color);

  auto text_color = LerpColor(m_TextColor, m_TextHoverColor, hover);
  text_color = LerpColor(text_color, m_TextPressedColor, pressed);
  text_color.a *= m_Alpha;
  m_Text->GetData().SetColor(text_color);

  auto border_color = LerpColor(m_BorderColor, m_BorderHoverColor, hover);
  border_color = LerpColor(border_color, m_BorderPressedColor, pressed);
  border_color.a *= m_Alpha;
  m_Border->GetData().SetColor(border_color);
}

void UIPrototypeButton::HandleStateChange(UIElementState prev_state, UIElementState new_state)
{
  switch (prev_state)
  {
  case UIElementState::kHover:
    m_HoverVal.LerpTo(0, 0.25f);
    break;
  case UIElementState::kPressed:
    m_PressedVal.LerpTo(0, 0.25f);
    break;
  }

  switch (new_state)
  {
  case UIElementState::kHover:
    m_HoverVal.LerpTo(1.0f, 0.25f);

    if (prev_state == UIElementState::kActive)
    {
      if(m_Sfx)
      {
        g_AudioManager.PlayAudio(m_Sfx->m_ButtonHoverSfx);
      }
      else
      {
        g_AudioManager.PlayAudio(g_UIButtonHoverSFX);
      }
    }

    break;
  case UIElementState::kPressed:
    m_PressedVal.LerpTo(1.0f, 0.25f);
    break;
  }
}

void UIPrototypeButton::SetBkgColor(const Color & color)
{
  m_BkgColor = color;
}

void UIPrototypeButton::SetBorderColor(const Color & color)
{
  m_BorderColor = color;
}

void UIPrototypeButton::SetTextColor(const Color & color)
{
  m_TextColor = color;
}

void UIPrototypeButton::SetBkgHoverColor(const Color & color)
{
  m_BkgHoverColor = color;
}

void UIPrototypeButton::SetBorderHoverColor(const Color & color)
{
  m_BorderHoverColor = color;
}

void UIPrototypeButton::SetTextHoverColor(const Color & color)
{
  m_TextHoverColor = color;
}

void UIPrototypeButton::SetBkgPressedColor(const Color & color)
{
  m_BkgPressedColor = color;
}

void UIPrototypeButton::SetBorderPressedColor(const Color & color)
{
  m_BorderPressedColor = color;
}

void UIPrototypeButton::SetTextPressedColor(const Color & color)
{
  m_TextPressedColor = color;
}

void UIPrototypeButton::SetAlpha(float alpha)
{
  m_Alpha = alpha;
}

void UIPrototypeButton::SetActive(bool active)
{
  m_Bkg->SetActive(active);
}
