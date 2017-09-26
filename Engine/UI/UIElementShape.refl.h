#pragma once

#include "Engine/EngineCommon.h"
#include "Engine/UI/UIElement.h"
#include "Engine/UI/UICustomPropertyData.refl.h"
#include "Engine/Rendering/VertexBuffer.h"

#include "Runtime/UI/UIDef.refl.h"

struct UIElementShapeInitData : public UIElementInitDataBase
{
  STORM_DATA_DEFAULT_CONSTRUCTION(UIElementShapeInitData);
};

static const float kUIElementShapeFilledRectangle = 0;
static const float kUIElementShapeFilledCircle = 1;
static const float kUIElementShapeRectangle = 2;
static const float kUIElementShapeCircle = 3;

struct UIElementShapeData : public UIElementDataStartEnd
{
  STORM_REFL;

  float m_Shape = 0.0f;
  float m_EdgeWidth = 1.0f;
};

class RenderState;
class RenderUtil;

class UIElementShape : public UIElement
{
public:
  UIElementShape(const UIElementShapeInitData & init_data, const UIElementShapeData & data = {});

  static UIElementType Type;

  void Update(float dt) override;
  void Render(RenderState & render_state, RenderUtil & render_util, const Vector2 & offset) override;
  void RenderDefault(RenderState & render_state, RenderUtil & render_util, const Vector2 & offset);

  const UIElementShapeInitData & GetInitData();
  UIElementShapeData & GetData();

  virtual NotNullPtr<UIElementDataBase> GetBaseData() override;
  virtual NullOptPtr<UIElementDataFrameCenter> GetFrameCenterData() override;
  virtual NullOptPtr<UIElementDataStartEnd> GetStartEndData() override;

  void SetCustomRenderCallback(Delegate<void, UIElementShape &, RenderState &, const Vector2 &> && render_callback);

protected:

  virtual StormExprValueInitBlock & GetLocalInitBlock() override;
  virtual StormExprValueInitBlock & GetAsParentInitBlock() override;
  virtual StormExprBindingList & GetBindingList() override;

private:

  UIElementShapeInitData m_InitData;
  UIElementShapeData m_Data;

  Delegate<void, UIElementShape &, RenderState &, const Vector2 &> m_RenderDelegate;
};

