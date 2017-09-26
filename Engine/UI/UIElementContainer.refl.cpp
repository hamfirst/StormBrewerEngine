
#include "Engine/EngineCommon.h"
#include "Engine/UI/UIElementContainer.refl.meta.h"

#include "Engine/Rendering/RenderUtil.h"
#include "Engine/Shader/ShaderManager.h"

#include "StormData/StormDataJson.h"

#include "Runtime/UI/UIElementTypeRegister.h"

STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(UIElementContainerInitData);
REGISTER_UIELEMENT_DATA(UIElementContainer, UIElementContainerInitData, UIElementContainerData);

UIElementType UIElementContainer::Type = UIElementType::kContainer;

static auto s_LocalInitBlock = StormExprCreateInitBlockForDataType<UIElementContainerData>();
static auto s_AsParentInitBlock = StormExprCreateInitBlockForDataType<UIElementContainerData>("p.");
static auto s_BindingList = StormExprGetBindingList<UIElementContainerData>();

UIElementContainer::UIElementContainer(const UIElementContainerInitData & init_data, const UIElementContainerData & data) :
  m_InitData(init_data),
  m_Data(data)
{

}

void UIElementContainer::Update(float dt)
{
  SetActiveArea(Box::FromPoints(Vector2(m_Data.m_StartX, m_Data.m_StartY), Vector2(m_Data.m_EndX, m_Data.m_EndY)));
  SetOffset(Vector2(m_Data.m_StartX, m_Data.m_StartY));

  UIElement::Update(dt);
  SetActiveArea(Box::FromPoints(Vector2(m_Data.m_StartX, m_Data.m_StartY), Vector2(m_Data.m_EndX, m_Data.m_EndY)));
  SetOffset(Vector2(m_Data.m_StartX, m_Data.m_StartY));
}

void UIElementContainer::Render(RenderState & render_state, RenderUtil & render_util, const Vector2 & offset)
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

void UIElementContainer::RenderDefault(RenderState & render_state, RenderUtil & render_util, const Vector2 & offset)
{

}

const UIElementContainerInitData & UIElementContainer::GetInitData()
{
  return m_InitData;
}

UIElementContainerData & UIElementContainer::GetData()
{
  return m_Data;
}

NotNullPtr<UIElementDataBase> UIElementContainer::GetBaseData()
{
  return &m_Data;
}

NullOptPtr<UIElementDataFrameCenter> UIElementContainer::GetFrameCenterData()
{
  return nullptr;
}

NullOptPtr<UIElementDataStartEnd> UIElementContainer::GetStartEndData()
{
  return &m_Data;
}

void UIElementContainer::SetCustomRenderCallback(Delegate<void, UIElementContainer &, RenderState &, const Vector2 &> && render_callback)
{
  m_RenderDelegate = std::move(render_callback);
}

StormExprValueInitBlock & UIElementContainer::GetLocalInitBlock()
{
  return s_LocalInitBlock;
}

StormExprValueInitBlock & UIElementContainer::GetAsParentInitBlock()
{
  return s_AsParentInitBlock;
}

StormExprBindingList & UIElementContainer::GetBindingList()
{
  return s_BindingList;
}
