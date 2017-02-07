
#include "Foundation/Common.h"
#include "Foundation/Time/FrameClock.h"

#include <thread>

FrameClock::FrameClock(double frame_interval)
{
  m_FrameInterval = frame_interval;
  m_LastFrame = 0;
  m_FrameCount = 0;
}

void FrameClock::Start()
{
  m_LastFrame = GetTimeSeconds();
}

bool FrameClock::ShouldSkipFrame()
{
  return GetTimeSeconds() - m_LastFrame > m_FrameInterval * 2;
}

bool FrameClock::ShouldStartFrame()
{
  return GetTimeSeconds() - m_LastFrame > m_FrameInterval / 2;
}

void FrameClock::WaitUntilNextFrame()
{
  double t = m_FrameInterval - (GetTimeSeconds() - m_LastFrame);
  if (t >= 0)
  {
    uint64_t micro_secs = (uint64_t)((t * 1000000) * GetTimeScale());
    std::this_thread::sleep_for(std::chrono::microseconds(micro_secs));
  }

  m_LastFrame += m_FrameInterval;
  m_FrameCount++;
}

void FrameClock::BeginFrame()
{
  m_LastFrame += m_FrameInterval;
  m_FrameCount++;
}

int FrameClock::GetFrameCount()
{
  return m_FrameCount;
}

double FrameClock::GetFrameInterval()
{
  return m_FrameInterval;
}