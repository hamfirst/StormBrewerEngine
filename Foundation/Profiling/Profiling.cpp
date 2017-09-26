
#include "Foundation/Common.h"
#include "Foundation/Profiling/Profiling.h"

static std::vector<std::pair<czstr, double>> s_Measurements;

void ResetProfiler()
{
  s_Measurements.clear();
}

void AddProfilerMeasurement(czstr category, double time)
{
  s_Measurements.emplace_back(std::make_pair(category, time));
}

void VisitMeasurements(Delegate<void, czstr, double> & visitor)
{
  for (auto & elem : s_Measurements)
  {
    visitor(elem.first, elem.second);
  }
}

std::string GetProfilerText()
{
  std::string data;
  for (auto & elem : s_Measurements)
  {
    data += elem.first;
    data += ": ";
    data += std::to_string((int)(elem.second * 1000));
    data += "\n";
  }

  return data;
}