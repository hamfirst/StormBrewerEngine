#pragma once

#include "Engine/EngineCommon.h"
#include "Engine/UI/UIElement.h"

#include "Runtime/Sprite/SpriteResource.h"
#include "Runtime/Animation/AnimationState.h"

#include "Runtime/UI/UIDef.refl.h"

struct UIElementSpriteFrameInitData : public UIElementDataBase
{
  STORM_DATA_DEFAULT_CONSTRUCTION(UIElementSpriteFrameInitData);

  RString STORM_REFL_ATTR_VAL(file, tilesheet) m_SpriteFile;
  RString m_Animation;
  int m_AnimationFrame = 0;
};

struct UIElementSpriteFrameData
{
  STORM_REFL;

  float m_CenterX = 0.0f;
  float m_CenterY = 0.0f;
  float m_WidthScale = 1.0f;
  float m_HeightScale = 1.0f;
  float m_Angle = 0.0f;
  float m_Enabled = 1.0f;

  std::string m_Animation;
  float m_FrameAdvance = 1.0f;

  float m_ColorR = 1.0f;
  float m_ColorG = 1.0f;
  float m_ColorB = 1.0f;
  float m_ColorA = 1.0f;

  float m_Active = 0.0f;
};

class RenderState;

class UIElementSpriteFrame : public UIElement
{
public:
  UIElementSpriteFrame(const UIElementSpriteFrameInitData & init_data, const UIElementSpriteFrameData & data = {});

  static UIElementType Type;

  void Update() override;
  void Render(RenderState & render_state, RenderUtil & render_util, const Vector2 & offset) override;
  void RenderDefault(RenderState & render_state, RenderUtil & render_util, const Vector2 & offset);

  const UIElementSpriteFrameInitData & GetInitData();
  UIElementSpriteFrameData & GetData();

  void SetCustomRenderCallback(Delegate<void, UIElementSpriteFrame &, RenderState &, const Vector2 &> && render_callback);
  
  SpritePtr & GetSprite();

protected:

  virtual StormExprValueInitBlock GetLocalBlock() override;
  virtual StormExprValueInitBlock GetAsParentBlock() override;
  virtual UIElementExprBindingList CreateBindingList() override;

private:

  EntityRenderState m_State;

  UIElementSpriteFrameInitData m_InitData;
  UIElementSpriteFrameData m_Data;

  Delegate<void, UIElementSpriteFrame &, RenderState &, const Vector2 &> m_RenderDelegate;
  SpritePtr m_Sprite;
};

