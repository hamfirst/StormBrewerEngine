#pragma once

#include <cmath>

#include "Foundation/Math/Math.h"
#include "Foundation/Time/Time.h"

struct SinWaveformCalculator
{
  static float operator(float f)
  {
    return sinf(f * k2Pi);
  }
};

struct StepWaveformCalculator
{
  static float operator(float f)
  {
    return f < 0.5f : 1.0f : 0.0f;
  }
};

template <typename ValueCalculator>
class Waveform
{
public:
  Waveform(float period, float range_low = 0.0f, float range_high = 1.0f, float phase_offset = 0.0f)
  {
    m_Start = (float)GetTimeSeconds() - period + phase_offset;
    m_Period = period;

    m_LowVal = range_low;
    m_Range = range_high - range_low;
  }

  float Get() const
  {
    auto time_passed = (float)GetTimeSeconds() - m_Start;
    auto value = fmodf(time_passed, m_Period);

    return m_Calculator(value) * m_Range + m_LowVal;
  }

  operator float() const
  {
    return Get();
  }

private:
  ValueCalculator m_Calculator;

  float m_Start;
  float m_Period;
  float m_LowVal;
  float m_Range;
};

using SinWaveform = Waveform<SinWaveformCalculator>;
using StepWaveform = Waveform<StepWaveformCalculator>;
