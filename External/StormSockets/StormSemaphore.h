
#pragma once

#if defined(_WINDOWS) && defined(USE_NATIVE_SEMAPHORE)
typedef void * Semaphore_t;
#else
#include <mutex>
#include <condition_variable>
#endif

namespace StormSockets
{
	class StormSemaphore
	{
#if defined(_WINDOWS) && defined(USE_NATIVE_SEMAPHORE)
    Semaphore_t m_Semaphore;
#else
    std::mutex m_Mutex;
    std::condition_variable m_ConditionVariable;
    int m_Count = 0;
#endif

	public:
		void Init(int max_count);
		void WaitOne(int ms);
		void WaitOne();

		void Release();
	};
}
