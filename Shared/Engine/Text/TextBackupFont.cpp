
#include "Engine/EngineCommon.h"
#include "Engine/Text/TextBackupFont.h"
#include "Engine/Asset/AssetLoader.h"

extern FT_Library g_FreeType;

TextBackupFont::TextBackupFont(Buffer && buffer)
{
  m_FontBuffer = std::move(buffer);

  if (FT_New_Memory_Face(g_FreeType, m_FontBuffer.Get(), (long)m_FontBuffer.GetSize(), 0, &m_Face))
  {
    throw std::runtime_error("Coult not load font");
  }
}

TextBackupFont::~TextBackupFont()
{

}

FT_GlyphSlot TextBackupFont::LoadGlyph(char32_t character_code, int font_size)
{
  FT_Set_Pixel_Sizes(m_Face, 0, font_size);

  auto glyph_index = FT_Get_Char_Index(m_Face, character_code);
  if (glyph_index == 0)
  {
    return nullptr;
  }

  if (FT_Load_Glyph(m_Face, glyph_index, FT_LOAD_DEFAULT))
  {
    return nullptr;
  }

  if (FT_Render_Glyph(m_Face->glyph, FT_RENDER_MODE_NORMAL))
  {
    return nullptr;
  }

  return m_Face->glyph;
}
