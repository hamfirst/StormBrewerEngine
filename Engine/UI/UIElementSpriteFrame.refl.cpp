
#include "Engine/EngineCommon.h"
#include "Engine/UI/UIElementSpriteFrame.refl.meta.h"
#include "Engine/UI/UIElementExprBlock.h"

#include "Engine/Sprite/SpriteEngineData.h"
#include "Engine/Shader/ShaderManager.h"

#include "Runtime/UI/UIElementTypeRegister.h"

STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(UIElementSpriteFrameInitData);
REGISTER_UIELEMENT_DATA(UIElementSpriteFrame, UIElementSpriteFrameInitData, UIElementSpriteFrameData);

UIElementType UIElementSpriteFrame::Type = UIElementType::kSpriteFrame;

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

  SetActiveArea(Box::FromFrameCenterAndSize(Vector2(m_Data.m_CenterX, m_Data.m_CenterY), Vector2(m_State.m_FrameWidth, m_State.m_FrameHeight)));
  SetOffset(Vector2(m_Data.m_CenterX, m_Data.m_CenterY) - Vector2(m_State.m_FrameWidth, m_State.m_FrameHeight));

  UIElement::Update();
  SetActiveArea(Box::FromFrameCenterAndSize(Vector2(m_Data.m_CenterX, m_Data.m_CenterY), Vector2(m_State.m_FrameWidth, m_State.m_FrameHeight)));
  SetOffset(Vector2(m_Data.m_CenterX, m_Data.m_CenterY) - Vector2(m_State.m_FrameWidth, m_State.m_FrameHeight));
}

void UIElementSpriteFrame::Render(RenderState & render_state, RenderUtil & render_util, const Vector2 & offset)
{
  if (m_RenderDelegate)
  {
    m_RenderDelegate(*this, render_state, offset);
  }
  else
  {
    RenderDefault(render_state, render_util, offset);
  }

  UIElement::Render(render_state, render_util, offset);
}

void UIElementSpriteFrame::RenderDefault(RenderState & render_state, RenderUtil & render_util, const Vector2 & offset)
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

  m_Sprite.GetResource()->Render(m_State, Vector2((int)m_Data.m_CenterX, (int)m_Data.m_CenterY) + offset);
}

const UIElementSpriteFrameInitData & UIElementSpriteFrame::GetInitData()
{
  return m_InitData;
}

UIElementSpriteFrameData & UIElementSpriteFrame::GetData()
{
  return m_Data;
}

void UIElementSpriteFrame::SetCustomRenderCallback(Delegate<void, UIElementSpriteFrame &, RenderState &, const Vector2 &> && render_callback)
{
  m_RenderDelegate = std::move(render_callback);
}

SpritePtr & UIElementSpriteFrame::GetSprite()
{
  return m_Sprite;
}

StormExprValueInitBlock UIElementSpriteFrame::GetLocalBlock()
{
  return UICreateInitBlockForDataType(m_Data);
}

StormExprValueInitBlock UIElementSpriteFrame::GetAsParentBlock()
{
  return UICreateInitBlockForDataType(m_Data, "p.");
}

UIElementExprBindingList UIElementSpriteFrame::CreateBindingList()
{
  return UICreateBindingList(m_Data);
}



