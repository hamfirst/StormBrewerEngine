
#include "Foundation/Common.h"
#include "Foundation/Time/FPSClock.h"

FPSClock::FPSClock() :
  m_FrameStart(GetTimeSeconds()),
  m_FrameCount(0),
  m_PrevFrameCount(0)
{

}

void FPSClock::Update()
{
  auto cur_time = GetTimeSeconds();
  if (cur_time - m_FrameStart > 1.0f)
  {
    m_PrevFrameCount = m_FrameCount;
    m_FrameCount = 0;

    m_FrameStart += 1.0f;
  }

  m_FrameCount++;
}

int FPSClock::GetFrameCount()
{
  return m_PrevFrameCount;
}
