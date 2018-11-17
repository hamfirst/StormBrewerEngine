
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

bool FrameClock::ShouldSkipFrameRender()
{
  return GetTimeSeconds() - m_LastFrame > m_FrameInterval;
}

bool FrameClock::ShouldSkipFrameUpdate()
{
  return GetTimeSeconds() - m_LastFrame < m_FrameInterval * 1.2f;
}

void FrameClock::WaitUntilNextFrame()
{
  double t = GetTimeUntilNextFrame();
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

void FrameClock::RemoveExtra()
{
  while (ShouldSkipFrameUpdate() == false)
  {
    m_LastFrame += m_FrameInterval;
  }
}

double FrameClock::GetTimeUntilNextFrame()
{
  double cur_time = GetTimeSeconds();
  double t = m_LastFrame + m_FrameInterval - cur_time;
  return t;
}

double FrameClock::GetFramePercent()
{
  return std::max(std::min(1.0 - GetTimeUntilNextFrame() / m_FrameInterval, 1.0), 0.0);
}

int FrameClock::GetFrameCount()
{
  return m_FrameCount;
}

double FrameClock::GetFrameInterval()
{
  return m_FrameInterval;
}