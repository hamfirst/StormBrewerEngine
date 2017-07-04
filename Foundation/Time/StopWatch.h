#pragma once

class StopWatch
{
public:
  StopWatch();

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

