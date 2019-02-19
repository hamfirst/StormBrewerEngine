#pragma once

#include <string>

bool ParseArgumentDefault(const char *& ptr, std::string & arg);
bool ParseArgumentRemainder(const char *& ptr);

template <typename ... Args>
bool ParseArgumentRemainder(const char *& ptr, std::string & arg, Args && ... args)
{
  if (sizeof...(Args) == 0)
  {
    if (*ptr == 0)
    {
      return false;
    }

    arg = ptr;
    return true;
  }

  if (!ParseArgumentDefault(ptr, arg))
  {
    return false;
  }

  return ParseArgumentRemainder(ptr, std::forward<Args>(args)...);
}

int ParseDuration(const char * str);