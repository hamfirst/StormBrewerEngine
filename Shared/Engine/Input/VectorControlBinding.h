#pragma once

#include "Foundation/Common.h"
#include "Foundation/Delegate/Delegate.h"

static const unsigned int kScalarControlHistory = 512;
static const float kScalarControlThreshold = 0.75;

class ENGINE_EXPORT VectorControlBinding
{
public:

  using CallbackType = Delegate<void, RenderVec2>;

  VectorControlBinding(int priority, Delegate<void, RenderVec3> callback);

  void UpdateState(RenderVec2 state);
  RenderVec3 GetCurrentState();
  void AdvanceFrame();

  RenderVec3 GetPriorValue(unsigned int frames_ago);

  int GetPriority() { return m_Priority; }

private:

  Delegate<void, RenderVec3> m_StateChangeCB;
  RenderVec3 m_CurrentState = {};
  int m_Priority;
  unsigned int m_HistoryCount = 0;
  unsigned int m_HistoryIndex = 0;
  RenderVec3 m_History[kScalarControlHistory] = {};
};
