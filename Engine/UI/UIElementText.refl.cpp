
#include "Engine/EngineCommon.h"
#include "Engine/UI/UIElementText.refl.meta.h"
#include "Engine/UI/UIElementExprBlock.h"

#include "Engine/Rendering/RenderUtil.h"
#include "Engine/Text/TextManager.h"

#include "Runtime/UI/UIElementTypeRegister.h"

STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(UIElementTextInitData);
REGISTER_UIELEMENT_DATA(UIElementText, UIElementTextInitData, UIElementTextData);

UIElementType UIElementText::Type = UIElementType::kText;

UIElementText::UIElementText(const UIElementTextInitData & init_data, const UIElementTextData & data) :
  m_InitData(init_data),
  m_Data(data)
{

}

void UIElementText::Update()
{
  auto size = g_TextManager.GetTextSize(m_Data.m_Text.c_str(), (int)m_Data.m_FontId);
  auto pos = Vector2(m_Data.m_PositionX, m_Data.m_PositionY);

  if (m_Data.m_Centered)
  {
    SetActiveArea(Box::FromFrameCenterAndSize(Vector2(m_Data.m_PositionX, m_Data.m_PositionY), size.Size()));
  }
  else
  {
    size.m_Start += pos;
    size.m_End += pos;
    SetActiveArea(size);
  }

  SetOffset(Vector2(m_Data.m_PositionX, m_Data.m_PositionY));

  UIElement::Update();

  size = g_TextManager.GetTextSize(m_Data.m_Text.c_str(), (int)m_Data.m_FontId);
  pos = Vector2(m_Data.m_PositionX, m_Data.m_PositionY);

  if (m_Data.m_Centered)
  {
    SetActiveArea(Box::FromFrameCenterAndSize(Vector2(m_Data.m_PositionX, m_Data.m_PositionY), size.Size()));
  }
  else
  {
    size.m_Start += pos;
    size.m_End += pos;
    SetActiveArea(size);
  }

  SetOffset(Vector2(m_Data.m_PositionX, m_Data.m_PositionY));
}

void UIElementText::Render(RenderState & render_state, RenderUtil & render_util, const Vector2 & offset)
{
  if (m_RenderDelegate)
  {
    m_RenderDelegate(*this, render_state, offset);
  }
  else
  {
    RenderDefault(render_state, render_util, offset);
  }

  UIElement::Render(render_state, render_util, offset);
}

void UIElementText::RenderDefault(RenderState & render_state, RenderUtil & render_util, const Vector2 & offset)
{
  g_TextManager.SetTextMode((TextRenderMode)(int)m_Data.m_TextMode);
  g_TextManager.SetPrimaryColor(Color(m_Data.m_PrimaryColorR, m_Data.m_PrimaryColorG, m_Data.m_PrimaryColorB, m_Data.m_PrimaryColorA));
  g_TextManager.SetShadowColor(Color(m_Data.m_SecondaryColorR, m_Data.m_SecondaryColorG, m_Data.m_SecondaryColorB, m_Data.m_SecondaryColorA));

  if (m_Data.m_EnableTextBounds)
  {
    g_TextManager.SetTextBounds(Box::FromPoints(Vector2(m_Data.m_TextBoundsStartX, m_Data.m_TextBoundsStartY), Vector2(m_Data.m_TextBoundsEndX, m_Data.m_TextBoundsEndY)));
  }
  else
  {
    g_TextManager.ClearTextBounds();
  }

  auto real_offset = offset + render_state.GetRenderSize() / 2;

  if (m_Data.m_Centered)
  {
    auto size = g_TextManager.GetTextSize(m_Data.m_Text.c_str(), (int)m_Data.m_FontId);
    g_TextManager.SetTextPos(Vector2(m_Data.m_PositionX, m_Data.m_PositionY) - (size.Size() / 2) + real_offset - size.m_Start);
  }
  else
  {
    g_TextManager.SetTextPos(Vector2(m_Data.m_PositionX, m_Data.m_PositionY) + real_offset);
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

void UIElementText::SetCustomRenderCallback(Delegate<void, UIElementText &, RenderState &, const Vector2 &> && render_callback)
{
  m_RenderDelegate = std::move(render_callback);
}

StormExprValueInitBlock UIElementText::GetLocalBlock()
{
  return UICreateInitBlockForDataType(m_Data);
}

StormExprValueInitBlock UIElementText::GetAsParentBlock()
{
  return UICreateInitBlockForDataType(m_Data, "p.");
}

UIElementExprBindingList UIElementText::CreateBindingList()
{
  return UICreateBindingList(m_Data);
}





