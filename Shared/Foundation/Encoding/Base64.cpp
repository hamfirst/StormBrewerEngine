
#include "Foundation/Common.h"
#include "Foundation/Encoding/Base64.h"

char b64chr(uint8_t v)
{
  if(v < 26)
  {
    return 'A' + v;
  }
  else if(v < 52)
  {
    return 'a' + v - 26;
  }
  else if(v < 62)
  {
    return '0' + v - 52;
  }
  else if(v == 62)
  {
    return '+';
  }
  else if(v == 63)
  {
    return '/';
  }
  else
  {
    ASSERT(false, "Bad base64 value");
  }
}

uint8_t b64dechr(char c)
{
  if(c >= 'A' && c <= 'Z')
  {
    return (uint8_t)(c - 'A');
  }
  else if(c >= 'a' && c <= 'z')
  {
    return (uint8_t)(c - 'a' + 26);
  }
  else if(c >= '0' && c <= '9')
  {
    return (uint8_t)(c - '0' + 52);
  }
  else if(c == '+')
  {
    return 62;
  }
  else if(c == '/')
  {
    return 63;
  }
  else
  {
    ASSERT(false, "Bad base64 value");
  }
}

std::string Base64Encode(const void * data, std::size_t length)
{
  std::string out;
  uint8_t prev_bits = 0;
  uint8_t num_bits = 0;

  uint8_t * ptr = (uint8_t *)data;
  uint8_t * end = ptr + length;

  while(ptr != end)
  {
    if(num_bits >= 6)
    {
      out += b64chr(prev_bits);

      prev_bits = 0;
      num_bits = 0;
    }
    else
    {
      int consumed_bits = 6 - num_bits;
      int extra_bits = 8 - consumed_bits;

      auto val = *ptr;
      val >>= (8 - consumed_bits);
      val |= prev_bits;

      out += b64chr(val);

      prev_bits = (*ptr << (6 - extra_bits)) & 0x3f;
      num_bits = (uint8_t)extra_bits;

      ptr++;
    }
  }

  if(num_bits > 0)
  {
    out += b64chr(prev_bits & 0x3f);
  }

  if(num_bits == 2)
  {
    out += "==";
  }

  if(num_bits == 4)
  {
    out += "=";
  }

  return out;
}

std::string Base64Encode(const std::string_view & str)
{
  return Base64Encode(str.data(), str.length());
}

std::vector<uint8_t> Base64Decode(const std::string_view & data)
{
  std::vector<uint8_t> buffer;

  uint8_t pushed_bits = 0;
  uint8_t num_bits = 0;

  for(auto & c : data)
  {
    if(c == '=')
    {
      num_bits -= 2;
      continue;
    }

    uint8_t val = b64dechr(c);
    uint8_t available_bits = 8 - num_bits;

    if(available_bits == 8)
    {
      pushed_bits |= (val << 2);
      num_bits = 6;
    }
    else if(available_bits == 6)
    {
      pushed_bits |= (val);
      buffer.emplace_back(pushed_bits);

      num_bits = 0;
      pushed_bits = 0;
    }
    else if(available_bits == 4)
    {
      pushed_bits |= (val >> 2);
      buffer.emplace_back(pushed_bits);

      num_bits = 2;
      pushed_bits = (val << 6);
    }
    else if(available_bits == 2)
    {
      pushed_bits |= (val >> 4);
      buffer.emplace_back(pushed_bits);

      num_bits = 4;
      pushed_bits = (val << 4);
    }
  }

  if(num_bits > 0)
  {
    buffer.emplace_back(pushed_bits);
  }

  return buffer;
}
