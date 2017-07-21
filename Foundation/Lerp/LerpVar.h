#pragma once

class LerpVar
{
public:

  LerpVar();
  LerpVar(float initial_val);

  LerpVar(const LerpVar & rhs) = default;
  LerpVar(LerpVar && rhs) = default;

  operator float() const;
  float Get() const;

  void LerpTo(float val, float time);
  void Set(float val);

private:
  float m_StartTimer;
  float m_MaxTime;

  float m_Start;
  float m_Target;
};

