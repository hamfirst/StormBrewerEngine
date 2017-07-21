
#include "Game/GameValidation.h"

static const int kMinCharacters = 3;
static const int kMaxCharacters = 16;
static const bool kAllowSpace = false;

bool ValidUserName(const char * name, bool allow_short)
{
  int name_len = 0;
  while(true)
  {
    auto c = *name;
    if (c == 0)
    {
      break;
    }

    name_len++;
    name++;

    bool is_alpha = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
    bool is_num = (c >= '0' && c <= '9');
    bool is_special = (c == '-' || c == '.' || c == '_');
    bool is_space = (c == ' ' && kAllowSpace);

    if (!is_alpha && !is_num && !is_special && !is_space)
    {
      return false;
    }
  }

  if ((name_len < kMinCharacters && allow_short  == false) || name_len > kMaxCharacters)
  {
    return false;
  }

  return true;
}
