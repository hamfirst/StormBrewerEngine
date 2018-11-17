
#include "Engine/EngineCommon.h"
#include "Engine/Input/InputState.h"
#include "Engine/Input/GamepadState.h"
#include "Engine/Window/Window.h"

InputState::InputState() :
  m_KeyboardState(this),
  m_MouseState(this),
  m_GamepadState(this)
{

}

void InputState::Update(bool in_keyboard_focus, bool in_mouse_focus, bool text_input_active, const Box & window_geo, bool query_state)
{
  m_KeyboardState.CheckDeltaState(in_keyboard_focus, text_input_active, query_state);
  m_MouseState.CheckDeltaState(window_geo, in_mouse_focus, query_state);
  m_GamepadState.CheckDeltaState(in_keyboard_focus);
}

BinaryControlHandle InputState::BindBinaryControl(const ControlId & control, int priority, ControlBindingMode mode, const Delegate<void, bool> & callback)
{
  if (control.m_Type == ControlType::kKeyboard)
  {
    return m_KeyboardState.AddKeyBinding(control.m_Index, priority, mode, callback);
  }

  if (control.m_Type == ControlType::kMouse)
  {
    if (control.m_Index >= 0)
    {
      return m_MouseState.AddButtonBinding(control.m_Index, priority, mode, callback);
    }
  }

  return{};
}

void InputState::UnbindBinaryControl(const BinaryControlHandle & handle)
{
  if (handle.m_ControlId.m_Type == ControlType::kKeyboard)
  {
    m_KeyboardState.RemoveKeyBinding(handle);
    return;
  }

  if (handle.m_ControlId.m_Type == ControlType::kMouse)
  {
    if (handle.m_ControlId.m_Index >= 0)
    {
      m_MouseState.RemoveButtonBinding(handle);
    }
    return;
  }
}

PointerControlHandle InputState::BindPointerControl(const ControlId & control, int priority, ControlBindingMode mode, const Delegate<void, PointerState> & callback)
{
  if (control.m_Type == ControlType::kMouse)
  {
    if (control.m_Index == -1)
    {
      return m_MouseState.AddCursorBinding(priority, mode, callback);
    }
  }

  return{};
}

void InputState::UnbindPointerControl(const PointerControlHandle & handle)
{
  if (handle.m_ControlId.m_Type == ControlType::kMouse)
  {
    if (handle.m_ControlId.m_Index == -1)
    {
      m_MouseState.RemoveCursorBinding(handle);
    }
    return;
  }
}

void InputState::SetBinaryControlInputCallback(const Delegate<void, const ControlId &> & callback)
{
  m_BinaryControlCallback = callback;
}

void InputState::ClearBinaryControlInputCallback()
{
  m_BinaryControlCallback.Clear();
}

bool InputState::GetKeyState(int scan_code)
{
  return m_KeyboardState.GetKeyState(scan_code);
}

bool InputState::GetKeyPressedThisFrame(int scan_code)
{
  return m_KeyboardState.GetKeyPressedThisFrame(scan_code);
}

bool InputState::GetMouseButtonState(int button)
{
  return m_MouseState.GetButtonState(button);
}

bool InputState::GetMousePressedThisFrame(int button)
{
  return m_MouseState.GetButtonPressedThisFrame(button);
}

PointerState InputState::GetPointerState()
{
  return m_MouseState.GetPointerState();
}

bool InputState::GetGamepadConnected(int gamepad_idx)
{
  return m_GamepadState.IsGamepadConnected(gamepad_idx);
}

bool InputState::GetGamepadButtonState(int gamepad_idx, GamepadButton button)
{
  return m_GamepadState.IsButtonPressed(gamepad_idx, button);
}

bool InputState::GetGamepadButtonPressedThisFrame(int gamepad_idx, GamepadButton button)
{
  return m_GamepadState.IsButtonPressedThisFrame(gamepad_idx, button);
}

float InputState::GetGamepadAxis(int gamepad_idx, GamepadAxis axis)
{
  return m_GamepadState.GetAxis(gamepad_idx, axis);
}

Vector2f InputState::GetGamepadJoystick(int gamepad_idx, GamepadJoystick joystick)
{
  float x = 0;
  float y = 0;

  switch (joystick)
  {
  case GamepadJoystick::kLeft:
    x = GetGamepadAxis(gamepad_idx, GamepadAxis::kLeftHorz);
    y = GetGamepadAxis(gamepad_idx, GamepadAxis::kLeftVert);
    break;
  case GamepadJoystick::kRight:
    x = GetGamepadAxis(gamepad_idx, GamepadAxis::kRightHorz);
    y = GetGamepadAxis(gamepad_idx, GamepadAxis::kRightVert);
    break;
  }

  return Vector2f{ x, y };
}

KeyboardPassthroughCallbackLink InputState::RegisterKeyboardPassThroughCallback(const Delegate<void, bool, ControlId> & del)
{
  return m_KeyboardState.RegisterPassThroughDelegate(del);
}

void InputState::ApplyDeadZone(Vector2f & input, float dead_zone)
{
  auto input_str = glm::length(input);

  if (input_str > 1.0f)
  {
    input /= input_str;
    input_str = 1.0f;
  }

  if (input_str < dead_zone)
  {
    input = {};
    return;
  }

  auto alive_zone = 1.0f - dead_zone;
  input /= input_str;
  
  input_str -= dead_zone;
  input_str /= alive_zone;
  input *= input_str;
}

void InputState::HandleKeyPressMessage(int scan_code, bool pressed, bool text_input_active)
{
  m_KeyboardState.HandleKeyPressMessage(scan_code, pressed, text_input_active);
}

void InputState::HandleMouseButtonPressMessage(int button, bool pressed, bool in_focus)
{
  m_MouseState.HandleButtonPressMessage(button, pressed);
}

void InputState::HandleMouseMoveMessage(int x, int y, const Box & window_geo, bool in_focus)
{
  m_MouseState.HandleMouseMoveMessage(x, y, window_geo, in_focus);
}
