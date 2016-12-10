
#include "Foundation/Common.h"
#include "Foundation/Time/Time.h"

#include <chrono>

std::chrono::system_clock::time_point s_StartTime = std::chrono::system_clock::now();

double GetTimeSeconds()
{
  auto now = std::chrono::system_clock::now();
  std::chrono::duration<double> since = (now - s_StartTime);

  return since.count();
}
