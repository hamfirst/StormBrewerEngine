#pragma once

#include "Engine/EngineCommon.h"
#include "Engine/UI/UIElement.h"
#include "Engine/Input/TextInputContext.h"

struct UIElementTextInputInitData
{
  STORM_REFL;
};

struct UIElementTextInputData
{
  STORM_REFL;

  float m_PositionX = 0.0f;
  float m_PositionY = 0.0f;

  std::string m_Prompt;

  float m_TextMode = 0;
  float m_FontId = 0;
  float m_Centered = 0;

  float m_EnableTextBounds = 0.0f;
  float m_TextBoundsStartX = 0.0f;
  float m_TextBoundsStartY = 0.0f;
  float m_TextBoundsEndX = 0.0f;
  float m_TextBoundsEndY = 0.0f;

  float m_PrimaryColorR = 1.0f;
  float m_PrimaryColorG = 1.0f;
  float m_PrimaryColorB = 1.0f;
  float m_PrimaryColorA = 1.0f;

  float m_SecondaryColorR = 0.0f;
  float m_SecondaryColorG = 0.0f;
  float m_SecondaryColorB = 0.0f;
  float m_SecondaryColorA = 1.0f;

  float m_SelectionColorR = 0.3f;
  float m_SelectionColorG = 0.3f;
  float m_SelectionColorB = 0.3f;
  float m_SelectionColorA = 1.0f;

  float m_SelectionBkgColorR = 0.9f;
  float m_SelectionBkgColorG = 0.9f;
  float m_SelectionBkgColorB = 0.9f;
  float m_SelectionBkgColorA = 1.0f;

  float m_Active = 0.0f;

  void SetColor(const Color & c)
  {
    m_PrimaryColorR = c.r;
    m_PrimaryColorG = c.g;
    m_PrimaryColorB = c.b;
    m_PrimaryColorA = c.a;
  }

  void SetSecondaryColor(const Color & c)
  {
    m_SecondaryColorR = c.r;
    m_SecondaryColorG = c.g;
    m_SecondaryColorB = c.b;
    m_SecondaryColorA = c.a;
  }

  void SetSelectionColor(const Color & c)
  {
    m_SelectionColorR = c.r;
    m_SelectionColorG = c.g;
    m_SelectionColorB = c.b;
    m_SelectionColorA = c.a;
  }

  void SetSelectionBkgColor(const Color & c)
  {
    m_SelectionBkgColorR = c.r;
    m_SelectionBkgColorG = c.g;
    m_SelectionBkgColorB = c.b;
    m_SelectionBkgColorA = c.a;
  }
};

class UIElementTextInput : public UIElement
{
public:
  UIElementTextInput(const UIElementTextInputInitData & init_data, const UIElementTextInputData & data, std::shared_ptr<TextInputContext> && input_context);

  static int Type;

  void Update() override;
  void Render(RenderState & render_state, RenderUtil & render_util, const Vector2 & offset) override;
  void RenderDefault(RenderState & render_state, RenderUtil & render_util, const Vector2 & offset);

  const UIElementTextInputInitData & GetInitData();
  UIElementTextInputData & GetData();
  TextInputContext & GetInputContext();

  void SetCustomRenderCallback(Delegate<void, UIElementTextInput &, RenderState &, const Vector2 &> && render_callback);

private:

  UIElementTextInputInitData m_InitData;
  UIElementTextInputData m_Data;
  
  std::shared_ptr<TextInputContext> m_TextInput;

  Delegate<void, UIElementTextInput &, RenderState &, const Vector2 &> m_RenderDelegate;
};

