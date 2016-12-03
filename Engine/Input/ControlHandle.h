#pragma once

#include "Foundation/Handle/Handle.h"

#include "ControlId.h"

class InputState;

class ControlHandle
{
protected:
  ControlHandle();
  ControlHandle(NotNullPtr<InputState> input_state, Handle handle, ControlId control_id);

  void * GetControlHandle();

protected:
  friend class KeyboardState;

  InputState * m_InputState;
  Handle m_Control;
  ControlId m_ControlId;
};

