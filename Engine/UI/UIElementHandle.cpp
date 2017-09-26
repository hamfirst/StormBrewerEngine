
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


NullOptPtr<const UIElement> UIElementHandle::Resolve() const
{
  if (m_UIManager == nullptr)
  {
    return nullptr;
  }

  return m_UIManager->ResolveHandle(m_Type, *this);
}

void UIElementHandle::Destroy()
{
  auto elem = Resolve();
  if (elem == nullptr)
  {
    return;
  }

  elem->Destroy();
}

void UIElementHandle::SetInput(uint32_t name_hash, float val)
{
  auto elem = Resolve();
  if (elem == nullptr)
  {
    return;
  }

  elem->SetInput(name_hash, val);
}

void UIElementHandle::SetInput(uint32_t name_hash, czstr val)
{
  auto elem = Resolve();
  if (elem == nullptr)
  {
    return;
  }

  elem->SetInput(name_hash, val);
}

void UIElementHandle::SetInput(uint32_t name_hash, const std::string & val)
{
  auto elem = Resolve();
  if (elem == nullptr)
  {
    return;
  }

  elem->SetInput(name_hash, val);
}
