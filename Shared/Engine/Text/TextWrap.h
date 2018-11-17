#pragma once

#include "Engine/EngineCommon.h"
#include "Engine/Text/TextManager.h"

template <typename Visitor>
void VisitTextWrapPoints(Visitor && visitor, const std::string_view & text, int font_id, float scale, int width)
{
  auto len = text.length();
  auto start = text.data();
  auto end = start + len;
  auto prev_text = start;

  while(start != end)
  {
    auto last_break = start;

    auto callback = [&](const Box &box, char32_t codepoint, czstr ptr)
    {
      if(codepoint == '\r')
      {
        return true;
      }

      if(codepoint == '\n')
      {
        auto new_text = ptr + 1;
        auto num_chars = new_text - start;

        visitor(std::string_view(start, new_text - start));

        ASSERT(len >= num_chars, "Consuming too much text to wrap");
        len -= num_chars;
        start = new_text;
        return false;
      }

      if(codepoint == '\t' || codepoint == ' ')
      {
        last_break = ptr;
      }

      if(box.m_End.x >= width )
      {
        czstr new_text;
        if(last_break == start)
        {
          new_text = prev_text;
        }
        else
        {
          new_text = last_break;
        }

        auto num_chars = new_text - start;

        visitor(std::string_view(start, new_text - start));

        ASSERT(len >= num_chars, "Consuming too much text to wrap");
        len -= num_chars;
        start = new_text;
        return false;
      }

      prev_text = ptr;
      return true;
    };

    if(g_TextManager.VisitTextSize(callback, std::string_view(start, len), font_id, scale))
    {
      visitor(std::string(start, len));
      break;
    }
  }
}

