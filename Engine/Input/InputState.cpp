
#include "Engine/EngineCommon.h"
#include "Engine/Input/InputState.h"

InputState::InputState() :
  m_KeyboardState(this),
  m_MouseState(this)
{

}

void InputState::Update(bool in_keyboard_focus, bool in_mouse_focus, const Box & window_geo)
{
  m_KeyboardState.CheckDeltaState(in_keyboard_focus);
  m_MouseState.CheckDeltaState(window_geo, in_mouse_focus);
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

bool InputState::GetMouseButtonSate(int button)
{
  return m_MouseState.GetButtonState(button);
}

PointerState InputState::GetPointerState()
{
  return m_MouseState.GetPointerState();
}

DelegateLink<void, bool, ControlId> InputState::RegisterKeyboardPassThroughCallback(const Delegate<void, bool, ControlId> & del)
{
  return m_KeyboardState.RegisterPassThroughDelegate(del);
}

void InputState::HandleKeyPressMessage(int scan_code, bool pressed)
{
  m_KeyboardState.HandleKeyPressMessage(scan_code, pressed);
}

void InputState::HandleMouseButtonPressMessage(int button, bool pressed, bool in_focus)
{
  m_MouseState.HandleButtonPressMessage(button, pressed);
}

void InputState::HandleMouseMoveMessage(int x, int y, const Box & window_geo, bool in_focus)
{
  m_MouseState.HandleMouseMoveMessage(x, y, window_geo, in_focus);
}
