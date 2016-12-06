
#include "Engine/EngineCommon.h"
#include "Engine/Time/Time.h"

#include <SDL/SDL_timer.h>

TimeManager g_TimeManager;

void TimeManager::Update()
{
  m_FrameCount++;
  m_Time = SDL_GetTicks() / 1000.0;
}

int TimeManager::GetFrameCount()
{
  return m_FrameCount;
}

double TimeManager::GetTime()
{
  return m_Time;
}

float TimeManager::GetTimef()
{
  return (float)m_Time;
}
