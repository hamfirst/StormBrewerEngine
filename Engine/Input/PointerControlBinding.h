#pragma once

#include "Foundation/Delegate/Delegate.h"

#include "Engine/Input/ControlBinding.h"
#include "Engine/Input/ControlHandle.h"

static const unsigned int kPointerControlHistory = 512;

class PointerControlBinding : public ControlBinding
{
public:
  using ControlValueType = bool;
  using CallbackType = Delegate<void, ControlValueType>;

  PointerControlBinding(int priority, ControlBindingMode mode, const CallbackType & callback);

  void UpdateState(ControlValueType state);
  ControlValueType GetCurrentState();
  void AdvanceFrame();

  bool WasOn(unsigned int history_frames);
  bool WasOff(unsigned int history_frames);

  ControlValueType GetPriorValue(unsigned int frames_ago);

private:

  CallbackType m_StateChangeCB;
  ControlValueType m_CurrentState = false;
  unsigned int m_HistoryCount = 0;
  unsigned int m_HistoryIndex = 0;
  ControlValueType m_History[kPointerControlHistory] = {};
};

class PointerControlHandle : public ControlHandle
{
protected:
  friend class InputState;
  friend class KeyboardState;

  PointerControlHandle(NotNullPtr<InputState> input_state, Handle handle, ControlId control_id);

public:
  PointerControlHandle() = default;

  PointerControlBinding::ControlValueType GetCurrentState();

  bool WasOn(unsigned int history_frames);
  bool WasOff(unsigned int history_frames);

  PointerControlBinding::ControlValueType GetPriorValue(unsigned int frames_ago);
};

