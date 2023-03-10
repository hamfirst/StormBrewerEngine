

#include <thread>
#include <chrono>

void StormBootstrapBlock()
{
  std::this_thread::sleep_for(std::chrono::milliseconds(1));
}
