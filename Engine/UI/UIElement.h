#pragma once

#include "Engine/EngineCommon.h"
#include "Engine/UI/UIElementHandle.h"

#include "Foundation/SkipField/SkipFieldIterator.h"

class RenderState;
class RenderUtil;

enum UIElementState
{
  kInactive,
  kActive,
  kHover,
  kPressed,
};

using UIOnClickHandler = Delegate<void, NotNullPtr<UIElement>>;
using UIOnStateChangeHandler = Delegate<void, UIElementState, UIElementState>;
using UIOnUpdateHandler = Delegate<void, NotNullPtr<UIElement>>;

class UIElement
{
public:

  virtual void Update();
  virtual void Render(RenderState & render_state, RenderUtil & render_util, const Vector2 & offset);

  void SetActive();
  void SetInactive();

  void SetEnabled();
  void SetDisabled();

  void Destroy();

  UIElementHandle GetHandle();

  UIElementState GetState();
  Optional<Box> GetActiveArea();

  NullOptPtr<UIElement> GetChild(uint32_t child_name_hash);
  NullOptPtr<UIElement> GetParent();

  void SetOnUpdateHandler(UIOnUpdateHandler && handler);
  void SetOnClickHandler(UIOnClickHandler && handler);
  void SetOnStateChangeHandler(UIOnStateChangeHandler && handler);

protected:
  void SetActiveArea(const Box & box);
  void SetOffset(const Vector2 & offset);

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
  UIOnStateChangeHandler m_OnStateChange;
  UIOnUpdateHandler m_OnUpdate;

  Box m_ActiveArea;
  Vector2 m_Offset;
  UIElementState m_State = UIElementState::kInactive;
  bool m_Enabled = true;
};
