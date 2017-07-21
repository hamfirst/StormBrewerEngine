
#include "Engine/EngineCommon.h"
#include "Engine/UI/UIElement.h"
#include "Engine/UI/UIManager.h"

void UIElement::Update()
{
  m_OnUpdate(this);

  for (auto elem : m_Children)
  {
    elem->Update();
  }
}

void UIElement::Render(RenderState & render_state, RenderUtil & render_util, const Vector2 & offset)
{
  auto child_offset = offset + m_Offset;
  for (auto child : m_Children)
  {
    child->Render(render_state, render_util, child_offset);
  }
}

void UIElement::SetActive()
{
  if (m_State == UIElementState::kInactive)
  {
    m_OnStateChange(m_State, UIElementState::kActive);
    m_State = UIElementState::kActive;
  }
}

void UIElement::SetInactive()
{
  if (m_State != UIElementState::kInactive)
  {
    m_OnStateChange(m_State, UIElementState::kInactive);
    m_State = UIElementState::kInactive;
  }
}

void UIElement::SetEnabled()
{
  m_Enabled = true;
}

void UIElement::SetDisabled()
{
  m_Enabled = false;
  if (m_State == UIElementState::kPressed || m_State == UIElementState::kHover)
  {
    m_OnStateChange(m_State, UIElementState::kActive);
    m_State = UIElementState::kActive;
  }
}

void UIElement::Destroy()
{
  m_Handle.m_UIManager->UnlinkElement(this);
}

UIElementHandle UIElement::GetHandle()
{
  return m_Handle;
}

UIElementState UIElement::GetState()
{
  return m_State;
}

Optional<Box> UIElement::GetActiveArea()
{
  if (m_State == UIElementState::kInactive)
  {
    return{};
  }

  return m_ActiveArea;
}

NullOptPtr<UIElement> UIElement::GetChild(uint32_t child_name_hash)
{
  for (auto child : m_Children)
  {
    if (child->m_NameHash == child_name_hash)
    {
      return child;
    }
  }

  return nullptr;
}

NullOptPtr<UIElement> UIElement::GetParent()
{
  return m_Parent;
}

void UIElement::SetOnUpdateHandler(UIOnUpdateHandler && handler)
{
  m_OnUpdate = std::move(handler);
}

void UIElement::SetOnClickHandler(UIOnClickHandler && handler)
{
  m_OnClick = std::move(handler);
}

void UIElement::SetOnStateChangeHandler(UIOnStateChangeHandler && handler)
{
  m_OnStateChange = std::move(handler);
}

void UIElement::SetActiveArea(const Box & box)
{
  m_ActiveArea = box;
}

void UIElement::SetOffset(const Vector2 & offset)
{
  m_Offset = offset;
}

void UIElement::SetHandle(Handle & handle)
{
  Handle & my_handle = m_Handle;
  my_handle = handle;
}

void UIElement::SetIterator(const SkipFieldIterator & itr)
{
  m_Iterator = itr;
}

const SkipFieldIterator & UIElement::GetIterator() const
{
  return m_Iterator;
}
