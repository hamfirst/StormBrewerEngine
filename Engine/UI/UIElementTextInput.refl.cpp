
#include "Engine/EngineCommon.h"
#include "Engine/UI/UIElementTextInput.refl.h"

#include "Engine/Rendering/RenderUtil.h"
#include "Engine/Text/TextManager.h"

int UIElementTextInput::Type = 8;

UIElementTextInput::UIElementTextInput(const UIElementTextInputInitData & init_data, const UIElementTextInputData & data, std::shared_ptr<TextInputContext> && input_context) :
  m_InitData(init_data),
  m_Data(data),
  m_TextInput(std::move(input_context))
{

}

void UIElementTextInput::Update()
{
  UIElement::Update();
  auto size = g_TextManager.GetTextSize(m_TextInput, (int)m_Data.m_FontId, m_Data.m_Prompt.data());
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
}

void UIElementTextInput::Render(RenderState & render_state, RenderUtil & render_util, const Vector2 & offset)
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

void UIElementTextInput::RenderDefault(RenderState & render_state, RenderUtil & render_util, const Vector2 & offset)
{
  g_TextManager.SetTextMode((TextRenderMode)(int)m_Data.m_TextMode);
  g_TextManager.SetPrimaryColor(Color(m_Data.m_PrimaryColorR, m_Data.m_PrimaryColorB, m_Data.m_PrimaryColorG, m_Data.m_PrimaryColorA));
  g_TextManager.SetShadowColor(Color(m_Data.m_SecondaryColorR, m_Data.m_SecondaryColorB, m_Data.m_SecondaryColorG, m_Data.m_SecondaryColorA));
  g_TextManager.SetSelectionColor(Color(m_Data.m_SelectionColorR, m_Data.m_SelectionColorB, m_Data.m_SelectionColorG, m_Data.m_SelectionColorA));
  g_TextManager.SetSelectionBkgColor(Color(m_Data.m_SelectionBkgColorR, m_Data.m_SelectionBkgColorG, m_Data.m_SelectionBkgColorB, m_Data.m_SelectionBkgColorA));

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
    auto size = g_TextManager.GetTextSize(m_TextInput, (int)m_Data.m_FontId, m_Data.m_Prompt.data());
    g_TextManager.SetTextPos(Vector2(m_Data.m_PositionX, m_Data.m_PositionY) - (size.Size() / 2) + real_offset - size.m_Start);
  }
  else
  {
    g_TextManager.SetTextPos(Vector2(m_Data.m_PositionX, m_Data.m_PositionY) + real_offset);
  }

  g_TextManager.RenderInputText(m_TextInput, (int)m_Data.m_FontId, render_state, m_Data.m_Prompt.data());
}

const UIElementTextInputInitData & UIElementTextInput::GetInitData()
{
  return m_InitData;
}

UIElementTextInputData & UIElementTextInput::GetData()
{
  return m_Data;
}

TextInputContext & UIElementTextInput::GetInputContext()
{
  return *m_TextInput.get();
}

void UIElementTextInput::SetCustomRenderCallback(Delegate<void, UIElementTextInput &, RenderState &, const Vector2 &> && render_callback)
{
  m_RenderDelegate = std::move(render_callback);
}

