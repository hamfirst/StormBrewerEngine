#pragma once

#include <SDL/SDL_scancode.h>

#include "Engine/Input/ControlBindingList.h"
#include "Engine/Input/BinaryControlBinding.h"
#include "Engine/Input/ControlHandle.h"

class InputState;

class KeyboardState
{
public:
  KeyboardState(NotNullPtr<InputState> input_state);

  void CheckDeltaState(bool in_focus);

  BinaryControlHandle AddKeyBinding(int scan_code, int priority, ControlBindingMode mode, const Delegate<void, bool> & callback);
  void RemoveKeyBinding(BinaryControlHandle handle);

  void HandleKeyPressMessage(int scan_code, bool pressed);

  static czstr GetKeyNameForScanCode(int scan_code);

protected:

  friend class ControlHandle;
  NullOptPtr<void> GetControlBinding(const ControlHandle & handle);

private:
  InputState * m_InputState;
  bool m_PressedState[SDL_NUM_SCANCODES] = {};
  ControlBindingList<BinaryControlBinding> m_KeyboardControls[SDL_NUM_SCANCODES];
};
