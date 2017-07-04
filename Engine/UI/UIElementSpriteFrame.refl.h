#pragma once

#include "Engine/EngineCommon.h"
#include "Engine/UI/UIElement.h"

#include "Runtime/Sprite/SpriteResource.h"
#include "Runtime/Animation/AnimationState.h"


struct UIElementSpriteFrameInitData
{
  STORM_REFL;

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

  static int Type;

  void Update() override;
  void Render(RenderState & render_state, RenderUtil & render_util) override;
  void RenderDefault(RenderState & render_state, RenderUtil & render_util);

  const UIElementSpriteFrameInitData & GetInitData();
  UIElementSpriteFrameData & GetData();

  void SetCustomRenderCallback(Delegate<void, UIElementSpriteFrame &, RenderState &> && render_callback);
  
  SpritePtr & GetSprite();

private:

  EntityRenderState m_State;

  UIElementSpriteFrameInitData m_InitData;
  UIElementSpriteFrameData m_Data;

  Delegate<void, UIElementSpriteFrame &, RenderState &> m_RenderDelegate;
  SpritePtr m_Sprite;
};

