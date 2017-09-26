#pragma once

#include "Engine/EngineCommon.h"
#include "Engine/UI/UIElement.h"
#include "Engine/UI/UICustomPropertyData.refl.h"

#include "Runtime/Sprite/SpriteResource.h"
#include "Runtime/Animation/AnimationState.h"

#include "Runtime/UI/UIDef.refl.h"

struct UIElementSpriteFrameInitData : public UIElementInitDataBase
{
  STORM_DATA_DEFAULT_CONSTRUCTION(UIElementSpriteFrameInitData);

  RString STORM_REFL_ATTR_VAL(file, sprite) m_SpriteFile;
  int m_AnimationFrame = 0;
};

struct UIElementSpriteFrameData : public UIElementDataFrameCenter
{
  STORM_REFL;

  float m_ScaleX = 1.0f;
  float m_ScaleY = 1.0f;
  float m_Angle = 0.0f;

  std::string m_Animation;
  float m_FrameAdvance = 1.0f;
};

class RenderState;

class UIElementSpriteFrame : public UIElement
{
public:
  UIElementSpriteFrame(const UIElementSpriteFrameInitData & init_data, const UIElementSpriteFrameData & data = {});

  static UIElementType Type;

  void Update(float dt) override;
  void Render(RenderState & render_state, RenderUtil & render_util, const Vector2 & offset) override;
  void RenderDefault(RenderState & render_state, RenderUtil & render_util, const Vector2 & offset);

  const UIElementSpriteFrameInitData & GetInitData();
  UIElementSpriteFrameData & GetData();

  virtual NotNullPtr<UIElementDataBase> GetBaseData() override;
  virtual NullOptPtr<UIElementDataFrameCenter> GetFrameCenterData() override;
  virtual NullOptPtr<UIElementDataStartEnd> GetStartEndData() override;

  void SetCustomRenderCallback(Delegate<void, UIElementSpriteFrame &, RenderState &, const Vector2 &> && render_callback);
  
  SpritePtr & GetSprite();

protected:

  virtual StormExprValueInitBlock & GetLocalInitBlock() override;
  virtual StormExprValueInitBlock & GetAsParentInitBlock() override;
  virtual StormExprBindingList & GetBindingList() override;

private:

  EntityRenderState m_State;

  UIElementSpriteFrameInitData m_InitData;
  UIElementSpriteFrameData m_Data;

  Delegate<void, UIElementSpriteFrame &, RenderState &, const Vector2 &> m_RenderDelegate;
  SpritePtr m_Sprite;

  double m_LastUpdate;
  double m_AccumulationTime;
};

