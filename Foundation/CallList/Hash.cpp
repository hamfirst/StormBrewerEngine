
#include "Foundation\Common.h"
#include "Foundation\Hash\Hash.h"

Hash crc32(czstr str)
{
  Hash hash = 0xFFFFFFFF;
  while (*str != 0)
  {
    hash >>= 8;
    hash ^= crc_table[(hash ^ *str) & 0xFF];
    str++;
  }

  return hash ^ 0xFFFFFFFF;
}

Hash crc32(const std::string & str)
{
  return crc32(str.data());
}
