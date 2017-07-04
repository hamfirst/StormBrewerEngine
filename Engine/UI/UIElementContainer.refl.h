#pragma once

#include "Engine/EngineCommon.h"
#include "Engine/UI/UIElement.h"

struct UIElementContainerInitData
{
  STORM_REFL;
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

  static int Type;

  void Update() override;
  void Render(RenderState & render_state, RenderUtil & render_util) override;
  void RenderDefault(RenderState & render_state, RenderUtil & render_util);

  const UIElementContainerInitData & GetInitData();
  UIElementContainerData & GetData();

  void SetCustomRenderCallback(Delegate<void, UIElementContainer &, RenderState &> && render_callback);

private:

  UIElementContainerInitData m_InitData;
  UIElementContainerData m_Data;

  Delegate<void, UIElementContainer &, RenderState &> m_RenderDelegate;
};

