
#include "Foundation/Common.h"
#include "Semaphore.h"

#ifndef _INCLUDEOS

void Semaphore::WaitOne(int ms)
{
  std::unique_lock<std::mutex> lck(m_Mutex);
  while (m_Count == 0)
  {
    m_ConditionVariable.wait_for(lck, std::chrono::milliseconds(ms));
  }

  m_Count--;
}

void Semaphore::WaitOne()
{
  std::unique_lock<std::mutex> lock(m_Mutex);
  while (m_Count == 0)
  {
    m_ConditionVariable.wait(lock);
  }

  m_Count--;
}

void Semaphore::Release(int amount)
{
  std::unique_lock<std::mutex> lock(m_Mutex);
  m_Count += amount;

  if (amount == 1)
  {
    m_ConditionVariable.notify_one();
  }
  else
  {
    m_ConditionVariable.notify_all();
  }
}

#endif
