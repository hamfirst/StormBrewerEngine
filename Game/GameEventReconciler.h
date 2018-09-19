#pragma once

#include "Foundation/Common.h"
#include "Foundation/CircularBuffer/CircularBuffer.h"

class GameEventReconciler
{
public:
  explicit GameEventReconciler(int max_dist = 5, int max_time = 3);

  bool PushEvent(std::size_t event_type, uint64_t event_id, const Vector2 & position, int frames_past);
  void AdvanceFrame();
private:

  struct EventInfo
  {
    std::size_t m_EventType;
    uint64_t m_EventId;
    Vector2 m_Position;
  };

  static const int kMaxHistoryFrames = 128;
  CircularBuffer<std::vector<EventInfo>, kMaxHistoryFrames> m_HistoryEvents;

  int m_MaxDist;
  int m_MaxTime;
};

