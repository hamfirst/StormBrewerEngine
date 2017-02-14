#pragma once

class StopWatch
{
public:
  StopWatch();

  void Start();

  double GetTimeSinceLastCheck();

  void SetTimeScale(double scale);
  double GetTimeScale(double scale);

private:
  double m_LastUpdate;
  double m_TimeScale;
};

