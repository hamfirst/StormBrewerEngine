#pragma once

#include "Foundation/Delegate/Delegate.h"

#include "Engine/Input/ControlBinding.h"
#include "Engine/Input/ControlHandle.h"

static const unsigned int kScalarControlHistory = 512;

class ENGINE_EXPORT ScalarControlBinding : public ControlBinding
{
public:
  using ControlValueType = float;
  using CallbackType = Delegate<void, ControlValueType>;

  ScalarControlBinding(int priority, ControlBindingMode mode, const CallbackType & callback);

  void UpdateState(ControlValueType state);
  ControlValueType GetCurrentState();
  void AdvanceFrame();

  ControlValueType GetPriorValue(unsigned int frames_ago);

private:

  CallbackType m_StateChangeCB;
  ControlValueType m_CurrentState = {};
  unsigned int m_HistoryCount = 0;
  unsigned int m_HistoryIndex = 0;
  ControlValueType m_History[kScalarControlHistory] = {};
};

class ENGINE_EXPORT ScalarControlHandle : public ControlHandle
{
protected:
  friend class InputState;
  friend class MouseState;
  friend class GamepadState;

  ScalarControlHandle(NotNullPtr<InputState> input_state, Handle handle, ControlId control_id);

public:
  ScalarControlHandle() = default;

  ScalarControlBinding::ControlValueType GetCurrentState();
  ScalarControlBinding::ControlValueType GetPriorValue(unsigned int frames_ago);
};

