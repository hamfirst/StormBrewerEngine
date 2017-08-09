
#include "Engine/EngineCommon.h"
#include "Engine/UI/UIManager.h"
#include "Engine/UI/Prototype/UIPrototypeTextInput.h"
#include "Engine/Audio/AudioManager.h"

UIPrototypeTextInput::UIPrototypeTextInput(UIManager & manager, czstr name, 
                                           NullOptPtr<UIElement> parent, const Box & box, czstr prompt, NullOptPtr<UISoundPrototypeEffects> sfx) :
  m_Sfx(sfx),
  m_BkgColor(245, 245, 245, 255),
  m_BorderColor(150, 150, 150, 255),
  m_TextColor(30, 35, 67, 255),
  m_BkgHoverColor(250, 255, 195, 255),
  m_BorderHoverColor(0, 0, 0, 100),
  m_TextHoverColor(60, 60, 70, 255),
  m_BkgPressedColor(160, 180, 250, 255),
  m_BorderPressedColor(0, 0, 195, 255),
  m_TextPressedColor(10, 15, 47, 255)
{
  auto size = box.Size();

  m_Bkg = manager.AllocateGradient(name, parent, {}, {});

  auto bkg = m_Bkg.Get();
  bkg->SetOnClickHandler([this](NotNullPtr<UIElement>) { Clicked(); });
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
  border_data.SetBounds(Box{ Vector2{ 0, 0 }, size });

  m_Text = manager.AllocateTextInput("text", bkg, {}, {});
  auto text = m_Text.Get();
  auto & text_data = text->GetData();
  text_data.m_Centered = 1.0f;
  text_data.m_PositionX = (float)(size.x / 2);
  text_data.m_PositionY = (float)(size.y / 2);
  text_data.m_FontId = -1;
  text_data.m_Prompt = prompt;
}

void UIPrototypeTextInput::SetOnClickCallback(Delegate<void> && rhs)
{
  m_OnClick = std::move(rhs);
}

void UIPrototypeTextInput::MakeCurrent()
{
  auto active_area = m_Bkg->GetActiveArea();
  if (active_area)
  {
    m_Text->GetInputContext().MakeCurrent(&active_area.Value());
  }
}

TextInputContext & UIPrototypeTextInput::GetInputContext()
{
  return m_Text->GetInputContext();
}

void UIPrototypeTextInput::Update()
{
  float hover = m_HoverVal;
  float pressed = m_PressedVal;

  auto bkg_color = LerpColor(m_BkgColor, m_BkgHoverColor, hover);
  bkg_color = LerpColor(bkg_color, m_BkgPressedColor, pressed);
  m_Bkg->GetData().SetColor(bkg_color);

  auto text_color = LerpColor(m_TextColor, m_TextHoverColor, hover);
  text_color = LerpColor(text_color, m_TextPressedColor, pressed);
  m_Text->GetData().SetColor(text_color);

  auto border_color = LerpColor(m_BorderColor, m_BorderHoverColor, hover);
  border_color = LerpColor(border_color, m_BorderPressedColor, pressed);
  m_Border->GetData().SetColor(border_color);
}

void UIPrototypeTextInput::Clicked()
{
  MakeCurrent();
  m_OnClick();
}

void UIPrototypeTextInput::HandleStateChange(UIElementState prev_state, UIElementState new_state)
{
  switch (prev_state)
  {
  case UIElementState::kHover:
    m_HoverVal.LerpTo(0, 0.01f);
    break;
  case UIElementState::kPressed:
    m_PressedVal.LerpTo(0, 0.01f);
    break;
  }

  switch (new_state)
  {
  case UIElementState::kHover:
    m_HoverVal.LerpTo(1.0f, 0.1f);

    if (m_Sfx)
    {
      g_AudioManager.PlayAudio(m_Sfx->m_ButtonHoverSfx);
    }
    break;
  case UIElementState::kPressed:
    m_PressedVal.LerpTo(1.0f, 0.1f);
    break;
  }
}

void UIPrototypeTextInput::SetBkgColor(const Color & color)
{
  m_BkgColor = color;
}

void UIPrototypeTextInput::SetBorderColor(const Color & color)
{
  m_BorderColor = color;
}

void UIPrototypeTextInput::SetTextColor(const Color & color)
{
  m_TextColor = color;
}

void UIPrototypeTextInput::SetBkgHoverColor(const Color & color)
{
  m_BkgHoverColor = color;
}

void UIPrototypeTextInput::SetBorderHoverColor(const Color & color)
{
  m_BorderHoverColor = color;
}

void UIPrototypeTextInput::SetTextHoverColor(const Color & color)
{
  m_TextHoverColor = color;
}

void UIPrototypeTextInput::SetBkgPressedColor(const Color & color)
{
  m_BkgPressedColor = color;
}

void UIPrototypeTextInput::SetBorderPressedColor(const Color & color)
{
  m_BorderPressedColor = color;
}

void UIPrototypeTextInput::SetTextPressedColor(const Color & color)
{
  m_TextPressedColor = color;
}
