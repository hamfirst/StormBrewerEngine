#pragma once

#include "Engine/EngineCommon.h"
#include "Engine/UI/UIElementHandle.h"

#include "Foundation/SkipField/SkipFieldIterator.h"

class RenderState;
class RenderUtil;

using UIOnClickHandler = Delegate<void, NotNullPtr<UIElement>>;
using UIOnActivationChangeHandler = Delegate<void, NotNullPtr<UIElement>, bool>;

class UIElement
{
public:

  virtual void Update();
  virtual void Render(RenderState & render_state, RenderUtil & render_util);

  UIElementHandle GetHandle();

  Optional<Box> GetActiveArea();

  NullOptPtr<UIElement> GetChild(uint32_t child_name_hash);
  NullOptPtr<UIElement> GetParent();

  void SetOnClickHandler(UIOnClickHandler && handler);
  void SetOnActivationChangeHandler(UIOnActivationChangeHandler && handler);

private:

  template <typename Type>
  friend class SkipField;

  friend class UIManager;

  void SetHandle(Handle & handle);
  void SetIterator(const SkipFieldIterator & itr);
  const SkipFieldIterator & GetIterator() const;

private:

  UIElementHandle m_Handle;
  SkipFieldIterator m_Iterator;

  std::string m_Name;
  uint32_t m_NameHash;
  NullOptPtr<UIElement> m_Parent;
  std::vector<NotNullPtr<UIElement>> m_Children;

  UIOnClickHandler m_OnClick;
  UIOnActivationChangeHandler m_OnActivationChanged;


  Box m_ActiveArea;
  bool m_Active = false;
};
