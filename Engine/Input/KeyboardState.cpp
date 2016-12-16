
#include "Engine/EngineCommon.h"
#include "Engine/Input/KeyboardState.h"
#include "Engine/Input/InputState.h"

#include <SDL/SDL_keyboard.h>


KeyboardState::KeyboardState(NotNullPtr<InputState> input_state) :
  m_InputState(input_state)
{

}

void KeyboardState::CheckDeltaState(bool in_focus)
{
  int num_keys = 0;
  const uint8_t * keys = SDL_GetKeyboardState(&num_keys);

  for (int index = 0; index < num_keys; index++)
  {
    bool pressed = keys[index] && in_focus;

    m_KeyboardControls[index].SetControlValue(pressed);

    if (m_PressedState[index] == 0 && pressed)
    {
      if (m_InputState->m_BinaryControlCallback)
      {
        m_InputState->m_BinaryControlCallback(CreateKeyboardBinding(index));
      }
    }

    m_PressedState[index] = pressed;
  }
}

BinaryControlHandle KeyboardState::AddKeyBinding(int scan_code, int priority, ControlBindingMode mode, const Delegate<void, bool> & callback)
{
  Handle handle = m_KeyboardControls[scan_code].CreateControlBinding(priority, mode, callback);
  return BinaryControlHandle(m_InputState, handle, CreateKeyboardBinding(scan_code));
}

void KeyboardState::RemoveKeyBinding(BinaryControlHandle handle)
{
  m_KeyboardControls[handle.m_ControlId.m_Index].RemoveControlBinding(handle.m_Control);
}

bool KeyboardState::GetKeyState(int scan_code)
{
  if (scan_code >= kNumKeyboardKeys)
  {
    return false;
  }

  return m_PressedState[scan_code];
}

void KeyboardState::HandleKeyPressMessage(int scan_code, bool pressed)
{
  m_KeyboardControls[scan_code].SetControlValue(pressed);

  if (m_PressedState[scan_code] == 0 && pressed)
  {
    if (m_InputState->m_BinaryControlCallback)
    {
      m_InputState->m_BinaryControlCallback(CreateKeyboardBinding(scan_code));
    }
  }

  m_PressedState[scan_code] = pressed;
}

czstr KeyboardState::GetKeyNameForScanCode(int scan_code)
{
  const char * key_name = SDL_GetKeyName(SDL_GetKeyFromScancode((SDL_Scancode)scan_code));
  return key_name;
}

NullOptPtr<void> KeyboardState::GetControlBinding(const ControlHandle & handle)
{
  return m_KeyboardControls[handle.m_ControlId.m_Index].GetControlBinding(handle.m_Control);
}
