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

  int GetFrameCount();
  
private:
  double m_FrameInterval;
  double m_LastFrame;

  int m_FrameCount;
};
