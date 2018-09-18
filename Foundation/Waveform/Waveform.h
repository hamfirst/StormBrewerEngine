#pragma once

#include <cmath>

#include "Foundation/Math/Math.h"
#include "Foundation/Time/Time.h"

struct SinWaveformCalculator
{
  float operator()(float f) const
  {
    return 0.5f * sinf(f * k2Pi) + 0.5f;
  }
};

struct StepWaveformCalculator
{
  float operator()(float f) const
  {
    return f < 0.5f ? 1.0f : 0.0f;
  }
};

struct SawWaveformCalculator
{
  float operator()(float f) const
  {
    return f;
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

  float Get(float phase_offset) const
  {
    auto time_passed = (float)GetTimeSeconds() - m_Start + phase_offset;
    auto value = fmodf(time_passed, m_Period);

    return m_Calculator(value) * m_Range + m_LowVal;
  }

  operator float() const
  {
    return Get();
  }

  float operator ()(float f) const
  {
    auto value = fmodf(f, m_Period);
    return m_Calculator(value) * m_Range + m_LowVal;
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
using SawWaveform = Waveform<SawWaveformCalculator>;
