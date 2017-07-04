
#include "Engine/EngineCommon.h"
#include "Engine/UI/UIElement.h"

void UIElement::Update()
{
  for (auto elem : m_Children)
  {
    elem->Update();
  }
}

void UIElement::Render(RenderState & render_state, RenderUtil & render_util)
{

}

UIElementHandle UIElement::GetHandle()
{
  return m_Handle;
}

Optional<Box> UIElement::GetActiveArea()
{
  if (m_Active)
  {
    return m_ActiveArea;
  }

  return{};
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

void UIElement::SetOnClickHandler(UIOnClickHandler && handler)
{
  m_OnClick = std::move(handler);
}

void UIElement::SetOnActivationChangeHandler(UIOnActivationChangeHandler && handler)
{
  m_OnActivationChanged = std::move(handler);
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
