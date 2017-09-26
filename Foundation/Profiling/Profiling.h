#pragma once

#include "Foundation/Common.h"
#include "Foundation/Delegate/Delegate.h"
#include "Foundation/Time/Time.h"

void ResetProfiler();
void AddProfilerMeasurement(czstr category, double time);
void VisitMeasurements(Delegate<void, czstr, double> & visitor);
std::string GetProfilerText();

class ProfileScope
{
public:
  ProfileScope(czstr category)
  {
    m_Start = GetTimeSeconds();
    m_Category = category;
  }

  ~ProfileScope()
  {
    AddProfilerMeasurement(m_Category, GetTimeSeconds() - m_Start);
  }

private:
  czstr m_Category;
  double m_Start;
};

#define PROFILE_SCOPE(Category) ProfileScope __m_profiler(Category);
