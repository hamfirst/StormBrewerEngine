#pragma once

#include "Foundation/Delegate/Delegate.h"

static const unsigned int kScalarControlHistory = 512;
static const float kScalarControlThreshold = 0.75;

class ScalarControlBinding
{
public:

  using CallbackType = Delegate<void, float>;

  ScalarControlBinding(int priority, Delegate<void, float> callback);

  void UpdateState(float state);
  float GetCurrentState();
  void AdvanceFrame();

  bool WasOn(unsigned int history_frames);
  bool WasOff(unsigned int history_frames);

  float GetPriorValue(unsigned int frames_ago);

  int GetPriority() { return m_Priority; }

private:

  Delegate<void, float> m_StateChangeCB;
  float m_CurrentState = 0;
  int m_Priority;
  unsigned int m_HistoryCount = 0;
  unsigned int m_HistoryIndex = 0;
  float m_History[kScalarControlHistory] = {};
};
