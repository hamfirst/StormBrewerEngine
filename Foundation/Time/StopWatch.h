#pragma once

class StopWatch
{
public:
  StopWatch();
  StopWatch(const StopWatch & rhs) = default;
  StopWatch(StopWatch && rhs) = default;

  StopWatch & operator =(const StopWatch & rhs) = default;
  StopWatch & operator =(StopWatch && rhs) = default;

  void Start();

  double GetTimeSinceLastCheck();
  double GetTimeSinceStart();

  void SetTimeScale(double scale);
  double GetTimeScale(double scale);

private:
  double m_LastUpdate;
  double m_TimeScale;
  double m_StartTime;
};

