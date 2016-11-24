#pragma once

#include "Foundation/Common.h"
#include "Foundation/Delegate/Delegate.h"

static const unsigned int kScalarControlHistory = 512;
static const float kScalarControlThreshold = 0.75;

class VectorControlBinding
{
  VectorControlBinding(int priority, Delegate<void, RenderVec2> callback);

  void UpdateState(RenderVec2 state);
  RenderVec2 GetCurrentState();
  void AdvanceFrame();

  RenderVec2 GetPriorValue(unsigned int frames_ago);

  int GetPriority() { return m_Priority; }

private:

  Delegate<void, RenderVec2> m_StateChangeCB;
  RenderVec2 m_CurrentState = {};
  int m_Priority;
  unsigned int m_HistoryCount = 0;
  unsigned int m_HistoryIndex = 0;
  RenderVec2 m_History[kScalarControlHistory] = {};
};
