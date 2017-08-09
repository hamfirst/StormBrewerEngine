#pragma once

#include "Engine/EngineCommon.h"
#include "Engine/UI/UIElement.h"
#include "Engine/Rendering/VertexBuffer.h"

#include "Runtime/UI/UIDef.refl.h"

struct UIElementShapeInitData : public UIElementDataBase
{
  STORM_DATA_DEFAULT_CONSTRUCTION(UIElementShapeInitData);
};

static const float kUIElementShapeFilledRectangle = 0;
static const float kUIElementShapeFilledCircle = 1;
static const float kUIElementShapeRectangle = 2;
static const float kUIElementShapeCircle = 3;

struct UIElementShapeData
{
  STORM_REFL;

  float m_StartX = 0.0f;
  float m_StartY = 0.0f;
  float m_EndX = 0.0f;
  float m_EndY = 0.0f;
  float m_Enabled = 1.0f;
  float m_Shape = 0.0f;
  float m_EdgeWidth = 1.0f;

  float m_ColorR = 1.0f;
  float m_ColorG = 1.0f;
  float m_ColorB = 1.0f;
  float m_ColorA = 1.0f;

  float m_Active = 0.0f;

  void SetBounds(const Box & b)
  {
    m_StartX = (float)b.m_Start.x;
    m_StartY = (float)b.m_Start.y;
    m_EndX = (float)b.m_End.x;
    m_EndY = (float)b.m_End.y;
  }

  void SetColor(const Color & c)
  {
    m_ColorR = c.r;
    m_ColorG = c.g;
    m_ColorB = c.b;
    m_ColorA = c.a;
  }
};

class RenderState;
class RenderUtil;

class UIElementShape : public UIElement
{
public:
  UIElementShape(const UIElementShapeInitData & init_data, const UIElementShapeData & data = {});

  static UIElementType Type;

  void Update() override;
  void Render(RenderState & render_state, RenderUtil & render_util, const Vector2 & offset) override;
  void RenderDefault(RenderState & render_state, RenderUtil & render_util, const Vector2 & offset);

  const UIElementShapeInitData & GetInitData();
  UIElementShapeData & GetData();

  void SetCustomRenderCallback(Delegate<void, UIElementShape &, RenderState &, const Vector2 &> && render_callback);

protected:

  virtual StormExprValueInitBlock GetLocalBlock() override;
  virtual StormExprValueInitBlock GetAsParentBlock() override;
  virtual UIElementExprBindingList CreateBindingList() override;

private:

  UIElementShapeInitData m_InitData;
  UIElementShapeData m_Data;

  Delegate<void, UIElementShape &, RenderState &, const Vector2 &> m_RenderDelegate;
};

