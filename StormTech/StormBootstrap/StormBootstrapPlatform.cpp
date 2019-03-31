

#ifdef _INCLUDEOS
#include <kernel/os.hpp>
#else
#include <thread>
#include <chrono>
#endif

void StormBootstrapBlock()
{
#ifdef _INCLUDEOS
  OS::block();
#else
  std::this_thread::sleep_for(std::chrono::milliseconds(1));
#endif
}
