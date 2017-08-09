#pragma once

#include "Engine/EngineCommon.h"
#include "Engine/UI/UIElement.h"
#include "Engine/Rendering/VertexBuffer.h"

#include "Runtime/UI/UIDef.refl.h"

struct UIElementGradientInitData : public UIElementDataBase
{
  STORM_DATA_DEFAULT_CONSTRUCTION(UIElementGradientInitData);
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

  void SetBounds(const Box & b)
  {
    m_StartX = (float)b.m_Start.x;
    m_StartY = (float)b.m_Start.y;
    m_EndX = (float)b.m_End.x;
    m_EndY = (float)b.m_End.y;
  }

  void SetColor(const Color & c)
  {
    m_BLColorR = c.r;
    m_BLColorG = c.g;
    m_BLColorB = c.b;
    m_BLColorA = c.a;

    m_BRColorR = c.r;
    m_BRColorG = c.g;
    m_BRColorB = c.b;
    m_BRColorA = c.a;

    m_TLColorR = c.r;
    m_TLColorG = c.g;
    m_TLColorB = c.b;
    m_TLColorA = c.a;

    m_TRColorR = c.r;
    m_TRColorG = c.g;
    m_TRColorB = c.b;
    m_TRColorA = c.a;
  }

  float m_Active = 0.0f;
};

class RenderState;
class RenderUtil;

class UIElementGradient : public UIElement
{
public:
  UIElementGradient(const UIElementGradientInitData & init_data, const UIElementGradientData & data = {});

  static UIElementType Type;

  void Update() override;
  void Render(RenderState & render_state, RenderUtil & render_util, const Vector2 & offset) override;
  void RenderDefault(RenderState & render_state, RenderUtil & render_util, const Vector2 & offset);

  const UIElementGradientInitData & GetInitData();
  UIElementGradientData & GetData();

  void SetCustomRenderCallback(Delegate<void, UIElementGradient &, RenderState &, const Vector2 &> && render_callback);

protected:

  virtual StormExprValueInitBlock GetLocalBlock() override;
  virtual StormExprValueInitBlock GetAsParentBlock() override;
  virtual UIElementExprBindingList CreateBindingList() override;

private:

  UIElementGradientInitData m_InitData;
  UIElementGradientData m_Data;

  Delegate<void, UIElementGradient &, RenderState &, const Vector2 &> m_RenderDelegate;

  VertexBuffer m_VertexBuffer;
};

