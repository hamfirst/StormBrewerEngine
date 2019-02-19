
#include "CommandParse.h"


bool ParseArgumentDefault(const char *& ptr, std::string & arg)
{
  while (*ptr == ' ')
  {
    ptr++;
  }

  if (*ptr == 0)
  {
    return false;
  }

  while (*ptr != 0)
  {
    if (*ptr == ' ')
    {
      ptr++;
      break;
    }

    arg += *ptr;
    ptr++;
  }

  return true;
}

bool ParseArgumentRemainder(const char *& ptr)
{
  return true;
}

int ParseDuration(const char * str)
{
  int duration = 0;

  int parse_val = 0;
  while (*str != 0)
  {
    if (*str >= '0' && *str <= '9')
    {
      parse_val *= 10;
      parse_val += *str - '0';
    }
    else if (*str == 's')
    {
      duration += parse_val;
      parse_val = 0;
    }
    else if (*str == 'm')
    {
      duration += parse_val * 60;
      parse_val = 0;
    }
    else if (*str == 'h')
    {
      duration += parse_val * 60 * 60;
      parse_val = 0;
    }
    else if (*str == 'd')
    {
      duration += parse_val * 24 * 60 * 60;
      parse_val = 0;
    }
    else if (*str == 'w')
    {
      duration += parse_val * 24 * 60 * 60 * 7;
      parse_val = 0;
    }
    else if (*str == 'm')
    {
      duration += parse_val * 24 * 60 * 60 * 30;
      parse_val = 0;
    }
    else if (*str == 'y')
    {
      duration += parse_val * 24 * 60 * 60 * 365;
      parse_val = 0;
    }

    str++;
  }

  return duration;
}
