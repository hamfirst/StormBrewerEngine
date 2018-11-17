
#include "Engine/EngineCommon.h"
#include "Engine/UI/UIClickablePtr.h"

UIClickablePtr::UIClickablePtr() :
  m_Clickable(nullptr)
{

}

UIClickablePtr::UIClickablePtr(NotNullPtr<UIClickable> clickable) :
  m_Clickable(clickable)
{

}

UIClickablePtr::UIClickablePtr(UIClickablePtr && rhs) :
  m_Clickable(rhs.m_Clickable)
{
  rhs.m_Clickable = nullptr;
}

UIClickablePtr & UIClickablePtr::operator = (UIClickablePtr && rhs)
{
  Clear();
  m_Clickable = rhs.m_Clickable;
  rhs.m_Clickable = nullptr;
  return *this;
}

UIClickablePtr::~UIClickablePtr()
{
  Clear();
}

void UIClickablePtr::Clear()
{
  if (m_Clickable)
  {
    m_Clickable->Destroy();
    m_Clickable = nullptr;
  }
}

NullOptPtr<UIClickable> UIClickablePtr::Get()
{
  return m_Clickable;
}

NullOptPtr<const UIClickable> UIClickablePtr::Get() const
{
  return m_Clickable;
}

NullOptPtr<UIClickable> UIClickablePtr::operator -> ()
{
  return m_Clickable;
}

NullOptPtr<const UIClickable> UIClickablePtr::operator -> () const
{
  return m_Clickable;
}
