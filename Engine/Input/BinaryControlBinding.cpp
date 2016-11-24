
#include "Engine/EngineCommon.h"
#include "Engine/Input/BinaryControlBinding.h"

BinaryControlBinding::BinaryControlBinding(int priority, Delegate<void, bool> callback) :
  m_StateChangeCB(callback),
  m_Priority(priority)
{

}

void BinaryControlBinding::UpdateState(bool state)
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

bool BinaryControlBinding::GetCurrentState()
{
  return m_CurrentState;
}

void BinaryControlBinding::AdvanceFrame()
{
  m_HistoryIndex = (m_HistoryIndex + 1) % kBinaryControlHistory;
  m_History[m_HistoryIndex] = m_CurrentState;
  m_HistoryCount++;
}

bool BinaryControlBinding::WasOn(unsigned int history_frames)
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

bool BinaryControlBinding::WasOff(unsigned int history_frames)
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

bool BinaryControlBinding::GetPriorValue(unsigned int frames_ago)
{
  if (frames_ago > m_HistoryCount || frames_ago > kBinaryControlHistory)
  {
    return false;
  }

  int history_index = (m_HistoryIndex + kBinaryControlHistory - frames_ago) % kBinaryControlHistory;
  return m_History[history_index];
}
