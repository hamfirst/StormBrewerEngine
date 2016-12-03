
#include "Engine/EngineCommon.h"
#include "Engine/Input/InputState.h"

InputState::InputState() :
  m_KeyboardState(this)
{

}

void InputState::Update(bool in_focus)
{
  m_KeyboardState.CheckDeltaState(in_focus);
}

BinaryControlHandle InputState::BindBinaryControl(const ControlId & control, int priority, ControlBindingMode mode, const Delegate<void, bool> & callback)
{
  if (control.m_Type == ControlType::kKeyboard)
  {
    return m_KeyboardState.AddControlBinding(control.m_Index, priority, mode, callback);
  }

  return{};
}

void InputState::UnbindBinaryControl(const BinaryControlHandle & handle)
{
  if (handle.m_ControlId.m_Type == ControlType::kKeyboard)
  {
    m_KeyboardState.RemoveControlBinding(handle);
    return;
  }
}

void InputState::HandleKeypressMessage(int scan_code, bool pressed)
{
  m_KeyboardState.HandleKeypressMessage(scan_code, pressed);
}

void InputState::SetBinaryControlInputCallback(const Delegate<void, const ControlId &> & callback)
{
  m_BinaryControlCallback = callback;
}

void InputState::ClearBinaryControlInputCallback()
{
  m_BinaryControlCallback.Clear();
}
