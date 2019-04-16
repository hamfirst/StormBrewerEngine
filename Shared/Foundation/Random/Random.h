#pragma once

#include <cstdint>

uint32_t GetRandomNumber();
uint32_t GetRandomNumberRange(uint32_t low, uint32_t high);
uint64_t GetRandomNumber64();
uint64_t GetRandomNumberRange64(uint64_t low, uint64_t high);

float GetRandomUnitFloat();

struct RandomGenerator
{
  using result_type = uint32_t;
  static uint32_t min() { return 0; }
  static uint32_t max() { return UINT32_MAX; }
  uint32_t operator ()() { return GetRandomNumber(); }
};

struct RandomGenerator64
{
  using result_type = uint64_t;
  static uint64_t min() { return 0; }
  static uint64_t max() { return UINT64_MAX; }
  uint64_t operator ()() { return GetRandomNumber64(); }
};
