#pragma once

#include "Engine/UI/UIClickable.h"

class UIClickablePtr
{
public:
  UIClickablePtr();
  UIClickablePtr(const UIClickablePtr & rhs) = delete;
  UIClickablePtr(UIClickablePtr && rhs);

  UIClickablePtr & operator = (const UIClickablePtr & rhs) = delete;
  UIClickablePtr & operator = (UIClickablePtr && rhs);

  ~UIClickablePtr();

  void Clear();

  NullOptPtr<UIClickable> Get();
  NullOptPtr<const UIClickable> Get() const;

  NullOptPtr<UIClickable> operator -> ();
  NullOptPtr<const UIClickable> operator -> () const;

private:

  friend class UIManager;

  UIClickablePtr(NotNullPtr<UIClickable> clickable);

private:

  NullOptPtr<UIClickable> m_Clickable;
};
