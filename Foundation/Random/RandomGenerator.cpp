
#include "Foundation/Common.h"
#include "Foundation/Random/RandomGenerator.h"


RandomGenerator::RandomGenerator(uint32_t seed) :
  m_RandomEngine(seed)
{

}

uint32_t RandomGenerator::GetRandomNumber()
{
  return m_RandomEngine();
}

uint32_t RandomGenerator::GetRandomNumberRange(uint32_t low, uint32_t high)
{
  std::uniform_int_distribution<uint32_t> dist(low, high);
  return dist(m_RandomEngine);
}

float RandomGenerator::GetRandomNumberUniform()
{
  std::uniform_real_distribution<float> dist(0.0f, 1.0f);
  return dist(m_RandomEngine);
}


RandomGenerator64::RandomGenerator64(uint64_t seed) :
  m_RandomEngine(seed)
{

}

uint64_t RandomGenerator64::GetRandomNumber()
{
  return m_RandomEngine();
}

uint64_t RandomGenerator64::GetRandomNumberRange(uint64_t low, uint64_t high)
{
  std::uniform_int_distribution<uint64_t> dist(low, high);
  return dist(m_RandomEngine);
}

float RandomGenerator64::GetRandomNumberUniform()
{
  std::uniform_real_distribution<float> dist(0.0f, 1.0f);
  return dist(m_RandomEngine);
}
