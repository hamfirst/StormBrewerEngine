
#include "Foundation/Common.h"
#include "Foundation/Time/StopWatch.h"

StopWatch::StopWatch() :
  m_LastUpdate(GetTimeSeconds()),
  m_TimeScale(1.0),
  m_StartTime(0)
{

}

void StopWatch::Start()
{
  m_LastUpdate = GetTimeSeconds();
  m_StartTime = m_LastUpdate;
}

double StopWatch::GetTimeSinceLastCheck()
{
  auto cur_time = GetTimeSeconds();

  auto diff_time = cur_time - m_LastUpdate;
  m_LastUpdate = cur_time;

  return diff_time * m_TimeScale;
}

double StopWatch::GetTimeSinceStart()
{
  auto cur_time = GetTimeSeconds();
  return cur_time - m_StartTime;
}

void StopWatch::SetTimeScale(double scale)
{
  m_TimeScale = scale;
}

double StopWatch::GetTimeScale(double scale)
{
  return m_TimeScale;
}
