#pragma once

#include "Engine/EngineCommon.h"
#include "Engine/UI/UIElement.h"
#include "Engine/UI/UICustomPropertyData.refl.h"

#include "Runtime/UI/UIDef.refl.h"

struct UIElementTextInitData : public UIElementInitDataBase
{
  STORM_DATA_DEFAULT_CONSTRUCTION(UIElementTextInitData);
};

struct UIElementTextData : public UIElementDataFrameCenter
{
  STORM_REFL;

  std::string m_Text;

  float m_TextMode = 0;
  float m_FontId = -1.0f;
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

  void SetSecondaryColor(const Color & c)
  {
    m_SecondaryColorR = c.r;
    m_SecondaryColorG = c.g;
    m_SecondaryColorB = c.b;
    m_SecondaryColorA = c.a;
  }
};

class UIElementText : public UIElement
{
public:
  UIElementText(const UIElementTextInitData & init_data, const UIElementTextData & data = {});

  static UIElementType Type;

  void Update(float dt) override;
  void Render(RenderState & render_state, RenderUtil & render_util, const Vector2 & offset) override;
  void RenderDefault(RenderState & render_state, RenderUtil & render_util, const Vector2 & offset);

  const UIElementTextInitData & GetInitData();
  UIElementTextData & GetData();

  virtual NotNullPtr<UIElementDataBase> GetBaseData() override;
  virtual NullOptPtr<UIElementDataFrameCenter> GetFrameCenterData() override;
  virtual NullOptPtr<UIElementDataStartEnd> GetStartEndData() override;

  void SetCustomRenderCallback(Delegate<void, UIElementText &, RenderState &, const Vector2 &> && render_callback);

protected:

  virtual StormExprValueInitBlock & GetLocalInitBlock() override;
  virtual StormExprValueInitBlock & GetAsParentInitBlock() override;
  virtual StormExprBindingList & GetBindingList() override;

private:

  UIElementTextInitData m_InitData;
  UIElementTextData m_Data;

  Delegate<void, UIElementText &, RenderState &, const Vector2 &> m_RenderDelegate;
};

