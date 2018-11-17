#pragma once

#include "Engine/EngineCommon.h"
#include "Engine/UI/UIElementHandle.h"

template <typename UIElement>
class UIElementPtr
{
private:
  UIElementPtr(NotNullPtr<UIElement> ptr) :
    m_Ptr(ptr),
    m_Handle(),
    m_Owning(true)
  {

  }

  UIElementPtr(const UIElementHandle & handle) :
    m_Ptr(nullptr),
    m_Handle(handle),
    m_Owning(false)
  {

  }

public:
  UIElementPtr() :
    m_Ptr(nullptr),
    m_Handle(),
    m_Owning(true)
  {

  }

  UIElementPtr(const UIElementPtr<UIElement> & rhs) = delete;
  UIElementPtr(UIElementPtr<UIElement> && rhs) :
    m_Ptr(rhs.m_Ptr),
    m_Handle(std::move(rhs.m_Handle)),
    m_Owning(rhs.m_Owning)
  {
    rhs.m_Ptr = nullptr;
    rhs.m_Owning = true;
  }

  ~UIElementPtr()
  {
    if (m_Ptr && m_Owning)
    {
      m_Ptr->Destroy();
    }
  }

  UIElementPtr & operator = (const UIElementPtr<UIElement> & rhs) = delete;
  UIElementPtr & operator = (UIElementPtr<UIElement> && rhs)
  {    
    Clear();
    m_Ptr = rhs.m_Ptr;
    m_Handle = std::move(rhs.m_Handle);
    m_Owning = rhs.m_Owning;
    rhs.m_Ptr = nullptr;
    rhs.m_Owning = true;
    return *this;
  }

  void Clear()
  {
    if (m_Ptr)
    {
      if (m_Owning)
      {
        m_Ptr->Destroy();
      }

      m_Ptr = nullptr;
      m_Owning = true;
    }
  }

  void Release()
  {
    m_Ptr = nullptr;
    m_Owning = true;
  }

  NullOptPtr<UIElement> Get()
  {
    if (m_Owning)
    {
      return m_Ptr;
    }
    else
    {
      return m_Handle.ResolveTo<UIElement>();
    }
  }

  NullOptPtr<const UIElement> Get() const
  {
    if (m_Owning)
    {
      return m_Ptr;
    }
    else
    {
      return m_Handle.ResolveTo<UIElement>();
    }
  }

  NullOptPtr<UIElement> operator -> ()
  {
    return Get();
  }

  NullOptPtr<const UIElement> operator -> () const
  {
    return Get();
  }

  operator NullOptPtr<UIElement>()
  {
    return Get();
  }

  operator NullOptPtr<const UIElement>() const
  {
    return Get();
  }

private:

  friend class UIManager;

  NotNullPtr<UIElement> m_Ptr;
  UIElementHandle m_Handle;
  bool m_Owning;
};
