#pragma once

#include "Foundation/Common.h"
#include "Foundation/Delegate/Delegate.h"
#include "Foundation/Time/StopWatch.h"

class SequenceElement
{
public:
  SequenceElement(float time, Delegate<void, float> && del);
  SequenceElement(const SequenceElement & rhs) = default;
  SequenceElement(SequenceElement && rhs) = default;

  SequenceElement & operator = (const SequenceElement & rhs) = default;
  SequenceElement & operator = (SequenceElement && rhs) = default;

  float Update(float time);
  void Complete();

private:

  float m_TimeLeft;
  float m_MaxTime;

  Delegate<void, float> m_Delegate;
};

class Sequencer
{
public:

  Sequencer();

  void Update();
  void Push(float time, Delegate<void, float> && del);
  void Complete();
  bool IsComplete() const;


  void Clear();

private:
  std::vector<SequenceElement> m_Elems;
  std::size_t m_CurElem;

  StopWatch m_Timer;

};

