#pragma once

#include <chrono>

class TimeManager
{
public:

  void Update();

  int GetFrameCount();
  double GetTime();

  float GetTimef();

private:
  int m_FrameCount = 0;
  double m_Time = 0;
};

extern TimeManager g_TimeManager;
