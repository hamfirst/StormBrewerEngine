#pragma once

#include "Engine/EngineCommon.h"

class UIElement;
class UIManager;

class UIElementHandle : public Handle
{
public:

  UIElementHandle() = default;
  UIElementHandle(const UIElementHandle & rhs) = default;
  UIElementHandle(UIElementHandle && rhs) = default;

  UIElementHandle & operator =(const UIElementHandle & rhs) = default;
  UIElementHandle & operator =(UIElementHandle && rhs) = default;

  bool operator == (const UIElementHandle && rhs);
  bool operator != (const UIElementHandle && rhs);

  template <typename UIElement>
  NullOptPtr<UIElement> ResolveTo()
  {
    if (m_Type != UIElement::Type)
    {
      return nullptr;
    }

    return static_cast<UIElement *>(Resolve());
  }

  template <typename UIElement>
  NullOptPtr<const UIElement> ResolveTo() const
  {
    if (m_Type != UIElement::Type)
    {
      return nullptr;
    }

    return static_cast<const UIElement *>(Resolve());
  }

  NullOptPtr<UIElement> Resolve();

protected:

  friend class UIManager;
  friend class UIElement;

private:

  uint32_t m_Type;
  NotNullPtr<UIManager> m_UIManager = nullptr;
};

