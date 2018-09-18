#pragma once

#include "Foundation/Delegate/DelegateList.h"

#include "Engine/Input/ControlBindingList.h"
#include "Engine/Input/BinaryControlBinding.h"
#include "Engine/Input/ScalarControlBinding.h"
#include "Engine/Input/ControlHandle.h"
#include "Engine/Input/ControlId.h"

static const int kMaxGamepads = 8;

class InputState;

class ENGINE_EXPORT GamepadState
{
public:

  GamepadState(NotNullPtr<InputState> input_state);

  static void Init();
  static void Cleanup();

  static void GamepadConnected(int joystick_idx);
  static void GamepadDisonnected(int joystick_id);

  void CheckDeltaState(bool in_focus);

  BinaryControlHandle AddControllerConnectedBinding(int gamepad_idx, int priority, ControlBindingMode mode, const Delegate<void, bool> & callback);
  void RemoveControllerConnectedBinding(BinaryControlHandle handle);
  bool IsGamepadConnected(int gamepad_idx);

  BinaryControlHandle AddButtonBinding(GamepadButton button, int gamepad_idx, int priority, ControlBindingMode mode, const Delegate<void, bool> & callback);
  void RemoveButtonBinding(BinaryControlHandle handle);
  bool IsButtonPressed(int gamepad_idx, GamepadButton button); 
  bool IsButtonPressedThisFrame(int gamepad_idx, GamepadButton button);

  ScalarControlHandle AddAxisBinding(GamepadAxis axis, int gamepad_idx, int priority, ControlBindingMode mode, const Delegate<void, float> & callback);
  void RemoveAxisBinding(ScalarControlHandle handle);
  float GetAxis(int gamepad_idx, GamepadAxis axis);

private:

  InputState * m_InputState;
  static void * m_OpenGamePads[kMaxGamepads];

  bool m_ConnectedState[kMaxGamepads] = {};
  ControlBindingList<BinaryControlBinding> m_ControllerConnected[kMaxGamepads];

  bool m_PressedState[kMaxGamepads][(int)GamepadButton::kCount] = {};
  bool m_PressedThisFrame[kMaxGamepads][(int)GamepadButton::kCount] = {};
  ControlBindingList<BinaryControlBinding> m_ButtonControls[kMaxGamepads][(int)GamepadButton::kCount];

  float m_AxisValue[kMaxGamepads][(int)GamepadAxis::kCount] = {};
  ControlBindingList<ScalarControlBinding> m_AxisControls[kMaxGamepads][(int)GamepadAxis::kCount];
};
