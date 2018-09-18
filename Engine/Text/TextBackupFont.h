#pragma once

#include <freetype2/ft2build.h>
#include FT_FREETYPE_H

class ENGINE_EXPORT TextBackupFont
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
