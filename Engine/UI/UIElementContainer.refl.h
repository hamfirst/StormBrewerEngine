#pragma once

#include "Engine/EngineCommon.h"
#include "Engine/UI/UIElement.h"

#include "Runtime/UI/UIDef.refl.h"

struct UIElementContainerInitData : public UIElementDataBase
{
  STORM_DATA_DEFAULT_CONSTRUCTION(UIElementContainerInitData);
};

struct UIElementContainerData
{
  STORM_REFL;

  float m_StartX = 0.0f;
  float m_StartY = 0.0f;
  float m_EndX = 0.0f;
  float m_EndY = 0.0f;

  float m_Active = 0.0f;
};

class UIElementContainer : public UIElement
{
public:
  UIElementContainer(const UIElementContainerInitData & init_data, const UIElementContainerData & data = {});

  static UIElementType Type;

  void Update() override;
  void Render(RenderState & render_state, RenderUtil & render_util, const Vector2 & offset) override;
  void RenderDefault(RenderState & render_state, RenderUtil & render_util, const Vector2 & offset);

  const UIElementContainerInitData & GetInitData();
  UIElementContainerData & GetData();

  void SetCustomRenderCallback(Delegate<void, UIElementContainer &, RenderState &, const Vector2 &> && render_callback);

protected:

  virtual StormExprValueInitBlock GetLocalBlock() override;
  virtual StormExprValueInitBlock GetAsParentBlock() override;
  virtual UIElementExprBindingList CreateBindingList() override;

private:

  UIElementContainerInitData m_InitData;
  UIElementContainerData m_Data;

  Delegate<void, UIElementContainer &, RenderState &, const Vector2 &> m_RenderDelegate;
};

