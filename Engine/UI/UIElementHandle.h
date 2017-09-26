#pragma once

#include "Engine/EngineCommon.h"

#include "Runtime/UI/UIDef.refl.h"

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

  UIElementType GetType() const;

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
  NullOptPtr<const UIElement> Resolve() const;

  void Destroy();

  void SetInput(uint32_t name_hash, float val);
  void SetInput(uint32_t name_hash, czstr val);
  void SetInput(uint32_t name_hash, const std::string & val);

protected:

  friend class UIManager;
  friend class UIElement;

private:

  UIElementType m_Type;
  NotNullPtr<UIManager> m_UIManager = nullptr;
};

