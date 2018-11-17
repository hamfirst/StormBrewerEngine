
#include "Engine/EngineCommon.h"
#include "Engine/UI/UIManager.h"
#include "Engine/UI/Prototype/UIPrototypeMuteButton.h"
#include "Engine/Audio/AudioManager.h"

#include "Foundation/Lerp/LerpFuncs.h"

UIPrototypeMuteButton::UIPrototypeMuteButton(UIManager & manager, czstr name, NullOptPtr<UIElement> parent, const Vector2 & pos, bool music_only, NullOptPtr<UISoundPrototypeEffects> sfx) :
  m_Sfx(sfx),
  m_Alpha(1.0f),
  m_MusicOnly(music_only)
{
  UIElementFullTextureInitData enabled_data;
  enabled_data.m_TextureFile = music_only ? "./Images/UI/MusicOn.png" : "./Images/UI/MuteOff.png";

  UIElementFullTextureInitData disabled_data;
  disabled_data.m_TextureFile = music_only ? "./Images/UI/MusicOff.png" : "./Images/UI/Mute.png";

  m_ImgEnabled = manager.AllocateFullTexture(name, parent, enabled_data, {});
  m_ImgDisabled = manager.AllocateFullTexture(name, parent, disabled_data, {});

  auto img_enabled = m_ImgEnabled.Get();
  img_enabled->SetOnClickHandler([this](NotNullPtr<UIElement>) { if (m_Sfx) { g_AudioManager.PlayAudio(m_Sfx->m_ButtonPressedSfx); } HandleClick(); });
  img_enabled->SetOnUpdateHandler([this](NotNullPtr<UIElement>) { Update(); });
  img_enabled->SetOnStateChangeHandler([this](UIElementState prev_state, UIElementState new_state) { HandleStateChange(prev_state, new_state); });
  auto & img_enabled_data = img_enabled->GetData();
  img_enabled_data.m_Active = true;
  img_enabled_data.m_PositionX = (float)pos.x;
  img_enabled_data.m_PositionY = (float)pos.y;
  img_enabled->SetActive();

  auto img_disabled = m_ImgDisabled.Get();
  img_disabled->SetOnClickHandler([this](NotNullPtr<UIElement>) { if (m_Sfx) { g_AudioManager.PlayAudio(m_Sfx->m_ButtonPressedSfx); } HandleClick(); });
  img_disabled->SetOnStateChangeHandler([this](UIElementState prev_state, UIElementState new_state) { HandleStateChange(prev_state, new_state); });
  auto & img_disabled_data = img_disabled->GetData();
  img_disabled_data.m_Active = true;
  img_disabled_data.m_PositionX = (float)pos.x;
  img_disabled_data.m_PositionY = (float)pos.y;
  img_disabled->SetActive();
  img_disabled->SetDisabled();
}

void UIPrototypeMuteButton::Update()
{
  auto color = Color(1.0f, 1.0f, 1.0f, m_Alpha);
  m_ImgEnabled->GetData().SetColor(color);
  m_ImgDisabled->GetData().SetColor(color);

  if (m_MusicOnly)
  {
    if (g_AudioManager.GetVolumeForCategory(VolumeCategory::kMusic) != 0.0f)
    {
      m_ImgEnabled->SetEnabled();
      m_ImgDisabled->SetDisabled();
    }
    else
    {
      m_ImgEnabled->SetDisabled();
      m_ImgDisabled->SetEnabled();
    }
  }
  else
  {
    if (g_AudioManager.GetGlobalVolume() == 1.0f)
    {
      m_ImgEnabled->SetEnabled();
      m_ImgDisabled->SetDisabled();
    }
    else
    {
      m_ImgEnabled->SetDisabled();
      m_ImgDisabled->SetEnabled();
    }
  }
}

void UIPrototypeMuteButton::HandleStateChange(UIElementState prev_state, UIElementState new_state)
{

}

void UIPrototypeMuteButton::HandleClick()
{
  if (m_MusicOnly)
  {
    if (g_AudioManager.GetVolumeForCategory(VolumeCategory::kMusic) != 0.0f)
    {
      g_AudioManager.SetVolumeCategory(VolumeCategory::kMusic, 0.0f);
    }
    else
    {
      g_AudioManager.SetVolumeCategory(VolumeCategory::kMusic, 0.5f);
    }
  }
  else
  {
    if (g_AudioManager.GetGlobalVolume() == 1.0f)
    {
      g_AudioManager.SetGlobalVolume(0.0f);
    }
    else
    {
      g_AudioManager.SetGlobalVolume(1.0f);
    }
  }
}

void UIPrototypeMuteButton::SetAlpha(float alpha)
{
  m_Alpha = alpha;
}
