#pragma once

class FrameClock
{
public:
  FrameClock(double frame_interval = 1.0/60.0);

  void Start();
  bool ShouldSkipFrameRender();
  bool ShouldSkipFrameUpdate();

  void WaitUntilNextFrame();
  void BeginFrame();

  double GetTimeUntilNextFrame();
  double GetFramePercent();

  int GetFrameCount();
  double GetFrameInterval();

private:
  double m_FrameInterval;
  double m_LastFrame;

  int m_FrameCount;
};
