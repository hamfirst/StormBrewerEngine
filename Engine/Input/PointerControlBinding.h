#pragma once

#include "Foundation/Delegate/Delegate.h"

#include "Engine/Input/ControlBinding.h"
#include "Engine/Input/ControlHandle.h"

static const unsigned int kPointerControlHistory = 512;

struct PointerState
{
  Vector2 m_Pos;
  bool m_InFocus;
};

class PointerControlBinding : public ControlBinding
{
public:
  using ControlValueType = PointerState;
  using CallbackType = Delegate<void, ControlValueType>;

  PointerControlBinding(int priority, ControlBindingMode mode, const CallbackType & callback);

  void UpdateState(ControlValueType state);
  ControlValueType GetCurrentState();
  void AdvanceFrame();

  ControlValueType GetPriorValue(unsigned int frames_ago);

private:

  CallbackType m_StateChangeCB;
  ControlValueType m_CurrentState = {};
  unsigned int m_HistoryCount = 0;
  unsigned int m_HistoryIndex = 0;
  ControlValueType m_History[kPointerControlHistory] = {};
};

class PointerControlHandle : public ControlHandle
{
protected:
  friend class InputState;
  friend class MouseState;

  PointerControlHandle(NotNullPtr<InputState> input_state, Handle handle, ControlId control_id);

public:
  PointerControlHandle() = default;

  PointerControlBinding::ControlValueType GetCurrentState();
  PointerControlBinding::ControlValueType GetPriorValue(unsigned int frames_ago);
};

