
#include "Engine/EngineCommon.h"
#include "Engine/Input/VectorControlBinding.h"

VectorControlBinding::VectorControlBinding(int priority, Delegate<void, RenderVec2> callback) :
  m_StateChangeCB(callback),
  m_Priority(priority)
{

}

void VectorControlBinding::UpdateState(RenderVec2 state)
{
  m_CurrentState = state;
  m_History[m_HistoryIndex] = state;

  if (m_StateChangeCB)
  {
    m_StateChangeCB.Call(state);
  }
}

RenderVec2 VectorControlBinding::GetCurrentState()
{
  return m_CurrentState;
}

void VectorControlBinding::AdvanceFrame()
{
  m_HistoryIndex = (m_HistoryIndex + 1) % kScalarControlHistory;
  m_History[m_HistoryIndex] = m_CurrentState;
  m_HistoryCount++;
}

RenderVec2 VectorControlBinding::GetPriorValue(unsigned int frames_ago)
{
  if (frames_ago > m_HistoryCount || frames_ago > kScalarControlHistory)
  {
    return{};
  }

  int history_index = (m_HistoryIndex + kScalarControlHistory - frames_ago) % kScalarControlHistory;
  return m_History[history_index];
}
