
#include "Engine/EngineCommon.h"
#include "Engine/UI/UIElementText.refl.meta.h"

#include "Engine/Rendering/RenderUtil.h"
#include "Engine/Text/TextManager.h"

#include "Runtime/UI/UIElementTypeRegister.h"

STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(UIElementTextInitData);
REGISTER_UIELEMENT_DATA(UIElementText, UIElementTextInitData, UIElementTextData);

UIElementType UIElementText::Type = UIElementType::kText;

static auto s_LocalInitBlock = StormExprCreateInitBlockForDataType<UIElementTextData>();
static auto s_AsParentInitBlock = StormExprCreateInitBlockForDataType<UIElementTextData>("p.");
static auto s_BindingList = StormExprGetBindingList<UIElementTextData>();

UIElementText::UIElementText(const UIElementTextInitData & init_data, const UIElementTextData & data) :
  m_InitData(init_data),
  m_Data(data)
{

}

void UIElementText::Update(float dt)
{
  auto size = g_TextManager.GetTextSize(m_Data.m_Text.c_str(), (int)m_Data.m_FontId, m_Data.m_Scale);
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

  UIElement::Update(dt);

  size = g_TextManager.GetTextSize(m_Data.m_Text.c_str(), (int)m_Data.m_FontId, m_Data.m_Scale);
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
  if (m_Data.m_Enabled == 0)
  {
    return;
  }

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
  g_TextManager.SetPrimaryColor(Color(m_Data.m_ColorR, m_Data.m_ColorG, m_Data.m_ColorB, m_Data.m_ColorA));
  g_TextManager.SetShadowColor(Color(m_Data.m_SecondaryColorR, m_Data.m_SecondaryColorG, m_Data.m_SecondaryColorB, m_Data.m_SecondaryColorA));

  if (m_Data.m_EnableTextBounds)
  {
    g_TextManager.SetTextBounds(Box::FromPoints(Vector2(m_Data.m_TextBoundsStartX, m_Data.m_TextBoundsStartY), Vector2(m_Data.m_TextBoundsEndX, m_Data.m_TextBoundsEndY)));
  }
  else
  {
    g_TextManager.ClearTextBounds();
  }

  if (m_Data.m_Centered)
  {
    auto size = g_TextManager.GetTextSize(m_Data.m_Text.c_str(), (int)m_Data.m_FontId, m_Data.m_Scale);
    g_TextManager.SetTextPos(Vector2(m_Data.m_PositionX, m_Data.m_PositionY) - (size.Size() / 2) + offset - size.m_Start);
  }
  else
  {
    g_TextManager.SetTextPos(Vector2(m_Data.m_PositionX, m_Data.m_PositionY) + offset);
  }

  g_TextManager.RenderText(m_Data.m_Text.c_str(), (int)m_Data.m_FontId, m_Data.m_Scale, render_state);
}

const UIElementTextInitData & UIElementText::GetInitData()
{
  return m_InitData;
}

UIElementTextData & UIElementText::GetData()
{
  return m_Data;
}

NotNullPtr<UIElementDataBase> UIElementText::GetBaseData()
{
  return &m_Data;
}

NullOptPtr<UIElementDataFrameCenter> UIElementText::GetFrameCenterData()
{
  return &m_Data;
}

NullOptPtr<UIElementDataStartEnd> UIElementText::GetStartEndData()
{
  return nullptr;
}

void UIElementText::SetCustomRenderCallback(Delegate<void, UIElementText &, RenderState &, const Vector2 &> && render_callback)
{
  m_RenderDelegate = std::move(render_callback);
}

StormExprValueInitBlock & UIElementText::GetLocalInitBlock()
{
  return s_LocalInitBlock;
}

StormExprValueInitBlock & UIElementText::GetAsParentInitBlock()
{
  return s_AsParentInitBlock;
}

StormExprBindingList & UIElementText::GetBindingList()
{
  return s_BindingList;
}





