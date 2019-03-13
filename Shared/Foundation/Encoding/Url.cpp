
#include "Foundation/Common.h"
#include "Foundation/Encoding/Url.h"

bool IsValidUrlChar(char c)
{
  if(c >= 'A' && c <= 'Z')
  {
    return true;
  }

  if(c >= 'a' && c <= 'z')
  {
    return true;
  }

  if(c >= '0' && c <= '9')
  {
    return true;
  }

  switch(c)
  {
  case '-':
  case '_':
  case '.':
  case '~':
    return true;
  default:
    return false;
  }
}

std::string UrlEncode(const void * data, std::size_t length)
{
  std::string out;
  for(auto c = (const char *)data; length > 0; --length)
  {
    if(IsValidUrlChar(*c))
    {
      out += *c;
    }
    else
    {
      out += '%';

      auto hb = (*c & 0xf0) >> 4;
      auto lb = *c & 0x0f;

      if(hb >= 10)
      {
        out += ('A' + hb - 10);
      }
      else
      {
        out += ('0' + hb);
      }

      if(lb >= 10)
      {
        out += ('A' + lb - 10);
      }
      else
      {
        out += ('0' + lb);
      }
    }

    ++c;
  }

  return out;
}

std::string UrlEncode(const std::string_view & data)
{
  return UrlEncode(data.data(), data.size());
}

std::string UrlDecodeAsString(const std::string_view & data)
{
  std::string out;

  auto len = data.size();
  auto ptr = data.data();
  while(len > 0)
  {
    if(*ptr == '%')
    {
      --len;
      ++ptr;
      if(len == 0)
      {
        return out;
      }

      auto hb = *ptr;

      --len;
      ++ptr;
      if(len == 0)
      {
        return out;
      }

      auto lb = *ptr;

      char val = 0;
      if(hb >= '0' && hb <= '9')
      {
        val |= (hb - '0') << 4;
      }
      else if(hb >= 'a' && hb <= 'f')
      {
        val |= (hb - 'a' + 10) << 4;
      }
      else if(hb >= 'A' && hb <= 'F')
      {
        val |= (hb - 'A' + 10) << 4;
      }

      if(lb >= '0' && lb <= '9')
      {
        val |= (lb - '0');
      }
      else if(lb >= 'a' && lb <= 'f')
      {
        val |= (lb - 'a' + 10);
      }
      else if(lb >= 'A' && lb <= 'F')
      {
        val |= (lb - 'A' + 10);
      }

      out += val;

      --len;
      ++ptr;
    }
    else
    {
      ++ptr;
      --len;
    }
  }

  return out;
}

