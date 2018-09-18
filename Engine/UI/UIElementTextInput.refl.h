#pragma once

#include "Engine/EngineCommon.h"
#include "Engine/UI/UIElement.h"
#include "Engine/UI/UICustomPropertyData.refl.h"
#include "Engine/Input/TextInputContext.h"

#include "Runtime/UI/UIDef.refl.h"

struct UIElementTextInputInitData : public UIElementInitDataBase
{
  STORM_DATA_DEFAULT_CONSTRUCTION(UIElementTextInputInitData);
};

struct UIElementTextInputData : public UIElementDataFrameCenter
{
  STORM_REFL;

  std::string m_Prompt;

  float m_TextMode = 0;
  float m_FontId = -1;
  float m_Justify = 0;
  float m_Scale = 1;

  float m_EnableTextBounds = 0.0f;
  float m_TextBoundsStartX = 0.0f;
  float m_TextBoundsStartY = 0.0f;
  float m_TextBoundsEndX = 0.0f;
  float m_TextBoundsEndY = 0.0f;

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
  ~UIElementTextInput();

  static UIElementType Type;

  void Update(float dt) override;
  void Render(RenderState & render_state, RenderUtil & render_util, const Vector2 & offset) override;
  void RenderDefault(RenderState & render_state, RenderUtil & render_util, const Vector2 & offset);

  const UIElementTextInputInitData & GetInitData();
  UIElementTextInputData & GetData();

  virtual NotNullPtr<UIElementDataBase> GetBaseData() override;
  virtual NullOptPtr<UIElementDataFrameCenter> GetFrameCenterData() override;
  virtual NullOptPtr<UIElementDataStartEnd> GetStartEndData() override;

  TextInputContext & GetInputContext();
  void SetCustomRenderCallback(Delegate<void, UIElementTextInput &, RenderState &, const Vector2 &> && render_callback);

protected:

  virtual StormExprValueInitBlock & GetLocalInitBlock() override;
  virtual StormExprValueInitBlock & GetAsParentInitBlock() override;
  virtual StormExprBindingList & GetBindingList() override;

private:

  UIElementTextInputInitData m_InitData;
  UIElementTextInputData m_Data;
  
  std::shared_ptr<TextInputContext> m_TextInput;

  Delegate<void, UIElementTextInput &, RenderState &, const Vector2 &> m_RenderDelegate;
};

