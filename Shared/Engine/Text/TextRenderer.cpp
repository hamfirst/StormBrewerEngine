
#include "Engine/EngineCommon.h"
#include "Engine/Text/TextRenderer.h"

#include "Engine/Settings/EngineSettings.refl.h"

#include "Engine/Rendering/VertexBufferBuilder.h"
#include "Engine/Rendering/RenderState.h"

#include <codecvt>

extern FT_Library g_FreeType;

#define COMMON_CHARS "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890!.?-_,:;()\"' \r\n"


TextRenderer::TextRenderer(const AssetReference<FontAsset> & asset_ref, int font_size, std::vector<std::unique_ptr<TextBackupFont>> & backup_fonts) :
  m_Font(asset_ref),
  m_BackupFonts(backup_fonts),
  m_Loaded(false),
  m_Face(nullptr),
  m_FontSize(font_size),
  m_Alloc(g_EngineSettings.m_FontCacheSize, g_EngineSettings.m_FontCacheSize)
{
  m_Texture.CreateEmptyTexture(g_EngineSettings.m_FontCacheSize, g_EngineSettings.m_FontCacheSize, TextureType::kGrayscale);
  m_LoadLink = m_Font.Resolve()->AddLoadCallback(FontAsset::LoadCallback(&TextRenderer::FinalizeAssetLoad, this));

  // Allocate 0,0 to just be a solid pixel
  m_Alloc.Allocate(1, 1);
  PixelBuffer buffer(1, 1, 1);
  *buffer.GetPixelPtr<uint8_t>() = 255;

  m_Texture.SetTextureSubData(buffer, 0, 0);
  m_Texture.SetLinearFilter();
}

TextRenderer::~TextRenderer()
{
  if (m_Face)
  {
    FT_Done_Face(m_Face);
  }
}

void TextRenderer::FinalizeAssetLoad(FontAsset * asset)
{
  if (m_Face)
  {
    FT_Done_Face(m_Face);
    m_Face = nullptr;
  }

  if (asset->IsLoaded())
  {
    if (FT_New_Memory_Face(g_FreeType, asset->m_FontBuffer.Get(), (long)asset->m_FontBuffer.GetSize(), 0, &m_Face))
    {
      printf("Error creating font face\n");
      throw std::runtime_error("Coult not load font");
    }

    FT_Set_Pixel_Sizes(m_Face, 0, m_FontSize);
    AddString(COMMON_CHARS, strlen(COMMON_CHARS));
  }

  m_Loaded = asset->IsLoaded();
}

void TextRenderer::AddGlyphToBuffer(float x, float y, float scale, const GlyphInfo & glyph, const TextSettings & settings, TextBufferBuilder & buffer, const Color & color)
{
  float sx = x + (float)glyph.m_BufferLeft * scale;
  float sy = y + (float)glyph.m_BufferTop * scale;

  float w = (float)glyph.m_Width * scale;
  float h = (float)glyph.m_Height * scale;

  RenderVec2 start_pos = { sx, sy + h };
  RenderVec2 end_pos = { sx + w, sy };

  RenderVec2 start_tex = RenderVec2{ glyph.m_X, glyph.m_Y };
  RenderVec2 end_tex = glyph.m_Rotated ? RenderVec2{ glyph.m_X + glyph.m_Height, glyph.m_Y + glyph.m_Width } :
    RenderVec2{ glyph.m_X + glyph.m_Width, glyph.m_Y + glyph.m_Height };

  start_tex /= RenderVec2{ g_EngineSettings.m_FontCacheSize, g_EngineSettings.m_FontCacheSize };
  end_tex /= RenderVec2{ g_EngineSettings.m_FontCacheSize, g_EngineSettings.m_FontCacheSize };

  // 00 = 10   0 = 2
  // 01 = 00   1 = 0
  // 10 = 11   2 = 3
  // 11 = 01   3 = 1

  VertexInfo text_vert;
  text_vert.m_Color = color;

  text_vert.m_Position = SelectVectorXY(start_pos, end_pos, 0);
  text_vert.m_TexCoord = SelectVectorXY(start_tex, end_tex, glyph.m_Rotated ? 2 : 0);
  buffer.m_Verts.AddVert(text_vert);

  text_vert.m_Position = SelectVectorXY(start_pos, end_pos, 1);
  text_vert.m_TexCoord = SelectVectorXY(start_tex, end_tex, glyph.m_Rotated ? 0 : 1);
  buffer.m_Verts.AddVert(text_vert);

  text_vert.m_Position = SelectVectorXY(start_pos, end_pos, 3);
  text_vert.m_TexCoord = SelectVectorXY(start_tex, end_tex, glyph.m_Rotated ? 1 : 3);
  buffer.m_Verts.AddVert(text_vert);

  text_vert.m_Position = SelectVectorXY(start_pos, end_pos, 0);
  text_vert.m_TexCoord = SelectVectorXY(start_tex, end_tex, glyph.m_Rotated ? 2 : 0);
  buffer.m_Verts.AddVert(text_vert);

  text_vert.m_Position = SelectVectorXY(start_pos, end_pos, 3);
  text_vert.m_TexCoord = SelectVectorXY(start_tex, end_tex, glyph.m_Rotated ? 1 : 3);
  buffer.m_Verts.AddVert(text_vert);

  text_vert.m_Position = SelectVectorXY(start_pos, end_pos, 2);
  text_vert.m_TexCoord = SelectVectorXY(start_tex, end_tex, glyph.m_Rotated ? 3 : 2);
  buffer.m_Verts.AddVert(text_vert);
}

void TextRenderer::CreateVertexBufferForString(const std::string_view & utf8_str, float scale, int sel_start, int sel_end, int cursor_pos,
  const TextSettings & settings, TextBufferBuilder & buffer, std::vector<Box> & glyph_positions)
{
  glyph_positions.clear();

  float line_height = (int)(((float)m_Face->height / (float)m_Face->units_per_EM) * (float)m_FontSize) * scale;
  float ascender = (int)(((float)m_Face->bbox.yMax / (float)m_Face->units_per_EM) * (float)m_FontSize) * scale;
  float descender = (int)(((float)m_Face->bbox.yMin / (float)m_Face->units_per_EM) * (float)m_FontSize) * scale;

  auto len = utf8_str.length();

#ifdef _MSC_VER
  char32_t * wide_buffer = (char32_t *)_alloca(sizeof(char32_t) * len);
#else
  char32_t * wide_buffer = (char32_t *)alloca(sizeof(char32_t) * len);
#endif
  std::codecvt_utf8<char32_t> converter;

  std::mbstate_t mb = {};
  const char * from_next;
  char32_t * to_next;

  float x = (float)settings.m_TextPos.x;
  float y = (float)settings.m_TextPos.y;

  converter.in(mb, utf8_str.data(), utf8_str.data() + len, from_next, wide_buffer, wide_buffer + len, to_next);
  std::size_t num_glyphs = to_next - wide_buffer;
  glyph_positions.reserve(num_glyphs);

  int multiplier = 1;
  if (settings.m_Mode == TextRenderMode::kShadowed)
  {
    multiplier = 2;
  }
  else if (settings.m_Mode == TextRenderMode::kOutlined)
  {
    multiplier = 9;
  }

  for (uint16_t index = 0, glyph_index = 0; wide_buffer != to_next; wide_buffer++, glyph_index++)
  {
    if (*wide_buffer == '\n')
    {
      x = (float)settings.m_TextPos.x;
      y -= (line_height + 2);

      glyph_positions.emplace_back();
      continue;
    }

    if (*wide_buffer == '\r')
    {
      glyph_positions.emplace_back();
      continue;
    }

    auto glyph_itr = m_GlyphMap.find(*wide_buffer);
    if (glyph_itr == m_GlyphMap.end())
    {
      AddGlyph(*wide_buffer);
      glyph_itr = m_GlyphMap.find(*wide_buffer);
    }

    auto & glyph = glyph_itr->second;

    if (glyph.m_Valid == false)
    {
      continue;
    }

    Box glyph_box = { { x, y + ascender }, { x + glyph.m_Advance, y + descender } };
    glyph_positions.emplace_back(glyph_box);

    VertexInfo text_vert;

    if (glyph_index >= sel_start && glyph_index <= sel_end)
    {
      text_vert.m_Color = settings.m_SelectionColor;
      text_vert.m_TexCoord = {};

      Vector2f start_pos = Vector2f(glyph_box.m_Start) * scale;
      Vector2f end_pos = Vector2f(glyph_box.m_End) * scale;

      VertexInfo sel_vert;
      sel_vert.m_Color = settings.m_SelectionBkgColor;
      sel_vert.m_Position = SelectVectorXY(start_pos, end_pos, 0);
      buffer.m_Verts.AddVert(sel_vert);

      sel_vert.m_Position = SelectVectorXY(start_pos, end_pos, 1);
      buffer.m_Verts.AddVert(sel_vert);

      sel_vert.m_Position = SelectVectorXY(start_pos, end_pos, 3);
      buffer.m_Verts.AddVert(sel_vert);

      sel_vert.m_Position = SelectVectorXY(start_pos, end_pos, 0);
      buffer.m_Verts.AddVert(sel_vert);

      sel_vert.m_Position = SelectVectorXY(start_pos, end_pos, 3);
      buffer.m_Verts.AddVert(sel_vert);

      sel_vert.m_Position = SelectVectorXY(start_pos, end_pos, 2);
      buffer.m_Verts.AddVert(sel_vert);
    }
    else
    {
      text_vert.m_Color = settings.m_PrimaryColor;
    }

    if (*wide_buffer == ' ')
    {
      x += (float)glyph.m_Advance * scale;
      continue;
    }

    if (settings.m_Mode == TextRenderMode::kShadowed)
    {
      AddGlyphToBuffer(x + 1, y - 1, scale, glyph, settings, buffer, settings.m_ShadowColor);
    }
    else if (settings.m_Mode == TextRenderMode::kOutlined)
    {
      auto color = settings.m_ShadowColor;
      color.a *= 0.5f;

      AddGlyphToBuffer(x + 1, y + 1, scale, glyph, settings, buffer, color);
      AddGlyphToBuffer(x + 1, y - 1, scale, glyph, settings, buffer, color);
      AddGlyphToBuffer(x - 1, y + 1, scale, glyph, settings, buffer, color);
      AddGlyphToBuffer(x - 1, y - 1, scale, glyph, settings, buffer, color);
      AddGlyphToBuffer(x + 1, y, scale, glyph, settings, buffer, color);
      AddGlyphToBuffer(x - 1, y, scale, glyph, settings, buffer, color);
      AddGlyphToBuffer(x, y + 1, scale, glyph, settings, buffer, color);
      AddGlyphToBuffer(x, y - 1, scale, glyph, settings, buffer, color);
    }

    AddGlyphToBuffer(x, y, scale, glyph, settings, buffer, settings.m_PrimaryColor);
    x += (float)glyph.m_Advance * scale;
  }

  if (cursor_pos >= 0 && cursor_pos <= (int)glyph_positions.size())
  {
    Vector2 start_pos;
    Vector2 end_pos;

    if (glyph_positions.size() == 0)
    {
      start_pos = Vector2(x, y + ascender);
      end_pos = Vector2(x + 1, y + descender);
    }
    else if (cursor_pos < (int)glyph_positions.size())
    {
      start_pos = glyph_positions[cursor_pos].m_Start;
      end_pos = glyph_positions[cursor_pos].m_End;
      end_pos.x = start_pos.x + 1;
    }
    else if (cursor_pos == glyph_positions.size())
    {
      start_pos = glyph_positions[cursor_pos - 1].m_Start;
      end_pos = glyph_positions[cursor_pos - 1].m_End;
      start_pos.x = end_pos.x + 1;
      end_pos.x = start_pos.x + 1;
    }

    start_pos.x = end_pos.x - 2;

    VertexInfo sel_vert;
    sel_vert.m_TexCoord = {};
    sel_vert.m_Color = settings.m_PrimaryColor;
    sel_vert.m_Position = SelectVectorXY(start_pos, end_pos, 0);
    buffer.m_Verts.AddVert(sel_vert);

    sel_vert.m_Position = SelectVectorXY(start_pos, end_pos, 1);
    buffer.m_Verts.AddVert(sel_vert);

    sel_vert.m_Position = SelectVectorXY(start_pos, end_pos, 3);
    buffer.m_Verts.AddVert(sel_vert);

    sel_vert.m_Position = SelectVectorXY(start_pos, end_pos, 0);
    buffer.m_Verts.AddVert(sel_vert);

    sel_vert.m_Position = SelectVectorXY(start_pos, end_pos, 3);
    buffer.m_Verts.AddVert(sel_vert);

    sel_vert.m_Position = SelectVectorXY(start_pos, end_pos, 2);
    buffer.m_Verts.AddVert(sel_vert);
  }
}

void TextRenderer::BindGlyphTexture(RenderState & render_state, int texture_stage)
{
  render_state.BindTexture(m_Texture, texture_stage);
}

Box TextRenderer::GetTextSize(const std::string_view & utf8_str, float scale)
{
  float line_height = (((float)m_Face->height / (float)m_Face->units_per_EM) * (float)m_FontSize * scale);
  float ascender = (((float)m_Face->bbox.yMax / (float)m_Face->units_per_EM) * (float)m_FontSize * scale);
  float descender = (((float)m_Face->bbox.yMin / (float)m_Face->units_per_EM) * (float)m_FontSize * scale);

  float sx = -1;
  float sy = descender;
  float ex = 0;
  float ey = ascender;

  auto len = utf8_str.length();

#ifdef _MSC_VER
  char32_t * wide_buffer = (char32_t *)_alloca(sizeof(char32_t) * len);
#else
  char32_t * wide_buffer = (char32_t *)alloca(sizeof(char32_t) * len);
#endif

  std::codecvt_utf8<char32_t> converter;

  std::mbstate_t mb = {};
  const char * from_next;
  char32_t * to_next;

  converter.in(mb, utf8_str.data(), utf8_str.data() + len, from_next, wide_buffer, wide_buffer + len, to_next);

  for (float line_x = 0; wide_buffer != to_next; wide_buffer++)
  {
    if (*wide_buffer == '\n')
    {
      line_x = 0;
      sy -= line_height + 2;
      continue;
    }

    if (*wide_buffer == '\r')
    {
      continue;
    }

    AddGlyph(*wide_buffer);
    auto glyph_itr = m_GlyphMap.find(*wide_buffer);

    auto & glyph = glyph_itr->second;

    if (glyph.m_Valid == false)
    {
      continue;
    }

    if (line_x == 0)
    {
      sx = std::min((float)glyph.m_BufferLeft, sx);
    }

    line_x += (float)glyph.m_Advance * scale;
    ex = std::max(line_x, ex);
  }

  Box size;
  size.m_Start.x = (int)sx;
  size.m_Start.y = (int)sy;
  size.m_End.x = (int)ex;
  size.m_End.y = (int)ey;

  return size;
}

bool TextRenderer::VisitTextSize(Delegate<bool, const Box &, char32_t, czstr> & callback, const std::string_view & utf8_str, float scale)
{
  float line_height = (((float)m_Face->height / (float)m_Face->units_per_EM) * (float)m_FontSize * scale);
  float ascender = (((float)m_Face->bbox.yMax / (float)m_Face->units_per_EM) * (float)m_FontSize * scale);
  float descender = (((float)m_Face->bbox.yMin / (float)m_Face->units_per_EM) * (float)m_FontSize * scale);

  float sx = -1;
  float sy = descender;
  float ex = 0;
  float ey = ascender;

  auto len = utf8_str.length();

  std::codecvt_utf8<char32_t> converter;

  std::mbstate_t mb = {};
  auto ptr = utf8_str.data();
  auto end = utf8_str.data() + len;
  const char * from_next;
  char32_t * to_next;
  float line_x = 0;

  while (ptr != end)
  {
    char32_t code_point;
    converter.in(mb, ptr, ptr + len, from_next, &code_point, &code_point + 1, to_next);

    ptr = from_next;

    if (code_point == '\n')
    {
      line_x = 0;
      sy -= line_height + 2;
    }
    else if (code_point != '\r')
    {
      AddGlyph(code_point);
      auto glyph_itr = m_GlyphMap.find(code_point);

      auto &glyph = glyph_itr->second;

      if (glyph.m_Valid == false)
      {
        continue;
      }

      if (line_x == 0)
      {
        sx = std::min((float) glyph.m_BufferLeft, sx);
      }

      line_x += (float) glyph.m_Advance * scale;
      ex = std::max(line_x, ex);
    }

    Box size;
    size.m_Start.x = (int)sx;
    size.m_Start.y = (int)sy;
    size.m_End.x = (int)ex;
    size.m_End.y = (int)ey;

    if (callback(size, code_point, ptr) == false)
    {
      return false;
    }
  }

  return true;
}

void TextRenderer::AddString(czstr utf8_str, std::size_t len)
{
#ifdef _MSC_VER
  char32_t * wide_buffer = (char32_t *)_alloca(sizeof(char32_t) * len);
#else
  char32_t * wide_buffer = (char32_t *)alloca(sizeof(char32_t) * len);
#endif

  std::codecvt_utf8<char32_t> converter;

  std::mbstate_t mb = {};
  const char * from_next;
  char32_t * to_next;

  converter.in(mb, utf8_str, utf8_str + len, from_next, wide_buffer, wide_buffer + len, to_next);
  while (wide_buffer != to_next)
  {
    AddGlyph(*wide_buffer);
    wide_buffer++;
  }
}

void TextRenderer::AddGlyph(char32_t character_code)
{
  auto glyph_itr = m_GlyphMap.find(character_code);
  if (glyph_itr != m_GlyphMap.end())
  {
    return;
  }

  auto glyph = LoadGlyph(character_code);
  if(glyph == nullptr)
  {
    m_GlyphMap.emplace(std::make_pair(character_code, GlyphInfo{}));
    return;
  }

  auto pos = m_Alloc.Allocate(glyph->bitmap.width + 2, glyph->bitmap.rows + 2);
  if (!pos)
  {
    m_GlyphMap.emplace(std::make_pair(character_code, GlyphInfo{}));
    return;
  }

  GlyphInfo glyph_info;
  glyph_info.m_Valid = true;
  glyph_info.m_Rotated = pos->m_Rotated;
  glyph_info.m_X = pos->m_X + 1;
  glyph_info.m_Y = pos->m_Y + 1;
  glyph_info.m_Width = glyph->bitmap.width;
  glyph_info.m_Height = glyph->bitmap.rows;
  glyph_info.m_BufferLeft = glyph->bitmap_left;
  glyph_info.m_BufferTop = glyph->bitmap_top - glyph->metrics.height / 64;
  glyph_info.m_Advance = glyph->metrics.horiAdvance / 64;

  m_GlyphMap.emplace(std::make_pair(character_code, glyph_info));

  Optional<PixelBuffer> pixel_buffer;
  if (glyph->bitmap.pixel_mode == FT_PIXEL_MODE_MONO)
  {
    pixel_buffer = PixelBuffer(glyph_info.m_Width, glyph_info.m_Height, 1);

    uint8_t * dst_ptr = pixel_buffer->GetPixelPtr<uint8_t>();

    uint8_t * src_ptr = glyph->bitmap.buffer;
    for (int y = 0; y < glyph_info.m_Height; y++)
    {
      uint8_t * ptr = src_ptr;
      int bit = 7;
      for (int x = 0; x < glyph_info.m_Width; x++)
      {
        *dst_ptr = ((1 << bit) & *ptr) != 0 ? 255 : 0;
        dst_ptr++;
        bit--;

        if (bit < 0)
        {
          ptr++;
          bit = 7;
        }
      }

      src_ptr += glyph->bitmap.pitch;
    }
  }
  else if (glyph->bitmap.pixel_mode == FT_PIXEL_MODE_GRAY)
  {
    pixel_buffer = PixelBuffer(glyph->bitmap.buffer, glyph_info.m_Width, glyph_info.m_Height, 1);
  }
  else
  {
    throw std::runtime_error("Invalid font file");
  }
  
  if (pos->m_Rotated)
  {
    m_Texture.SetTextureSubData(pixel_buffer->Rotate(), glyph_info.m_X, glyph_info.m_Y);
  }
  else
  {
    m_Texture.SetTextureSubData(*pixel_buffer, glyph_info.m_X, glyph_info.m_Y);
  }
}

FT_GlyphSlot TextRenderer::LoadGlyph(char32_t character_code)
{
  auto glyph_index = FT_Get_Char_Index(m_Face, character_code);
  if (glyph_index == 0)
  {
    return LoadBackupGlyph(character_code);
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

FT_GlyphSlot TextRenderer::LoadBackupGlyph(char32_t character_code)
{
  for (auto & font : m_BackupFonts)
  {
    auto glyph = font->LoadGlyph(character_code, m_FontSize);
    if (glyph)
    {
      return glyph;
    }
  }

  return nullptr;
}
