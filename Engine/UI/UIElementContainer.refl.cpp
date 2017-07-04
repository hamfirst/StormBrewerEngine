
#include "Engine/EngineCommon.h"
#include "Engine/UI/UIElementContainer.refl.h"

#include "Engine/Rendering/RenderUtil.h"
#include "Engine/Shader/ShaderManager.h"

int UIElementContainer::Type = 1;

UIElementContainer::UIElementContainer(const UIElementContainerInitData & init_data, const UIElementContainerData & data) :
  m_InitData(init_data),
  m_Data(data)
{

}

void UIElementContainer::Update()
{
  UIElement::Update();
}

void UIElementContainer::Render(RenderState & render_state, RenderUtil & render_util)
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

void UIElementContainer::RenderDefault(RenderState & render_state, RenderUtil & render_util)
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

void UIElementContainer::SetCustomRenderCallback(Delegate<void, UIElementContainer &, RenderState &> && render_callback)
{
  m_RenderDelegate = std::move(render_callback);
}

