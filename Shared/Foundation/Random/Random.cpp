
#include "Foundation/Common.h"

#include <random>
#include <chrono>

static std::mt19937 s_RandomEngine(std::random_device{}());
static std::mt19937_64 s_RandomEngine64(std::random_device{}());

uint32_t GetRandomNumber()
{
  return (uint32_t)s_RandomEngine();
}

uint32_t GetRandomNumberRange(uint32_t low, uint32_t high)
{
  std::uniform_int_distribution<uint32_t> dist(low, high);
  return dist(s_RandomEngine);
}

uint64_t GetRandomNumber64()
{
  return (uint64_t)s_RandomEngine64();
}

uint64_t GetRandomNumberRange64(uint64_t low, uint64_t high)
{
  std::uniform_int_distribution<uint64_t> dist(low, high);
  return dist(s_RandomEngine64);
}

float GetRandomUnitFloat()
{
  uint32_t val = GetRandomNumber();
  return (float)val / (float)UINT_MAX;
}