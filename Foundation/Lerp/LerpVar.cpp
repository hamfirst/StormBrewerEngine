
#include "Foundation/Common.h"
#include "Foundation/Lerp/LerpVar.h"


LerpVar::LerpVar() : 
  m_StartTimer(0),
  m_MaxTime(0),
  m_Start(0),
  m_Target(0)
{

}

LerpVar::LerpVar(float initial_val) :
  m_StartTimer(0),
  m_MaxTime(0),
  m_Start(initial_val),
  m_Target(initial_val)
{

}

LerpVar::operator float() const
{
  return Get();
}

float LerpVar::Get() const
{
  auto time_since = (float)GetTimeSeconds() - m_StartTimer;
  if (time_since > m_MaxTime)
  {
    return m_Target;
  }

  auto v = time_since / m_MaxTime;
  return (v * m_Target) + (1.0f - v) * m_Start;
}

float LerpVar::GetTarget() const
{
  return m_Target;
}

void LerpVar::LerpTo(float val, float time)
{
  m_Start = Get();

  m_StartTimer = (float)GetTimeSeconds();
  m_MaxTime = time;
  m_Target = val;
}

void LerpVar::Set(float val)
{
  m_StartTimer = 0;
  m_MaxTime = 0;
  m_Start = val;
  m_Target = val;
}
