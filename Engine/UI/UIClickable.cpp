
#include "Engine/EngineCommon.h"
#include "Engine/UI/UIClickable.h"
#include "Engine/UI/UIManager.h"

UIClickable::UIClickable(UIClickableConstructorTag)
{

}

void UIClickable::SetEnabled()
{
  if (m_State == UIClickableState::kDisabled)
  {
    m_OnStateChange(UIClickableState::kActive, m_State);
    m_State = UIClickableState::kActive;
  }
}

void UIClickable::SetDisabled()
{
  if (m_State != UIClickableState::kDisabled)
  {
    m_OnStateChange(UIClickableState::kDisabled, m_State);
    m_State = UIClickableState::kDisabled;
  }
}

UIClickableState UIClickable::GetState()
{
  return m_State;
}

void UIClickable::SetOnClickHandler(UIClickableOnClickHandler && handler)
{
  m_OnClick = std::move(handler);
}

void UIClickable::SetOnStateChangeHandler(UIClickableOnStateChangeHandler && handler)
{
  m_OnStateChange = std::move(handler);
}

Box UIClickable::GetActiveArea()
{
  return m_ActiveArea;
}

void UIClickable::SetActiveArea(const Box & box)
{
  m_ActiveArea = box;
}

void UIClickable::SetHandle(Handle & handle)
{
  m_Handle = handle;
}

Handle & UIClickable::GetHandle()
{
  return m_Handle;
}

void UIClickable::SetIterator(const SkipFieldIterator & itr)
{
  m_Iterator = itr;
}

const SkipFieldIterator & UIClickable::GetIterator() const
{
  return m_Iterator;
}

void UIClickable::Destroy()
{
  m_Manager->ReleaseClickable(this);
}
