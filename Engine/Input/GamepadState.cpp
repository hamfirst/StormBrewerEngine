
#include "Engine/EngineCommon.h"
#include "Engine/Input/GamepadState.h"
#include "Engine/Input/InputState.h"

#include <SDL/SDL_joystick.h>


GamepadState::GamepadState(NotNullPtr<InputState> input_state) :
  m_InputState(input_state)
{
}

void GamepadState::CheckDeltaState(bool in_focus)
{

}

void GamepadState::GamepadConnected(int gamepad_idx)
{
  if (gamepad_idx >= kMaxGamepads)
  {
    return;
  }

  SDL_Joystick * js = SDL_JoystickOpen(gamepad_idx);
}

void GamepadState::GamepadDisonnected(int gamepad_idx)
{

}

BinaryControlHandle GamepadState::AddControllerConnectedBinding(int gamepad_idx, int priority, ControlBindingMode mode, const Delegate<void, bool> & callback)
{
  Handle handle = m_ControllerConnected[gamepad_idx].CreateControlBinding(priority, mode, callback);
  return BinaryControlHandle(m_InputState, handle, CreateGamepadConnectionBinding(gamepad_idx));
}

void GamepadState::RemoveControllerConnectedBinding(BinaryControlHandle handle)
{
  m_ControllerConnected[handle.m_ControlId.m_Index].RemoveControlBinding(handle.m_Control);
}

BinaryControlHandle GamepadState::AddButtonBinding(GamepadButton button, int gamepad_idx, int priority, ControlBindingMode mode, const Delegate<void, bool> & callback)
{
  Handle handle = m_ButtonControls[gamepad_idx][(int)button].CreateControlBinding(priority, mode, callback);
  return BinaryControlHandle(m_InputState, handle, CreateGamepadButtonBinding(gamepad_idx, button));
}

void GamepadState::RemoveButtonBinding(BinaryControlHandle handle)
{
  m_ButtonControls[handle.m_ControlId.m_Index][handle.m_ControlId.m_SubIndex].RemoveControlBinding(handle.m_Control);
}

ScalarControlHandle GamepadState::AddAxisBinding(GamepadAxis axis, int gamepad_idx, int priority, ControlBindingMode mode, const Delegate<void, float> & callback)
{
  Handle handle = m_AxisControls[gamepad_idx][(int)axis].CreateControlBinding(priority, mode, callback);
  return ScalarControlHandle(m_InputState, handle, CreateGamepadAxisBinding(gamepad_idx, axis));
}

void GamepadState::RemoveAxisBinding(ScalarControlHandle handle)
{
  m_AxisControls[handle.m_ControlId.m_Index][handle.m_ControlId.m_SubIndex].RemoveControlBinding(handle.m_Control);
}
