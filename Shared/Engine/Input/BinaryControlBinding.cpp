
#include "Engine/EngineCommon.h"
#include "Engine/Input/BinaryControlBinding.h"

BinaryControlBinding::BinaryControlBinding(int priority, ControlBindingMode mode, const CallbackType & callback, bool force_callback) :
  ControlBinding(priority, mode),
  m_StateChangeCB(callback),
  m_ForceCallback(force_callback)
{

}

void BinaryControlBinding::UpdateState(BinaryControlBinding::ControlValueType state)
{
  if (state != m_CurrentState || m_ForceCallback)
  {
    m_CurrentState = state;
    m_History[m_HistoryIndex] = state;

    if (m_StateChangeCB)
    {
      m_StateChangeCB(state);
    }
  }
}

BinaryControlBinding::ControlValueType BinaryControlBinding::GetCurrentState() const
{
  return m_CurrentState;
}

void BinaryControlBinding::AdvanceFrame()
{
  m_HistoryIndex = (m_HistoryIndex + 1) % kBinaryControlHistory;
  m_History[m_HistoryIndex] = m_CurrentState;
  m_HistoryCount++;
}

bool BinaryControlBinding::WasOn(unsigned int history_frames) const
{
  history_frames = std::min({ history_frames, m_HistoryCount, kBinaryControlHistory });
  int history_index = (m_HistoryIndex + kBinaryControlHistory - history_frames) % kBinaryControlHistory;

  while (history_frames > 0)
  {
    if (m_History[history_index])
    {
      return true;
    }

    history_frames--;
    history_index = (history_index + 1) % kBinaryControlHistory;
  }

  return GetCurrentState();
}

bool BinaryControlBinding::WasOff(unsigned int history_frames) const
{
  history_frames = std::min({ history_frames, m_HistoryCount, kBinaryControlHistory });
  int history_index = (m_HistoryIndex + kBinaryControlHistory - history_frames) % kBinaryControlHistory;

  while (history_frames > 0)
  {
    if (!m_History[history_index])
    {
      return true;
    }

    history_frames--;
    history_index = (history_index + 1) % kBinaryControlHistory;
  }

  return GetCurrentState();
}

BinaryControlBinding::ControlValueType BinaryControlBinding::GetPriorValue(unsigned int frames_ago) const
{
  if (frames_ago > m_HistoryCount || frames_ago > kBinaryControlHistory)
  {
    return false;
  }

  int history_index = (m_HistoryIndex + kBinaryControlHistory - frames_ago) % kBinaryControlHistory;
  return m_History[history_index];
}

BinaryControlHandle::BinaryControlHandle(NotNullPtr<InputState> input_state, Handle handle, ControlId control_id) :
  ControlHandle(input_state, handle, control_id)
{

}

BinaryControlBinding::ControlValueType BinaryControlHandle::GetCurrentState() const
{
  BinaryControlBinding * binding = static_cast<BinaryControlBinding *>(GetControlHandle());
  if (binding == nullptr)
  {
    return{};
  }

  return binding->GetCurrentState();
}

BinaryControlHandle::operator bool() const
{
  return GetCurrentState();
}

bool BinaryControlHandle::WasOn(unsigned int history_frames) const
{
  BinaryControlBinding * binding = static_cast<BinaryControlBinding *>(GetControlHandle());
  if (binding == nullptr)
  {
    return{};
  }

  return binding->WasOn(history_frames);
}

bool BinaryControlHandle::WasOff(unsigned int history_frames) const
{
  BinaryControlBinding * binding = static_cast<BinaryControlBinding *>(GetControlHandle());
  if (binding == nullptr)
  {
    return{};
  }

  return binding->WasOff(history_frames);
}

BinaryControlBinding::ControlValueType BinaryControlHandle::GetPriorValue(unsigned int frames_ago) const
{
  BinaryControlBinding * binding = static_cast<BinaryControlBinding *>(GetControlHandle());
  if (binding == nullptr)
  {
    return{};
  }

  return binding->GetPriorValue(frames_ago);
}
