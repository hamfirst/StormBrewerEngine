
#include "Engine/EngineCommon.h"
#include "Engine/Input/ScalarControlBinding.h"

ScalarControlBinding::ScalarControlBinding(int priority, ControlBindingMode mode, const CallbackType & callback) :
  ControlBinding(priority, mode),
  m_StateChangeCB(callback)
{

}

void ScalarControlBinding::UpdateState(ScalarControlBinding::ControlValueType state)
{
  if (state != m_CurrentState)
  {
    m_CurrentState = state;
    m_History[m_HistoryIndex] = state;

    if (m_StateChangeCB)
    {
      m_StateChangeCB(state);
    }
  }
}

ScalarControlBinding::ControlValueType ScalarControlBinding::GetCurrentState()
{
  return m_CurrentState;
}

void ScalarControlBinding::AdvanceFrame()
{
  m_HistoryIndex = (m_HistoryIndex + 1) % kScalarControlHistory;
  m_History[m_HistoryIndex] = m_CurrentState;
  m_HistoryCount++;
}

ScalarControlBinding::ControlValueType ScalarControlBinding::GetPriorValue(unsigned int frames_ago)
{
  if (frames_ago > m_HistoryCount || frames_ago > kScalarControlHistory)
  {
    return{};
  }

  int history_index = (m_HistoryIndex + kScalarControlHistory - frames_ago) % kScalarControlHistory;
  return m_History[history_index];
}

ScalarControlHandle::ScalarControlHandle(NotNullPtr<InputState> input_state, Handle handle, ControlId control_id) :
  ControlHandle(input_state, handle, control_id)
{

}

ScalarControlBinding::ControlValueType ScalarControlHandle::GetCurrentState()
{
  ScalarControlBinding * binding = static_cast<ScalarControlBinding *>(GetControlHandle());
  if (binding == nullptr)
  {
    return{};
  }

  return binding->GetCurrentState();
}

ScalarControlBinding::ControlValueType ScalarControlHandle::GetPriorValue(unsigned int frames_ago)
{
  ScalarControlBinding * binding = static_cast<ScalarControlBinding *>(GetControlHandle());
  if (binding == nullptr)
  {
    return{};
  }

  return binding->GetPriorValue(frames_ago);
}
