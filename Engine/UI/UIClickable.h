#pragma once

#include "Engine/EngineCommon.h"
#include "Engine/UI/UIElementHandle.h"

#include "Foundation/SkipField/SkipFieldIterator.h"

class RenderState;
class RenderUtil;

enum class UIClickableState
{
  kDisabled,
  kActive,
  kHover,
  kPressed,
};

using UIClickableOnClickHandler = Delegate<void>;
using UIClickableOnStateChangeHandler = Delegate<void, UIClickableState, UIClickableState>;


class UIClickable
{
private:

  struct UIClickableConstructorTag {};

public:

  UIClickable(UIClickableConstructorTag);

  void SetEnabled();
  void SetDisabled();

  UIClickableState GetState();

  void SetOnClickHandler(UIClickableOnClickHandler && handler);
  void SetOnStateChangeHandler(UIClickableOnStateChangeHandler && handler);

  Box GetActiveArea();
  void SetActiveArea(const Box & box);

private:

  template <typename Type>
  friend class SkipField;

  friend class UIManager;
  friend class UIClickablePtr;

  void SetHandle(Handle & handle);
  Handle & GetHandle();
  void SetIterator(const SkipFieldIterator & itr);
  const SkipFieldIterator & GetIterator() const;

  void Destroy();

private:

  Handle m_Handle;
  SkipFieldIterator m_Iterator;

  NotNullPtr<UIManager> m_Manager;

  UIClickableOnClickHandler m_OnClick;
  UIClickableOnStateChangeHandler m_OnStateChange;

  Box m_ActiveArea;
  UIClickableState m_State = UIClickableState::kActive;
};
