
#include "Foundation\Common.h"
#include "Foundation\Hash\Hash.h"

uint32_t crc32(const char * str)
{
  uint32_t hash = 0xFFFFFFFF;
  while (*str != 0)
  {
    hash >>= 8;
    hash ^= crc_table[(hash ^ *str) & 0xFF];
    str++;
  }

  return hash ^ 0xFFFFFFFF;
}

uint32_t crc32(const std::string & str)
{
  return crc32(str.data());
}