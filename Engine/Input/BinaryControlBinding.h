#pragma once

#include "Foundation/Delegate/Delegate.h"

static const unsigned int kBinaryControlHistory = 512;

class BinaryControlBinding
{
  BinaryControlBinding(int priority, Delegate<void, bool> callback);

  void UpdateState(bool state);
  bool GetCurrentState();
  void AdvanceFrame();

  bool WasOn(unsigned int history_frames);
  bool WasOff(unsigned int history_frames);

  bool GetPriorValue(unsigned int frames_ago);

  int GetPriority() { return m_Priority; }

private:

  Delegate<void, bool> m_StateChangeCB;
  bool m_CurrentState = false;
  int m_Priority;
  unsigned int m_HistoryCount = 0;
  unsigned int m_HistoryIndex = 0;
  bool m_History[kBinaryControlHistory] = {};
};
