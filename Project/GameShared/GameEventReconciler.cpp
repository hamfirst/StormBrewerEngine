#include "GameShared/GameSharedCommon.h"
#include "GameShared/GameEventReconciler.h"

#include "Foundation/Math/Util.h"

GameEventReconciler::GameEventReconciler(int max_dist, int max_time) :
  m_MaxDist(max_dist),
  m_MaxTime(max_time)
{

}

bool GameEventReconciler::PushEvent(std::size_t event_type, uint64_t event_id, const Vector2 & position, int frames_past)
{
  int start_frame = frames_past - m_MaxTime;
  if (start_frame < 0)
  {
    start_frame = 0;
  }

  int end_frame = frames_past + m_MaxTime;
  if (end_frame >= kMaxHistoryFrames)
  {
    end_frame = kMaxHistoryFrames - 1;
  }

  for (int frame = start_frame; frame < end_frame; frame++)
  {
    auto history = m_HistoryEvents.Get(frame);
    if (history == nullptr)
    {
      continue;
    }

    for (auto & ev : *history)
    {
      if (ev.m_EventType == event_type && ev.m_EventId == event_id && ManhattanDist(position, ev.m_Position) <= m_MaxDist)
      {
        return false;
      }
    }
  }

  auto event_list = m_HistoryEvents.Get(frames_past);
  if (event_list != nullptr)
  {
    event_list->push_back(EventInfo{ event_type, event_id, position });
  }

  return true;
}

void GameEventReconciler::AdvanceFrame()
{
  m_HistoryEvents.Push(std::vector<EventInfo>{});
}

