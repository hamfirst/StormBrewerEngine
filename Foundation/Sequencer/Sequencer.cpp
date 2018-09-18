
#include "Foundation/Common.h"
#include "Foundation/Sequencer/Sequencer.h"

SequenceElement::SequenceElement(float time, Delegate<void, float> && del) :
  m_TimeLeft(time),
  m_MaxTime(time),
  m_Delegate(std::move(del))
{

}

float SequenceElement::Update(float time)
{
  m_TimeLeft -= time;
  if (m_TimeLeft < 0)
  {
    m_Delegate(1.0f);
    return -m_TimeLeft;
  }

  m_Delegate(1.0f - m_TimeLeft / m_MaxTime);
  return 0;
}

void SequenceElement::Complete()
{
  m_Delegate(1.0f);
}

Sequencer::Sequencer() :
  m_CurElem(0),
  m_Paused(false)
{
  m_Timer.Start();
}

void Sequencer::Update()
{
  auto time_passed = (float)m_Timer.GetTimeSinceLastCheck();
  Update(time_passed);
}

void Sequencer::Update(float dt)
{
  auto time_passed = dt;
  while (m_CurElem < m_Elems.size() && m_Paused == false)
  {
    if (time_passed == 0)
    {
      return;
    }

    time_passed = m_Elems[m_CurElem].Update(time_passed);
    if (time_passed > 0)
    {
      m_CurElem++;
    }
  }
}

void Sequencer::Skip()
{
  m_Timer.GetTimeSinceLastCheck();
}

void Sequencer::Push(float time, Delegate<void, float> && del)
{
  m_Elems.emplace_back(time, std::move(del));
}

void Sequencer::Complete()
{
  while (m_CurElem < m_Elems.size())
  {
    m_Elems[m_CurElem].Complete();
    m_CurElem++;
  }
}

bool Sequencer::IsComplete() const
{
  return m_CurElem >= m_Elems.size();
}

void Sequencer::Clear()
{
  m_Elems.clear();
  m_CurElem = 0;
}

void Sequencer::Pause()
{
  m_Paused = true;
}

void Sequencer::Unpause()
{
  m_Paused = false;
}
