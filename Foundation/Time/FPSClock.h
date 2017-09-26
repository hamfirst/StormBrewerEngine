#pragma once

class FPSClock
{
public:
  FPSClock();

  void Update();
  int GetFrameCount();

private:
  double m_FrameStart;
  int m_FrameCount;
  int m_PrevFrameCount;
};
