
#include "Engine/EngineCommon.h"
#include "Engine/UI/UIManager.h"
#include "Engine/UI/Prototype/UIPrototypeFullscreenButton.h"
#include "Engine/Audio/AudioManager.h"

#include "Foundation/Lerp/LerpFuncs.h"

UIPrototypeFullscreenButton::UIPrototypeFullscreenButton(UIManager & manager, czstr name, NullOptPtr<UIElement> parent, 
                                                         const Vector2 & pos, const Window & window, NullOptPtr<UISoundPrototypeEffects> sfx) :
  m_Window(window),
  m_Sfx(sfx),
  m_Alpha(1.0f)
{
  UIElementFullTextureInitData enabled_data;
  enabled_data.m_TextureFile = "./Images/UI/FullScreen.png";

  m_ImgEnabled = manager.AllocateFullTexture(name, parent, enabled_data, {});

  auto img_enabled = m_ImgEnabled.Get();
  img_enabled->SetOnClickHandler([this](NotNullPtr<UIElement>) { HandleClick(); });
  img_enabled->SetOnUpdateHandler([this](NotNullPtr<UIElement>) { Update(); });
  img_enabled->SetOnStateChangeHandler([this](UIElementState prev_state, UIElementState new_state) { HandleStateChange(prev_state, new_state); });
  auto & img_enabled_data = img_enabled->GetData();
  img_enabled_data.m_Active = true;
  img_enabled_data.m_PositionX = (float)pos.x;
  img_enabled_data.m_PositionY = (float)pos.y;
  img_enabled->SetActive();
}

void UIPrototypeFullscreenButton::Update()
{
  auto color = Color(1.0f, 1.0f, 1.0f, m_Alpha);
  m_ImgEnabled->GetData().SetColor(color);
}

void UIPrototypeFullscreenButton::HandleStateChange(UIElementState prev_state, UIElementState new_state)
{

}

void UIPrototypeFullscreenButton::HandleClick()
{
  printf("Toggle full screen\n");
  m_Window.SetFullscreen(!m_Window.IsFullScreen());
}

void UIPrototypeFullscreenButton::SetAlpha(float alpha)
{
  m_Alpha = alpha;
}
