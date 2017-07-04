
#include "Engine/EngineCommon.h"
#include "Engine/UI/UIElementText.refl.h"

#include "Engine/Rendering/RenderUtil.h"
#include "Engine/Text/TextManager.h"

int UIElementText::Type = 5;

UIElementText::UIElementText(const UIElementTextInitData & init_data, const UIElementTextData & data) :
  m_InitData(init_data),
  m_Data(data)
{

}

void UIElementText::Update()
{
  UIElement::Update();
}

void UIElementText::Render(RenderState & render_state, RenderUtil & render_util)
{
  if (m_RenderDelegate)
  {
    m_RenderDelegate(*this, render_state);
  }
  else
  {
    RenderDefault(render_state, render_util);
  }
}

void UIElementText::RenderDefault(RenderState & render_state, RenderUtil & render_util)
{
  g_TextManager.SetTextMode((TextRenderMode)(int)m_Data.m_TextMode);
  g_TextManager.SetTextPos(Vector2(m_Data.m_PositionX, m_Data.m_PositionY));
  g_TextManager.SetPrimaryColor(Color(m_Data.m_PrimaryColorR, m_Data.m_PrimaryColorB, m_Data.m_PrimaryColorG, m_Data.m_PrimaryColorA));
  g_TextManager.SetShadowColor(Color(m_Data.m_SecondaryColorR, m_Data.m_SecondaryColorB, m_Data.m_SecondaryColorG, m_Data.m_SecondaryColorA));

  if (m_Data.m_EnableTextBounds)
  {
    g_TextManager.SetTextBounds(Box::FromPoints(Vector2(m_Data.m_TextBoundsStartX, m_Data.m_TextBoundsStartY), Vector2(m_Data.m_TextBoundsEndX, m_Data.m_TextBoundsEndY)));
  }
  else
  {
    g_TextManager.ClearTextBounds();
  }

  g_TextManager.RenderText(m_Data.m_Text.c_str(), (int)m_Data.m_FontId, render_state);
}

const UIElementTextInitData & UIElementText::GetInitData()
{
  return m_InitData;
}

UIElementTextData & UIElementText::GetData()
{
  return m_Data;
}

void UIElementText::SetCustomRenderCallback(Delegate<void, UIElementText &, RenderState &> && render_callback)
{
  m_RenderDelegate = std::move(render_callback);
}

