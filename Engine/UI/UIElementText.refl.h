#pragma once

#include "Engine/EngineCommon.h"
#include "Engine/UI/UIElement.h"

struct UIElementTextInitData
{
  STORM_REFL;
};

struct UIElementTextData
{
  STORM_REFL;

  std::string m_Text;

  float m_PositionX = 0.0f;
  float m_PositionY = 0.0f;

  float m_TextMode = 0;
  float m_FontId = 0;

  float m_EnableTextBounds = 0.0f;
  float m_TextBoundsStartX = 0.0f;
  float m_TextBoundsStartY = 0.0f;
  float m_TextBoundsEndX = 0.0f;
  float m_TextBoundsEndY = 0.0f;

  float m_PrimaryColorR = 1.0f;
  float m_PrimaryColorG = 1.0f;
  float m_PrimaryColorB = 1.0f;
  float m_PrimaryColorA = 1.0f;

  float m_SecondaryColorR = 1.0f;
  float m_SecondaryColorG = 1.0f;
  float m_SecondaryColorB = 1.0f;
  float m_SecondaryColorA = 1.0f;

  float m_Active = 0.0f;
};

class UIElementText : public UIElement
{
public:
  UIElementText(const UIElementTextInitData & init_data, const UIElementTextData & data = {});

  static int Type;

  void Update() override;
  void Render(RenderState & render_state, RenderUtil & render_util) override;
  void RenderDefault(RenderState & render_state, RenderUtil & render_util);

  const UIElementTextInitData & GetInitData();
  UIElementTextData & GetData();

  void SetCustomRenderCallback(Delegate<void, UIElementText &, RenderState &> && render_callback);

private:

  UIElementTextInitData m_InitData;
  UIElementTextData m_Data;

  Delegate<void, UIElementText &, RenderState &> m_RenderDelegate;
};

