#pragma once

#include "Foundation/Delegate/DelegateList.h"

#include "Engine/Input/ControlBindingList.h"
#include "Engine/Input/BinaryControlBinding.h"
#include "Engine/Input/ScalarControlBinding.h"
#include "Engine/Input/ControlHandle.h"
#include "Engine/Input/ControlId.h"

static const int kMaxGamepads = 8;

class InputState;

class GamepadState
{
public:

  GamepadState(NotNullPtr<InputState> input_state);

  void CheckDeltaState(bool in_focus);

  void GamepadConnected(int joystick_id);
  void GamepadDisonnected(int joystick_id);

  BinaryControlHandle AddControllerConnectedBinding(int gamepad_idx, int priority, ControlBindingMode mode, const Delegate<void, bool> & callback);
  void RemoveControllerConnectedBinding(BinaryControlHandle handle);

  BinaryControlHandle AddButtonBinding(GamepadButton button, int gamepad_idx, int priority, ControlBindingMode mode, const Delegate<void, bool> & callback);
  void RemoveButtonBinding(BinaryControlHandle handle);

  ScalarControlHandle AddAxisBinding(GamepadAxis axis, int gamepad_idx, int priority, ControlBindingMode mode, const Delegate<void, float> & callback);
  void RemoveAxisBinding(ScalarControlHandle handle);

private:

  InputState * m_InputState;
  void * m_OpenJoysticks[kMaxGamepads];

  ControlBindingList<BinaryControlBinding> m_ControllerConnected[kMaxGamepads];

  bool m_PressedState[kMaxGamepads][(int)GamepadButton::kCount] = {};
  bool m_PressedThisFrame[kMaxGamepads][(int)GamepadButton::kCount] = {};
  ControlBindingList<BinaryControlBinding> m_ButtonControls[kMaxGamepads][(int)GamepadButton::kCount];

  ControlBindingList<ScalarControlBinding> m_AxisControls[kMaxGamepads][(int)GamepadAxis::kCount];
};
