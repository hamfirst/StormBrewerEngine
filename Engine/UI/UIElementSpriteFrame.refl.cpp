
#include "Engine/EngineCommon.h"
#include "Engine/UI/UIElementSpriteFrame.refl.h"

#include "Engine/Sprite/SpriteEngineData.h"
#include "Engine/Shader/ShaderManager.h"

int UIElementSpriteFrame::Type = 4;

UIElementSpriteFrame::UIElementSpriteFrame(const UIElementSpriteFrameInitData & init_data, const UIElementSpriteFrameData & data) :
  m_InitData(init_data),
  m_Data(data),
  m_Sprite(SpriteResource::Load(m_InitData.m_SpriteFile.data()))
{

}

void UIElementSpriteFrame::Update()
{
  auto anim_hash = crc32(m_Data.m_Animation);
  m_Sprite.GetResource()->FrameAdvance(anim_hash, m_State, true, (int)m_Data.m_FrameAdvance);

  UIElement::Update();
}

void UIElementSpriteFrame::Render(RenderState & render_state, RenderUtil & render_util)
{
  if (m_RenderDelegate)
  {
    m_RenderDelegate(*this, render_state);
  }
  else
  {
    RenderDefault(render_state, render_util);
  }
}

void UIElementSpriteFrame::RenderDefault(RenderState & render_state, RenderUtil & render_util)
{
  if (m_Sprite.GetResource() == nullptr)
  {
    return;
  }

  m_State.m_Color.r = m_Data.m_ColorR;
  m_State.m_Color.g = m_Data.m_ColorG;
  m_State.m_Color.b = m_Data.m_ColorB;
  m_State.m_Color.a = m_Data.m_ColorA;
  m_State.m_Draw = m_Data.m_Enabled != 0.0f;

  auto sc = SinCosf(m_Data.m_Angle);

  m_State.m_Matrix.x = sc.y * m_Data.m_WidthScale;
  m_State.m_Matrix.y = sc.x * m_Data.m_WidthScale;
  m_State.m_Matrix.z = -sc.x * m_Data.m_HeightScale;
  m_State.m_Matrix.w = sc.y * m_Data.m_HeightScale;

  m_Sprite.GetResource()->Render(m_State, Vector2((int)m_Data.m_CenterX, (int)m_Data.m_CenterY));
}

const UIElementSpriteFrameInitData & UIElementSpriteFrame::GetInitData()
{
  return m_InitData;
}

UIElementSpriteFrameData & UIElementSpriteFrame::GetData()
{
  return m_Data;
}

void UIElementSpriteFrame::SetCustomRenderCallback(Delegate<void, UIElementSpriteFrame &, RenderState &> && render_callback)
{
  m_RenderDelegate = std::move(render_callback);
}

SpritePtr & UIElementSpriteFrame::GetSprite()
{
  return m_Sprite;
}
