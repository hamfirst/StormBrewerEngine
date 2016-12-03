#pragma once

#include "Engine/Input/KeyboardState.h"

class InputState
{
public:
  InputState();

  void Update(bool in_focus);

  BinaryControlHandle BindBinaryControl(const ControlId & control, int priority, ControlBindingMode mode, const Delegate<void, bool> & callback);
  void UnbindBinaryControl(const BinaryControlHandle & handle);

  void HandleKeypressMessage(int scan_code, bool pressed);

  void SetBinaryControlInputCallback(const Delegate<void, const ControlId &> & callback);
  void ClearBinaryControlInputCallback();

private:

  friend class ControlHandle;
  friend class KeyboardState;

  KeyboardState m_KeyboardState;

  Delegate<void, const ControlId &> m_BinaryControlCallback;
};
