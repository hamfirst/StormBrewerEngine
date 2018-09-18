#pragma once

#include "Engine/EngineCommon.h"
#include "Engine/UI/UIElement.h"
#include "Engine/Rendering/VertexBuffer.h"
#include "Engine/UI/UICustomPropertyData.refl.h"

#include "Runtime/UI/UIDef.refl.h"

struct UIElementGradientInitData : public UIElementInitDataBase
{
  STORM_DATA_DEFAULT_CONSTRUCTION(UIElementGradientInitData);
};

struct UIElementGradientData : public UIElementDataStartEnd
{
  STORM_REFL;

  float m_Angle = 0.0f;

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
};

class RenderState;
class RenderUtil;

class UIElementGradient : public UIElement
{
public:
  UIElementGradient(const UIElementGradientInitData & init_data, const UIElementGradientData & data = {});

  static UIElementType Type;

  void Update(float dt) override;
  void Render(RenderState & render_state, RenderUtil & render_util, const Vector2 & offset) override;
  void RenderDefault(RenderState & render_state, RenderUtil & render_util, const Vector2 & offset);

  const UIElementGradientInitData & GetInitData();
  UIElementGradientData & GetData();

  virtual NotNullPtr<UIElementDataBase> GetBaseData() override;
  virtual NullOptPtr<UIElementDataFrameCenter> GetFrameCenterData() override;
  virtual NullOptPtr<UIElementDataStartEnd> GetStartEndData() override;

  void SetCustomRenderCallback(Delegate<void, UIElementGradient &, RenderState &, const Vector2 &> && render_callback);

protected:

  virtual StormExprValueInitBlock & GetLocalInitBlock() override;
  virtual StormExprValueInitBlock & GetAsParentInitBlock() override;
  virtual StormExprBindingList & GetBindingList() override;

private:

  UIElementGradientInitData m_InitData;
  UIElementGradientData m_Data;

  Delegate<void, UIElementGradient &, RenderState &, const Vector2 &> m_RenderDelegate;

  VertexBuffer m_VertexBuffer;
};

