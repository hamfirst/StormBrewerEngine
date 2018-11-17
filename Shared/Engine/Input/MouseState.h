#pragma once

#include "Engine/Input/ControlBindingList.h"
#include "Engine/Input/BinaryControlBinding.h"
#include "Engine/Input/PointerControlBinding.h"
#include "Engine/Input/ControlHandle.h"

class InputState;

static const int kNumMouseButtons = 32;

class ENGINE_EXPORT MouseState
{
public:
  MouseState(NotNullPtr<InputState> input_state);

  void CheckDeltaState(const Box & window_geo, bool in_focus, bool query_state);

  BinaryControlHandle AddButtonBinding(int button, int priority, ControlBindingMode mode, const Delegate<void, bool> & callback);
  void RemoveButtonBinding(BinaryControlHandle handle);

  PointerControlHandle AddCursorBinding(int priority, ControlBindingMode mode, const Delegate<void, PointerState> & callback);
  void RemoveCursorBinding(PointerControlHandle handle);

  void HandleButtonPressMessage(int button, bool pressed);
  void HandleMouseMoveMessage(int x, int y, const Box & window_geo, bool in_focus);

  bool GetButtonState(int button);
  bool GetButtonPressedThisFrame(int button);
  PointerState GetPointerState();

  static bool GetCursorVisibility();
  static void SetCursorVisibility(bool visible);
  static void LockMouseToWindow(bool enable);

protected:

  friend class ControlHandle;
  NullOptPtr<void> GetButtonBinding(const ControlHandle & handle);
  NullOptPtr<void> GetPointerBinding(const ControlHandle & handle);

private:
  InputState * m_InputState;
  bool m_PressedState[kNumMouseButtons] = {};
  bool m_PressedThisFrame[kNumMouseButtons] = {};
  bool m_PressedLastFrame[kNumMouseButtons] = {};
  PointerState m_PointerState = {};
  ControlBindingList<BinaryControlBinding> m_ButtonControls[kNumMouseButtons];
  ControlBindingList<PointerControlBinding> m_PointerBinding;
};
