#pragma once

#include "Engine/EngineCommon.h"
#include "Engine/UI/UIElement.h"
#include "Engine/UI/UICustomPropertyData.refl.h"

#include "Runtime/UI/UIDef.refl.h"

struct UIElementContainerInitData : public UIElementInitDataBase
{
  STORM_DATA_DEFAULT_CONSTRUCTION(UIElementContainerInitData);
};

struct UIElementContainerData : public UIElementDataStartEnd
{
  STORM_REFL;
};

class UIElementContainer : public UIElement
{
public:
  UIElementContainer(const UIElementContainerInitData & init_data, const UIElementContainerData & data = {});

  static UIElementType Type;

  void Update(float dt) override;
  void Render(RenderState & render_state, RenderUtil & render_util, const Vector2 & offset) override;
  void RenderDefault(RenderState & render_state, RenderUtil & render_util, const Vector2 & offset);

  const UIElementContainerInitData & GetInitData();
  UIElementContainerData & GetData();

  virtual NotNullPtr<UIElementDataBase> GetBaseData() override;
  virtual NullOptPtr<UIElementDataFrameCenter> GetFrameCenterData() override;
  virtual NullOptPtr<UIElementDataStartEnd> GetStartEndData() override;

  void SetCustomRenderCallback(Delegate<void, UIElementContainer &, RenderState &, const Vector2 &> && render_callback);

protected:

  virtual StormExprValueInitBlock & GetLocalInitBlock() override;
  virtual StormExprValueInitBlock & GetAsParentInitBlock() override;
  virtual StormExprBindingList & GetBindingList() override;

private:

  UIElementContainerInitData m_InitData;
  UIElementContainerData m_Data;

  Delegate<void, UIElementContainer &, RenderState &, const Vector2 &> m_RenderDelegate;
};

