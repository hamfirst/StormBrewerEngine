#pragma once

#include "Foundation/Delegate/DelegateList.h"

#include "Engine/Input/ControlBindingList.h"
#include "Engine/Input/BinaryControlBinding.h"
#include "Engine/Input/ControlHandle.h"

static const int kNumKeyboardKeys = 512;

class InputState;

class ENGINE_EXPORT KeyboardState
{
public:
  KeyboardState(NotNullPtr<InputState> input_state);

  void CheckDeltaState(bool in_focus, bool text_input_active, bool query_state);

  BinaryControlHandle AddKeyBinding(int scan_code, int priority, ControlBindingMode mode, const Delegate<void, bool> & callback);
  void RemoveKeyBinding(BinaryControlHandle handle);

  bool GetKeyState(int scan_code);
  bool GetKeyPressedThisFrame(int scan_code);

  void HandleKeyPressMessage(int scan_code, bool pressed, bool text_input_active);

  DelegateLink<void, bool, ControlId> RegisterPassThroughDelegate(const Delegate<void, bool, ControlId> & del);

  static czstr GetKeyNameForScanCode(int scan_code);
  static bool ScanCodeBlockeByTextInput(int scan_code);
  static int ScanCodeFromJavascriptCode(int javascript_key_code);
  static int ScanCodeFromQtCode(int qt_key_code);

protected:

  friend class ControlHandle;
  NullOptPtr<void> GetControlBinding(const ControlHandle & handle);

private:
  InputState * m_InputState;
  bool m_PressedState[kNumKeyboardKeys] = {};
  bool m_PressedThisFrame[kNumKeyboardKeys] = {};
  bool m_PressedLastFrame[kNumKeyboardKeys] = {};
  ControlBindingList<BinaryControlBinding> m_KeyboardControls[kNumKeyboardKeys];

  DelegateList<void, bool, ControlId> m_PassThroughCallbacks;
};
