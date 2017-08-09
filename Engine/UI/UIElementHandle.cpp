
#include "Engine/EngineCommon.h"
#include "Engine/UI/UIElementHandle.h"
#include "Engine/UI/UIManager.h"


bool UIElementHandle::operator == (const UIElementHandle && rhs)
{
  return m_Type == rhs.m_Type && *static_cast<const Handle *>(this) == *static_cast<const Handle *>(&rhs) && m_UIManager == rhs.m_UIManager;
}

bool UIElementHandle::operator != (const UIElementHandle && rhs)
{
  return m_Type != rhs.m_Type || *static_cast<const Handle *>(this) != *static_cast<const Handle *>(&rhs) || m_UIManager != rhs.m_UIManager;
}

UIElementType UIElementHandle::GetType() const
{
  return m_Type;
}

NullOptPtr<UIElement> UIElementHandle::Resolve()
{
  if (m_UIManager == nullptr)
  {
    return nullptr;
  }
  
  return m_UIManager->ResolveHandle(m_Type, *this);
}


