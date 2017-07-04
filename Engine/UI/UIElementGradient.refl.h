#pragma once

#include "Engine/EngineCommon.h"
#include "Engine/UI/UIElement.h"
#include "Engine/Rendering/VertexBuffer.h"

struct UIElementGradientInitData
{
  STORM_REFL;
};

struct UIElementGradientData
{
  STORM_REFL;

  float m_StartX = 0.0f;
  float m_StartY = 0.0f;
  float m_EndX = 0.0f;
  float m_EndY = 0.0f;
  float m_Angle = 0.0f;
  float m_Enabled = 1.0f;

  float m_BLColorR = 1.0f;
  float m_BLColorG = 1.0f;
  float m_BLColorB = 1.0f;
  float m_BLColorA = 1.0f;

  float m_BRColorR = 1.0f;
  float m_BRColorG = 1.0f;
  float m_BRColorB = 1.0f;
  float m_BRColorA = 1.0f;

  float m_TLColorR = 1.0f;
  float m_TLColorG = 1.0f;
  float m_TLColorB = 1.0f;
  float m_TLColorA = 1.0f;

  float m_TRColorR = 1.0f;
  float m_TRColorG = 1.0f;
  float m_TRColorB = 1.0f;
  float m_TRColorA = 1.0f;

  float m_Active = 0.0f;
};

class RenderState;
class RenderUtil;

class UIElementGradient : public UIElement
{
public:
  UIElementGradient(const UIElementGradientInitData & init_data, const UIElementGradientData & data = {});

  static int Type;

  void Update() override;
  void Render(RenderState & render_state, RenderUtil & render_util) override;
  void RenderDefault(RenderState & render_state, RenderUtil & render_util);

  const UIElementGradientInitData & GetInitData();
  UIElementGradientData & GetData();

  void SetCustomRenderCallback(Delegate<void, UIElementGradient &, RenderState &> && render_callback);

private:

  UIElementGradientInitData m_InitData;
  UIElementGradientData m_Data;

  Delegate<void, UIElementGradient &, RenderState &> m_RenderDelegate;

  VertexBuffer m_VertexBuffer;
};

