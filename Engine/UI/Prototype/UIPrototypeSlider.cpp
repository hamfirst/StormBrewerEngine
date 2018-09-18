
#include "Engine/EngineCommon.h"
#include "Engine/UI/UIManager.h"
#include "Engine/UI/Prototype/UIPrototypeSlider.h"
#include "Engine/Audio/AudioManager.h"

UIPrototypeSlider::UIPrototypeSlider(UIManager & manager, czstr name, NullOptPtr<UIElement> parent, const Box & box, czstr caption, NullOptPtr<UISoundPrototypeEffects> sfx, float initial_val) :
  m_Sfx(sfx),
  m_Dragging(false),
  m_BkgColor(245, 245, 245, 255),
  m_BorderColor(150, 150, 150, 255),
  m_BkgHoverColor(250, 255, 195, 255),
  m_BorderHoverColor(0, 0, 0, 100),
  m_BkgPressedColor(160, 180, 250, 255),
  m_BorderPressedColor(0, 0, 195, 255)
{
  auto size = box.Size();

  m_Bkg = manager.AllocateGradient(name, parent, {}, {});
  auto bkg = m_Bkg.Get();
  bkg->SetOnClickHandler([this](NotNullPtr<UIElement>) { m_OnClick(); });
  bkg->SetOnUpdateHandler([this](NotNullPtr<UIElement>) { Update(); });
  auto & bkg_data = bkg->GetData();
  bkg_data.m_Active = true;
  bkg_data.SetColor(m_BkgColor);
  bkg_data.SetBounds(box);
  bkg->SetActive();

  m_Track = manager.AllocateShape("track", bkg);
  auto & track_data = m_Track->GetData();
  track_data.SetColor(Color(0, 0, 0, 255));
  track_data.m_StartX = 3;
  track_data.m_StartY = box.Size().y / 2.0f;
  track_data.m_EndX = box.Size().x - 6.0f;
  track_data.m_EndY = box.Size().y / 2.0f;

  m_Border = manager.AllocateShape("border", bkg, {}, {});
  auto border = m_Border.Get();
  auto & border_data = border->GetData();
  border_data.SetBounds(Box{ Vector2{ 0, 0 }, size });

  auto height = box.Size().y;

  m_PipBkg = manager.AllocateShape("pip", bkg);
  auto & pip_data = m_PipBkg->GetData();
  pip_data.m_StartY = height / 2 - 10.0f;
  pip_data.m_EndY = pip_data.m_StartY + 20.0f;
  pip_data.m_Shape = kUIElementShapeFilledRectangle;
  m_PipBkg->SetOnStateChangeHandler([this](UIElementState prev_state, UIElementState new_state) { HandleStateChange(prev_state, new_state); });

  m_PipBorder = manager.AllocateShape("pip_border", m_PipBkg.Get());
  auto & pip_border_data = m_PipBorder->GetData();
  pip_border_data.m_EndX = 10;
  pip_border_data.m_EndY = 20;

  SetValue(initial_val);
}

void UIPrototypeSlider::SetOnClickCallback(Delegate<void> && rhs)
{
  m_OnClick = std::move(rhs);
}

void UIPrototypeSlider::SetValue(float val)
{
  m_Val = val;

  auto & bkg_data = m_Bkg->GetData();
  auto width = bkg_data.m_EndX - bkg_data.m_StartX - 6;

  auto & pip_data = m_PipBkg->GetData();
  pip_data.m_StartX = (int)(width * val) - 5.0f + 3.0f;
  pip_data.m_EndX = pip_data.m_StartX + 10.0f;
}

void UIPrototypeSlider::Update()
{
  float hover = m_HoverVal;
  float pressed = m_PressedVal;

  auto bkg_color = LerpColor(m_BkgColor, m_BkgHoverColor, hover);
  bkg_color = LerpColor(bkg_color, m_BkgPressedColor, pressed);
  m_PipBkg->GetData().SetColor(bkg_color);

  auto border_color = LerpColor(m_BorderColor, m_BorderHoverColor, hover);
  border_color = LerpColor(border_color, m_BorderPressedColor, pressed);
  m_PipBorder->GetData().SetColor(border_color);
}

void UIPrototypeSlider::HandleStateChange(UIElementState prev_state, UIElementState new_state)
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

    if (m_Sfx)
    {
      g_AudioManager.PlayAudio(m_Sfx->m_ButtonPressedSfx);
    }
    break;
  }
}

void UIPrototypeSlider::SetBkgColor(const Color & color)
{
  m_BkgColor = color;
}

void UIPrototypeSlider::SetBorderColor(const Color & color)
{
  m_BorderColor = color;
}

void UIPrototypeSlider::SetBkgHoverColor(const Color & color)
{
  m_BkgHoverColor = color;
}

void UIPrototypeSlider::SetBorderHoverColor(const Color & color)
{
  m_BorderHoverColor = color;
}

void UIPrototypeSlider::SetBkgPressedColor(const Color & color)
{
  m_BkgPressedColor = color;
}

void UIPrototypeSlider::SetBorderPressedColor(const Color & color)
{
  m_BorderPressedColor = color;
}
