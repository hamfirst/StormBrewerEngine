
#include "StormExprHash.h"

std::uint32_t StormExprHashString(const char * str)
{
  std::uint32_t hash = 0;

  for (; *str; ++str)
  {
    hash += *str;
    hash += (hash << 10);
    hash ^= (hash >> 6);
  }

  hash += (hash << 3);
  hash ^= (hash >> 11);
  hash += (hash << 15);

  return hash;
}

std::uint32_t StormExprHashString(const char * start, const char * end)
{
  std::uint32_t hash = 0;

  for (; start != end; ++start)
  {
    hash += *start;
    hash += (hash << 10);
    hash ^= (hash >> 6);
  }

  hash += (hash << 3);
  hash ^= (hash >> 11);
  hash += (hash << 15);

  return hash;
}
