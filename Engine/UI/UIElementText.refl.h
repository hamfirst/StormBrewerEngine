#pragma once

#include "Engine/EngineCommon.h"
#include "Engine/UI/UIElement.h"

#include "Runtime/UI/UIDef.refl.h"

struct UIElementTextInitData : public UIElementDataBase
{
  STORM_DATA_DEFAULT_CONSTRUCTION(UIElementTextInitData);
};

struct UIElementTextData
{
  STORM_REFL;

  std::string m_Text;

  float m_PositionX = 0.0f;
  float m_PositionY = 0.0f;

  float m_TextMode = 0;
  float m_FontId = -1.0f;
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
};

class UIElementText : public UIElement
{
public:
  UIElementText(const UIElementTextInitData & init_data, const UIElementTextData & data = {});

  static UIElementType Type;

  void Update() override;
  void Render(RenderState & render_state, RenderUtil & render_util, const Vector2 & offset) override;
  void RenderDefault(RenderState & render_state, RenderUtil & render_util, const Vector2 & offset);

  const UIElementTextInitData & GetInitData();
  UIElementTextData & GetData();

  void SetCustomRenderCallback(Delegate<void, UIElementText &, RenderState &, const Vector2 &> && render_callback);

protected:

  virtual StormExprValueInitBlock GetLocalBlock() override;
  virtual StormExprValueInitBlock GetAsParentBlock() override;
  virtual UIElementExprBindingList CreateBindingList() override;

private:

  UIElementTextInitData m_InitData;
  UIElementTextData m_Data;

  Delegate<void, UIElementText &, RenderState &, const Vector2 &> m_RenderDelegate;
};

