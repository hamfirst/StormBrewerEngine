
#pragma once

#include <mutex>

namespace StormSockets
{
  using StormMutex = std::mutex;

  template <typename MutexType>
  using StormUniqueLock = std::unique_lock<MutexType>;


  template <typename MutexType>
  using StormLockGuard = std::lock_guard<MutexType>;
}
