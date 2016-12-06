#pragma once

#include <freetype/ft2build.h>
#include FT_FREETYPE_H

class TextBackupFont
{
public:
  TextBackupFont(Buffer && buffer);
  ~TextBackupFont();

  FT_GlyphSlot LoadGlyph(char32_t character_code, int font_size);

private:

  friend class TextRenderer;

  FT_Face m_Face;
  Buffer m_FontBuffer;
};
