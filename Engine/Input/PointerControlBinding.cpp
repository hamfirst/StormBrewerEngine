
#include "Engine/EngineCommon.h"
#include "Engine/Input/PointerControlBinding.h"

PointerControlBinding::PointerControlBinding(int priority, ControlBindingMode mode, const CallbackType & callback) :
  ControlBinding(priority, mode),
  m_StateChangeCB(callback)
{

}

void PointerControlBinding::UpdateState(PointerControlBinding::ControlValueType state)
{
  if (state.m_Pos.x != m_CurrentState.m_Pos.x ||
      state.m_Pos.y != m_CurrentState.m_Pos.y ||
      state.m_InFocus != m_CurrentState.m_InFocus)
  {
    m_CurrentState = state;
    m_History[m_HistoryIndex] = state;

    if (m_StateChangeCB)
    {
      m_StateChangeCB(state);
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

PointerControlBinding::ControlValueType PointerControlBinding::GetPriorValue(unsigned int frames_ago)
{
  if (frames_ago > m_HistoryCount || frames_ago > kPointerControlHistory)
  {
    return{};
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

PointerControlBinding::ControlValueType PointerControlHandle::GetPriorValue(unsigned int frames_ago)
{
  PointerControlBinding * binding = static_cast<PointerControlBinding *>(GetControlHandle());
  if (binding == nullptr)
  {
    return{};
  }

  return binding->GetPriorValue(frames_ago);
}
