
#include "Engine/EngineCommon.h"
#include "Engine/Input/PointerControlBinding.h"

PointerControlBinding::PointerControlBinding(int priority, ControlBindingMode mode, const CallbackType & callback) :
  ControlBinding(priority, mode),
  m_StateChangeCB(callback)
{

}

void PointerControlBinding::UpdateState(PointerControlBinding::ControlValueType state)
{
  if (state != m_CurrentState)
  {
    m_CurrentState = state;
    m_History[m_HistoryIndex] = state;

    if (m_StateChangeCB)
    {
      m_StateChangeCB.Call(state);
    }
  }
}

PointerControlBinding::ControlValueType PointerControlBinding::GetCurrentState()
{
  return m_CurrentState;
}

void PointerControlBinding::AdvanceFrame()
{
  m_HistoryIndex = (m_HistoryIndex + 1) % kPointerControlHistory;
  m_History[m_HistoryIndex] = m_CurrentState;
  m_HistoryCount++;
}

bool PointerControlBinding::WasOn(unsigned int history_frames)
{
  history_frames = std::min({ history_frames, m_HistoryCount, kPointerControlHistory });
  int history_index = (m_HistoryIndex + kPointerControlHistory - history_frames) % kPointerControlHistory;

  while (history_frames > 0)
  {
    if (m_History[history_index])
    {
      return true;
    }

    history_frames--;
    history_index = (history_index + 1) % kPointerControlHistory;
  }

  return GetCurrentState();
}

bool PointerControlBinding::WasOff(unsigned int history_frames)
{
  history_frames = std::min({ history_frames, m_HistoryCount, kPointerControlHistory });
  int history_index = (m_HistoryIndex + kPointerControlHistory - history_frames) % kPointerControlHistory;

  while (history_frames > 0)
  {
    if (!m_History[history_index])
    {
      return true;
    }

    history_frames--;
    history_index = (history_index + 1) % kPointerControlHistory;
  }

  return GetCurrentState();
}

PointerControlBinding::ControlValueType PointerControlBinding::GetPriorValue(unsigned int frames_ago)
{
  if (frames_ago > m_HistoryCount || frames_ago > kPointerControlHistory)
  {
    return false;
  }

  int history_index = (m_HistoryIndex + kPointerControlHistory - frames_ago) % kPointerControlHistory;
  return m_History[history_index];
}

PointerControlHandle::PointerControlHandle(NotNullPtr<InputState> input_state, Handle handle, ControlId control_id) :
  ControlHandle(input_state, handle, control_id)
{

}

PointerControlBinding::ControlValueType PointerControlHandle::GetCurrentState()
{
  PointerControlBinding * binding = static_cast<PointerControlBinding *>(GetControlHandle());
  if (binding == nullptr)
  {
    return{};
  }

  return binding->GetCurrentState();
}

bool PointerControlHandle::WasOn(unsigned int history_frames)
{
  PointerControlBinding * binding = static_cast<PointerControlBinding *>(GetControlHandle());
  if (binding == nullptr)
  {
    return{};
  }

  return binding->WasOn(history_frames);
}

bool PointerControlHandle::WasOff(unsigned int history_frames)
{
  PointerControlBinding * binding = static_cast<PointerControlBinding *>(GetControlHandle());
  if (binding == nullptr)
  {
    return{};
  }

  return binding->WasOff(history_frames);
}

PointerControlBinding::ControlValueType PointerControlHandle::GetPriorValue(unsigned int frames_ago)
{
  PointerControlBinding * binding = static_cast<PointerControlBinding *>(GetControlHandle());
  if (binding == nullptr)
  {
    return{};
  }

  return binding->GetPriorValue(frames_ago);
}
