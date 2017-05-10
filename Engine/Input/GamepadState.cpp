
#include "Engine/EngineCommon.h"
#include "Engine/Input/GamepadState.h"
#include "Engine/Input/InputState.h"

#include <SDL2/SDL_gamecontroller.h>

void * GamepadState::m_OpenGamePads[kMaxGamepads] = {};

GamepadState::GamepadState(NotNullPtr<InputState> input_state) :
  m_InputState(input_state)
{
}

void GamepadState::Init()
{
  //for (int index = 0, end = std::min(SDL_NumJoysticks(), kMaxGamepads); index < end; index++)
  //{
  //  m_OpenGamePads[index] = SDL_GameControllerOpen(index);
  //}
}

void GamepadState::Cleanup()
{
  for (int index = 0; index < kMaxGamepads; ++index)
  {
    if (m_OpenGamePads[index] != nullptr)
    {
      SDL_GameControllerClose((SDL_GameController *)m_OpenGamePads[index]);
      return;
    }
  }
}

void GamepadState::CheckDeltaState(bool in_focus)
{
  for (int index = 0; index < kMaxGamepads; ++index)
  {
    if (m_OpenGamePads[index] != nullptr && m_ConnectedState[index] == true)
    {
      m_ConnectedState[index] = false;
      m_ControllerConnected[index].SetControlValue(false);
    }
    else
    {
      m_ConnectedState[index] = true;
      m_ControllerConnected[index].SetControlValue(true);
    }
    
    if (m_OpenGamePads[index] == nullptr)
    {
      for (int button = 0; button < (int)GamepadButton::kCount; ++button)
      {
        m_PressedThisFrame[index][button] = false;
        if (m_PressedState[index][button])
        {
          m_PressedState[index][button] = false;
          m_ButtonControls[index][button].SetControlValue(false);
        }
      }

      for (int axis = 0; axis < (int)GamepadAxis::kCount; ++axis)
      {
        m_AxisValue[index][axis] = 0;
        m_AxisControls[index][axis].SetControlValue((float)0);
      }
    }
    else
    {
      for (int button = 0; button < SDL_CONTROLLER_BUTTON_MAX; ++button)
      {
        auto pressed = SDL_GameControllerGetButton((SDL_GameController *)m_OpenGamePads[index], (SDL_GameControllerButton)button);

        if (pressed && m_PressedState[index][button] == false)
        {
          m_PressedState[index][button] = true;
          m_PressedThisFrame[index][button] = true;
          m_ButtonControls[index][button].SetControlValue(true);
        }
        else
        {
          m_PressedThisFrame[index][button] = false;
          if (pressed == false && m_PressedState[index][button])
          {
            m_PressedState[index][button] = false;
            m_ButtonControls[index][button].SetControlValue(false);
          }
        }
      }

      for (int axis = 0; axis < SDL_CONTROLLER_AXIS_MAX; ++axis)
      {
        auto value = SDL_GameControllerGetAxis((SDL_GameController *)m_OpenGamePads[index], (SDL_GameControllerAxis)axis);
        float f_val = (float)value / 32768.0f;

        if (axis < (int)GamepadAxis::kCount)
        {
          m_AxisValue[index][axis] = f_val;
          m_AxisControls[index][axis].SetControlValue(f_val);
        }
        else
        {
          bool pressed = f_val > 0.3f;
          int button = (axis - SDL_CONTROLLER_AXIS_TRIGGERLEFT) + (int)GamepadButton::kL1;

          if (pressed && m_PressedState[index][button] == false)
          {
            m_PressedState[index][button] = true;
            m_PressedThisFrame[index][button] = true;
            m_ButtonControls[index][button].SetControlValue(true);
          }
          else
          {
            m_PressedThisFrame[index][button] = false;
            if (pressed == false && m_PressedState[index][button])
            {
              m_PressedState[index][button] = false;
              m_ButtonControls[index][button].SetControlValue(false);
            }
          }
        }
      }
    }
  }
}

void GamepadState::GamepadConnected(int joystick_idx)
{
  for (int index = 0; index < kMaxGamepads; ++index)
  {
    if (m_OpenGamePads[index] == nullptr)
    {
      m_OpenGamePads[index] = SDL_GameControllerOpen(index);
      return;
    }
  }
}

void GamepadState::GamepadDisonnected(int joystick_id)
{
  for (int index = 0; index < kMaxGamepads; ++index)
  {
    if (m_OpenGamePads[index] != nullptr && SDL_JoystickInstanceID((SDL_Joystick *)m_OpenGamePads[index]) == joystick_id)
    {
      SDL_GameControllerClose((SDL_GameController *)m_OpenGamePads[index]);
      m_OpenGamePads[index] = nullptr;
      return;
    }
  }
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

bool GamepadState::IsGamepadConnected(int gamepad_idx)
{
  return m_ConnectedState[gamepad_idx];
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

bool GamepadState::IsButtonPressed(int gamepad_idx, GamepadButton button)
{
  return m_PressedState[gamepad_idx][(int)button];
}

bool GamepadState::IsButtonPressedThisFrame(int gamepad_idx, GamepadButton button)
{
  return m_PressedThisFrame[gamepad_idx][(int)button];
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

float GamepadState::GetAxis(int gamepad_idx, GamepadAxis axis)
{
  return m_AxisValue[gamepad_idx][(int)axis];
}