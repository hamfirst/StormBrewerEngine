#pragma once

#include "Foundation/Delegate/Delegate.h"

#include "Engine/Input/ControlBinding.h"
#include "Engine/Input/ControlHandle.h"

static const unsigned int kBinaryControlHistory = 512;

class ENGINE_EXPORT BinaryControlBinding : public ControlBinding
{
public:
  using ControlValueType = bool;
  using CallbackType = Delegate<void, ControlValueType>;

  BinaryControlBinding(int priority, ControlBindingMode mode, const CallbackType & callback, bool force_callback);

  void UpdateState(ControlValueType state);
  ControlValueType GetCurrentState() const;
  void AdvanceFrame();

  bool WasOn(unsigned int history_frames) const;
  bool WasOff(unsigned int history_frames) const;

  ControlValueType GetPriorValue(unsigned int frames_ago) const;

private:

  CallbackType m_StateChangeCB;
  ControlValueType m_CurrentState = false;
  unsigned int m_HistoryCount = 0;
  unsigned int m_HistoryIndex = 0;
  ControlValueType m_History[kBinaryControlHistory] = {};
  bool m_ForceCallback = false;
};

class ENGINE_EXPORT BinaryControlHandle : public ControlHandle
{
protected:
  friend class InputState;
  friend class KeyboardState;
  friend class MouseState;
  friend class GamepadState;

  BinaryControlHandle(NotNullPtr<InputState> input_state, Handle handle, ControlId control_id);

public:
  BinaryControlHandle() = default;

  BinaryControlBinding::ControlValueType GetCurrentState() const;
  operator bool() const;

  bool WasOn(unsigned int history_frames) const;
  bool WasOff(unsigned int history_frames) const;

  BinaryControlBinding::ControlValueType GetPriorValue(unsigned int frames_ago) const;
};

