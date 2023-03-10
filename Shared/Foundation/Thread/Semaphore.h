#pragma once

#include <mutex>
#include <condition_variable>

class Semaphore
{
public:
  void WaitOne(int ms);
  void WaitOne();

  void Release(int amount = 1);

private:

  std::mutex m_Mutex;
  std::condition_variable m_ConditionVariable;
  volatile int m_Count = 0;
};
