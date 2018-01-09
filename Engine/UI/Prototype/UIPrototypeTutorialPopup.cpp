
#include "Engine/EngineCommon.h"
#include "Engine/UI/UIManager.h"
#include "Engine/UI/Prototype/UIPrototypeTutorialPopup.h"
#include "Engine/Audio/AudioManager.h"

UIPrototypeTutorialPopup::UIPrototypeTutorialPopup(UIManager & manager, czstr name, NullOptPtr<UIElement> parent, const Box & box, czstr prompt, NullOptPtr<UISoundPrototypeEffects> sfx) :
  m_Sfx(sfx),
  m_BkgColor(255, 255, 255, 255),
  m_TextColor(255, 255, 255, 255)
{
  auto size = box.Size();

  m_Fader = manager.AllocateShape(name, parent);
  m_Fader->SetOnUpdateHandler([this](NotNullPtr<UIElement>) { Update(); });
  m_Fader->SetActive();
  auto & fader_data = m_Fader->GetData();
  fader_data.SetColor(Color(0, 0, 0, 0));
  fader_data.m_StartX = -10000;
  fader_data.m_StartY = -10000;
  fader_data.m_EndX = 10000;
  fader_data.m_EndY = 10000;
  fader_data.m_Shape = kUIElementShapeFilledRectangle;

  UIElementTextureSliceInitData slice_data;
  slice_data.m_StartX = 0;
  slice_data.m_StartY = 0;
  slice_data.m_EndX = 64;
  slice_data.m_EndY = 64;
  slice_data.m_StartCutX = 29;
  slice_data.m_EndCutX = 32;
  slice_data.m_StartCutY = 36;
  slice_data.m_EndCutY = 25;
  slice_data.m_SpriteFile = "./Images/TutorialBubble.png";
  slice_data.m_SliceHorizontally = 1.0f;
  slice_data.m_SliceVertically = 1.0f;
  m_Bkg = manager.AllocateTextureSlice("bkg", m_Fader, slice_data, {});

  auto bkg = m_Bkg.Get();
  auto & bkg_data = bkg->GetData();
  bkg_data.SetBounds(box);

  m_Text = manager.AllocateText("caption", bkg, {}, {});
  auto text = m_Text.Get();
  auto & text_data = text->GetData();
  text_data.m_Text = prompt;
  text_data.m_Centered = 1.0f;
  text_data.m_TextMode = 2.0f;
  text_data.m_PositionX = (float)(size.x / 2);
  text_data.m_PositionY = (float)(size.y - 40);
  text_data.m_FontId = -1;
  text_data.SetColor(m_TextColor);

  Box okay_box;
  okay_box.m_Start = Vector2(size.x - 90, 30);
  okay_box.m_End = okay_box.m_Start + Vector2(70, 25);

  m_OkayButton.Emplace(manager, "okay", bkg, okay_box, "Okay", sfx);
  m_OkayButton->SetOnClickCallback([this]() { m_OnOkay(); });

  Show();
}

void UIPrototypeTutorialPopup::Show()
{
  m_FaderLerp.LerpTo(1.0f, 0.3f);
}

void UIPrototypeTutorialPopup::Hide()
{
  m_FaderLerp.LerpTo(0.0f, 0.3f);
}

void UIPrototypeTutorialPopup::Toggle()
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

void UIPrototypeTutorialPopup::Update()
{
  float fade_val = m_FaderLerp;

  if (fade_val == 0)
  {
    m_Fader->SetDisabled();
  }
  else
  {
    m_Fader->SetEnabled();
    m_Fader->GetData().m_ColorA = fade_val * 0.1f;

    auto bkg_color = m_BkgColor;
    bkg_color.a *= fade_val;
    m_Bkg->GetData().SetColor(bkg_color);

    auto text_color = m_TextColor;
    text_color.a *= powf(fade_val, 1.0f);
    m_Text->GetData().SetColor(text_color);
    m_Text->GetData().SetSecondaryColor(Color(0.0f, 0.0f, 0.0f, powf(fade_val, 5.0f)));

    m_OkayButton->SetAlpha(fade_val);
  }

  bool active = m_FaderLerp.GetTarget() != 0;
  m_OkayButton->SetActive(active);
}

void UIPrototypeTutorialPopup::SetOnOkayCallback(Delegate<void> && rhs)
{
  m_OnOkay = std::move(rhs);
}

void UIPrototypeTutorialPopup::SetBkgColor(const Color & color)
{
  m_BkgColor = color;
}

void UIPrototypeTutorialPopup::SetTextColor(const Color & color)
{
  m_TextColor = color;
}

void UIPrototypeTutorialPopup::AttachText(czstr name, const UIElementTextInitData & init_data, const UIElementTextData & data)
{
  auto manager = m_Bkg->GetManager();
  m_ExtraText.push_back(manager->AllocateText(name, m_Bkg, init_data, data));
}

void UIPrototypeTutorialPopup::AttachImage(czstr name, const UIElementFullTextureInitData & init_data, const UIElementFullTextureData & data)
{
  auto manager = m_Bkg->GetManager();
  m_ExtraImages.push_back(manager->AllocateFullTexture(name, m_Bkg, init_data, data));
}
