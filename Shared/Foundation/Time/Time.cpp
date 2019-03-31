
#include "Foundation/Common.h"
#include "Foundation/Time/Time.h"

#include <chrono>

static std::chrono::system_clock::time_point s_StartTime = std::chrono::system_clock::now();
static double s_TimePassed = 0;
static double s_LastUpdate = 0;
static double s_TimeScale = 1.0;

double GetTimeSeconds()
{
  auto cur_time = GetRawTimeSeconds();

  s_TimePassed += (cur_time - s_LastUpdate) * s_TimeScale;
  s_LastUpdate = cur_time;

  return s_TimePassed;
}

double GetRawTimeSeconds()
{
  auto now = std::chrono::system_clock::now();
  std::chrono::duration<double> since = (now - s_StartTime);

  return since.count();
}

void SetTimeScale(double scale)
{
  s_TimeScale = scale;
}

double GetTimeScale()
{
  return s_TimeScale;
}

int64_t GetRawTimeMilliseconds()
{
  auto now = std::chrono::system_clock::now();
  auto since = std::chrono::duration_cast<std::chrono::milliseconds>(now - s_StartTime);

  return since.count();
}

