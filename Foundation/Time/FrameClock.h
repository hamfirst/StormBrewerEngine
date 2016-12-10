#pragma once

class FrameClock
{
public:
  FrameClock(double frame_interval);
  
  void Start();
  bool ShouldSkipFrame();

  void WaitUntilNextFrame();
  void BeginFrame();
  
private:
  double m_FrameInterval;
  double m_LastFrame;
};
