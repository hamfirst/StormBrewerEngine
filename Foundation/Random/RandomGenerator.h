#pragma once

#include <random>

class RandomGenerator
{
public:
  RandomGenerator(uint32_t seed);

  uint32_t GetRandomNumber();
  uint32_t GetRandomNumberRange(uint32_t low, uint32_t high);

  float GetRandomNumberUniform();

private:
  std::mt19937 m_RandomEngine;
};

class RandomGenerator64
{
public:
  RandomGenerator64(uint64_t seed);

  uint64_t GetRandomNumber();
  uint64_t GetRandomNumberRange(uint64_t low, uint64_t high);

  float GetRandomNumberUniform();

private:
  std::mt19937_64 m_RandomEngine;
};
