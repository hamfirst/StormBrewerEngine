
#pragma once

#include <QObject>
#include <QTime>

class LerpVar : public QObject
{
  Q_OBJECT
public:
  explicit LerpVar(bool create_updater = true, float time = 0.3f, QObject *parent = 0);

  float operator = (float val)
  {
    SetTarget(val);
    return val;
  }

  int operator = (int val)
  {
    SetTarget((float)val);
    return val;
  }

  float operator *= (float val)
  {
    SetTarget(m_Target * val);
    return val;
  }

  float operator * (float val)
  {
    return m_Target * val;
  }

  operator float()
  {
    return m_Var;
  }

  float Get()
  {
    return m_Var;
  }

  float Get(bool & is_modified)
  {
    is_modified = m_Modified;
    m_Modified = false;

    return m_Var;
  }

  bool WasModified()
  {
    if (m_Modified)
    {
      m_Modified = false;
      return true;
    }

    return false;
  }

  void Set(float val)
  {
    m_Target = val;
    m_Var = val;
  }

  void SetTarget(float val)
  {
    m_Timer->restart();
    m_Target = val;
  }

  void SetValue(float val)
  {
    m_Var = val;
  }

  void Complete()
  {
    m_Var = m_Target;
    m_Modified = true;
  }

  bool IsComplete()
  {
    return m_Var == m_Target;
  }

  float GetTarget()
  {
    return m_Target;
  }

  float GetLerpFactor()
  {
    return m_Var == m_Target ? 1.0f : std::min((float)m_Timer->elapsed() / (float)m_Time, 1.0f);
  }

private:
  float m_Target;
  float m_Var;

  QTime * m_Timer;
  int m_Time;

  bool m_Modified;

signals:

public slots:
  bool update();
};


