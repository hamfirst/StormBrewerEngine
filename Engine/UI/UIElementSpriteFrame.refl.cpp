
#include "Engine/EngineCommon.h"
#include "Engine/UI/UIElementSpriteFrame.refl.meta.h"

#include "Engine/Sprite/SpriteEngineData.h"
#include "Engine/Shader/ShaderManager.h"

#include "Runtime/UI/UIElementTypeRegister.h"

STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(UIElementSpriteFrameInitData);
REGISTER_UIELEMENT_DATA(UIElementSpriteFrame, UIElementSpriteFrameInitData, UIElementSpriteFrameData);

UIElementType UIElementSpriteFrame::Type = UIElementType::kSpriteFrame;

static auto s_LocalInitBlock = StormExprCreateInitBlockForDataType<UIElementSpriteFrameData>();
static auto s_AsParentInitBlock = StormExprCreateInitBlockForDataType<UIElementSpriteFrameData>("p.");
static auto s_BindingList = StormExprGetBindingList<UIElementSpriteFrameData>();

UIElementSpriteFrame::UIElementSpriteFrame(const UIElementSpriteFrameInitData & init_data, const UIElementSpriteFrameData & data) :
  m_InitData(init_data),
  m_Data(data),
  m_Sprite(SpriteResource::Load(m_InitData.m_SpriteFile.data())),
  m_LastUpdate(GetTimeSeconds()),
  m_AccumulationTime(0)
{
  m_State.m_AnimIndex = 0;
}

void UIElementSpriteFrame::Update(float dt)
{
  auto cur_time = GetTimeSeconds();
  auto frame_interval = 1.0 / 60.0;

  auto anim_hash = crc32(m_Data.m_Animation);
  if (anim_hash && m_Data.m_FrameAdvance != 0)
  {
    m_AccumulationTime += cur_time - m_LastUpdate;

    while (m_AccumulationTime > frame_interval)
    {
      m_Sprite.GetResource()->FrameAdvance(anim_hash, m_State, true, (int)m_Data.m_FrameAdvance);
      m_AccumulationTime -= frame_interval;
    }
  }

  m_LastUpdate = cur_time;

  SetActiveArea(Box::FromFrameCenterAndSize(Vector2(m_Data.m_PositionX, m_Data.m_PositionY), Vector2(m_State.m_FrameWidth, m_State.m_FrameHeight)));
  SetOffset(Vector2(m_Data.m_PositionX, m_Data.m_PositionY) - Vector2(m_State.m_FrameWidth, m_State.m_FrameHeight));

  UIElement::Update(dt);
  SetActiveArea(Box::FromFrameCenterAndSize(Vector2(m_Data.m_PositionX, m_Data.m_PositionY), Vector2(m_State.m_FrameWidth, m_State.m_FrameHeight)));
  SetOffset(Vector2(m_Data.m_PositionX, m_Data.m_PositionY) - Vector2(m_State.m_FrameWidth, m_State.m_FrameHeight));
}

void UIElementSpriteFrame::Render(RenderState & render_state, RenderUtil & render_util, const Vector2 & offset)
{
  if (m_Data.m_Enabled == 0)
  {
    return;
  }

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

  m_State.m_Matrix.x = sc.x * m_Data.m_ScaleX;
  m_State.m_Matrix.y = sc.y * m_Data.m_ScaleX;
  m_State.m_Matrix.z = -sc.y * m_Data.m_ScaleY;
  m_State.m_Matrix.w = sc.x * m_Data.m_ScaleY;

  m_Sprite.GetResource()->Render(render_state, m_State, Vector2((int)m_Data.m_PositionX, (int)m_Data.m_PositionY) + offset);
}

const UIElementSpriteFrameInitData & UIElementSpriteFrame::GetInitData()
{
  return m_InitData;
}

UIElementSpriteFrameData & UIElementSpriteFrame::GetData()
{
  return m_Data;
}

NotNullPtr<UIElementDataBase> UIElementSpriteFrame::GetBaseData()
{
  return &m_Data;
}

NullOptPtr<UIElementDataFrameCenter> UIElementSpriteFrame::GetFrameCenterData()
{
  return &m_Data;
}

NullOptPtr<UIElementDataStartEnd> UIElementSpriteFrame::GetStartEndData()
{
  return nullptr;
}

void UIElementSpriteFrame::SetCustomRenderCallback(Delegate<void, UIElementSpriteFrame &, RenderState &, const Vector2 &> && render_callback)
{
  m_RenderDelegate = std::move(render_callback);
}

SpritePtr & UIElementSpriteFrame::GetSprite()
{
  return m_Sprite;
}

StormExprValueInitBlock & UIElementSpriteFrame::GetLocalInitBlock()
{
  return s_LocalInitBlock;
}

StormExprValueInitBlock & UIElementSpriteFrame::GetAsParentInitBlock()
{
  return s_AsParentInitBlock;
}

StormExprBindingList & UIElementSpriteFrame::GetBindingList()
{
  return s_BindingList;
}



