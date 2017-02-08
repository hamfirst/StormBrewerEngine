#pragma once

class FrameClock
{
public:
  FrameClock(double frame_interval);
  
  void Start();
  bool ShouldSkipFrame();
  bool ShouldStartFrame();

  void WaitUntilNextFrame();
  void BeginFrame();

  double GetTimeUntilNextFrame();

  int GetFrameCount();
  double GetFrameInterval();
  
private:
  double m_FrameInterval;
  double m_LastFrame;

  int m_FrameCount;
};
