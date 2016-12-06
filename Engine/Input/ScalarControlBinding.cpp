
#include "Engine/EngineCommon.h"
#include "Engine/Input/ScalarControlBinding.h"

ScalarControlBinding::ScalarControlBinding(int priority, Delegate<void, float> callback) :
  m_StateChangeCB(callback),
  m_Priority(priority)
{

}

void ScalarControlBinding::UpdateState(float state)
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

float ScalarControlBinding::GetCurrentState()
{
  return m_CurrentState;
}

void ScalarControlBinding::AdvanceFrame()
{
  m_HistoryIndex = (m_HistoryIndex + 1) % kScalarControlHistory;
  m_History[m_HistoryIndex] = m_CurrentState;
  m_HistoryCount++;
}

bool ScalarControlBinding::WasOn(unsigned int history_frames)
{
  history_frames = std::min({ history_frames, m_HistoryCount, kScalarControlHistory });
  int history_index = (m_HistoryIndex + kScalarControlHistory - history_frames) % kScalarControlHistory;

  while (history_frames > 0)
  {
    if (m_History[history_index] > kScalarControlThreshold)
    {
      return true;
    }

    history_frames--;
    history_index = (history_index + 1) % kScalarControlHistory;
  }

  return GetCurrentState() > kScalarControlThreshold;
}

bool ScalarControlBinding::WasOff(unsigned int history_frames)
{
  history_frames = std::min({ history_frames, m_HistoryCount, kScalarControlHistory });
  int history_index = (m_HistoryIndex + kScalarControlHistory - history_frames) % kScalarControlHistory;

  while (history_frames > 0)
  {
    if (m_History[history_index] <= kScalarControlThreshold)
    {
      return true;
    }

    history_frames--;
    history_index = (history_index + 1) % kScalarControlHistory;
  }

  return GetCurrentState() <= kScalarControlThreshold;
}

float ScalarControlBinding::GetPriorValue(unsigned int frames_ago)
{
  if (frames_ago > m_HistoryCount || frames_ago > kScalarControlHistory)
  {
    return 0;
  }

  int history_index = (m_HistoryIndex + kScalarControlHistory - frames_ago) % kScalarControlHistory;
  return m_History[history_index];
}
