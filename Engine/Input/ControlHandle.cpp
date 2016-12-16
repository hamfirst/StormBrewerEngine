
#include "Engine/EngineCommon.h"
#include "Engine/Input/ControlHandle.h"
#include "Engine/Input/InputState.h"


ControlHandle::ControlHandle() :
  m_InputState(nullptr), m_Control(kInvalidHandle), m_ControlId(ControlId{ ControlType::kInvalid, 0, 0 })
{

}

ControlHandle::ControlHandle(InputState * input_state, Handle handle, ControlId control_id) :
  m_InputState(input_state), m_Control(handle), m_ControlId(control_id)
{

}

void * ControlHandle::GetControlHandle() const
{
  if (m_ControlId.m_Type == ControlType::kKeyboard)
  {
    return m_InputState->m_KeyboardState.GetControlBinding(*this);
  }

  if (m_ControlId.m_Type == ControlType::kMouse)
  {
    return m_InputState->m_MouseState.GetButtonBinding(*this);
  }

  return nullptr;
}

