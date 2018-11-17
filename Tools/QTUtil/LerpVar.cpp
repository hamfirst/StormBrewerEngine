#include "LerpVar.h"

#include <QTimer>

LerpVar::LerpVar(bool create_updater, float time, QObject *parent) : QObject(parent)
{
  m_Time = (int)(time * 1000);
  m_Timer = new QTime();

  m_Target = 0;
  m_Var = 0;

  if (create_updater)
  {
    QTimer * updater = new QTimer(this);
    connect(updater, &QTimer::timeout, this, &LerpVar::update);
    updater->start(16);
  }
}

bool LerpVar::update()
{
  if(m_Var == m_Target)
  {
    return false;
  }

  float move_fac = GetLerpFactor();
  float inv_move_fac = 1.0f - move_fac;

  if(move_fac >= 1.0f)
  {
    m_Var = m_Target;
  }
  else
  {
    m_Var = m_Target * move_fac + m_Var * inv_move_fac;
  }

  m_Modified = true;
  return true;
}
