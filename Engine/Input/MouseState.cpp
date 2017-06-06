
#include "Engine/EngineCommon.h"
#include "Engine/Input/MouseState.h"
#include "Engine/Input/InputState.h"

#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_events.h>


MouseState::MouseState(NotNullPtr<InputState> input_state) :
  m_InputState(input_state)
{

}

void MouseState::CheckDeltaState(const Box & window_geo, bool in_focus, bool query_state)
{
  int x, y;
  const uint32_t button_mask = SDL_GetGlobalMouseState(&x, &y);

  if (query_state)
  {
    bool in_window = PointInBox(window_geo, Vector2(x, y));

    x -= window_geo.m_Start.x;
    y -= window_geo.m_Start.y;

    if (SDL_GetRelativeMouseMode() == SDL_FALSE)
    {
      int height = window_geo.m_End.y - window_geo.m_Start.y;
      PointerState cur_state = { { x, height - y }, in_focus };

      m_PointerBinding.SetControlValue(cur_state);
      m_PointerState = cur_state;
    }

    for (int index = 1; index < kNumMouseButtons; index++)
    {
      bool pressed = ((1 << (index - 1)) & button_mask) != 0 && in_focus;

      m_ButtonControls[index].SetControlValue(pressed);

      if (m_PressedState[index] == 0 && pressed && in_window && in_focus)
      {
        if (m_InputState->m_BinaryControlCallback)
        {
          m_InputState->m_BinaryControlCallback(CreateMouseButtonBinding(index));
        }
      }

      m_PressedState[index] = pressed;
    }
  }
  else
  {
    bool in_window = in_focus;

    auto pointer_state = m_PointerState;
    if (pointer_state.m_InFocus != in_focus)
    {
      pointer_state.m_InFocus = in_focus;

      m_PointerBinding.SetControlValue(pointer_state);
      m_PointerState = pointer_state;
    }
  }
}

BinaryControlHandle MouseState::AddButtonBinding(int button, int priority, ControlBindingMode mode, const Delegate<void, bool> & callback)
{
  Handle handle = m_ButtonControls[button].CreateControlBinding(priority, mode, callback);
  return BinaryControlHandle(m_InputState, handle, CreateMouseButtonBinding(button));
}

void MouseState::RemoveButtonBinding(BinaryControlHandle handle)
{
  m_ButtonControls[handle.m_ControlId.m_Index].RemoveControlBinding(handle.m_Control);
}

PointerControlHandle MouseState::AddCursorBinding(int priority, ControlBindingMode mode, const Delegate<void, PointerState> & callback)
{
  Handle handle = m_PointerBinding.CreateControlBinding(priority, mode, callback);
  return PointerControlHandle(m_InputState, handle, CreateMousePointerBinding());
}

void MouseState::RemoveCursorBinding(PointerControlHandle handle)
{
  m_PointerBinding.RemoveControlBinding(handle.m_Control);
}

void MouseState::HandleButtonPressMessage(int button, bool pressed)
{
  m_ButtonControls[button].SetControlValue(pressed);

  if (m_PressedState[button] == 0 && pressed)
  {
    if (m_InputState->m_BinaryControlCallback)
    {
      m_InputState->m_BinaryControlCallback(CreateMouseButtonBinding(button));
    }
  }

  m_PressedState[button] = pressed;
}

void MouseState::HandleMouseMoveMessage(int x, int y, const Box & window_geo, bool in_focus)
{
  if (SDL_GetRelativeMouseMode() == SDL_TRUE)
  {
    int height = window_geo.m_End.y - window_geo.m_Start.y;

    PointerState cur_state = { { x, height - y }, in_focus };
    m_PointerBinding.SetControlValue(cur_state);
    m_PointerState = cur_state;
  }
  else
  {
    int height = window_geo.m_End.y - window_geo.m_Start.y;
    PointerState cur_state = { { x, height - y }, in_focus };
    m_PointerBinding.SetControlValue(cur_state);
    m_PointerState = cur_state;
  }

}

bool MouseState::GetButtonState(int button)
{
  if (button >= kNumMouseButtons)
  {
    return false;
  }

  return m_PressedState[button];
}

PointerState MouseState::GetPointerState()
{
  return m_PointerState;
}

NullOptPtr<void> MouseState::GetButtonBinding(const ControlHandle & handle)
{
  return m_ButtonControls[handle.m_ControlId.m_Index].GetControlBinding(handle.m_Control);
}

NullOptPtr<void> MouseState::GetPointerBinding(const ControlHandle & handle)
{
  return m_PointerBinding.GetControlBinding(handle.m_Control);
}

bool MouseState::GetCursorVisibility()
{
  return SDL_ShowCursor(SDL_QUERY) != 0;
}

void MouseState::SetCursorVisibility(bool visible)
{
  SDL_ShowCursor(visible);
}

void MouseState::LockMouseToWindow(bool enable)
{
  SDL_SetRelativeMouseMode(enable ? SDL_TRUE : SDL_FALSE);
}