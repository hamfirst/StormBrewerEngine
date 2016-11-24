
#include "Engine/EngineCommon.h"
#include "Engine/Text/TextRenderer.h"

#include "Engine/Settings/EngineSettings.refl.h"

#include "Engine/Rendering/VertexBufferBuilder.h"
#include "Engine/Rendering/RenderState.h"

#include "Data/BasicTypes/BasicTypeFuncs.h"


#include <codecvt>

extern FT_Library g_FreeType;

#define COMMON_CHARS "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890!.?-_,:;()\"' \r\n"


TextRenderer::TextRenderer(const AssetReference<FontAsset> & asset_ref, int font_size) :
  m_Font(asset_ref),
  m_Loaded(false),
  m_Face(nullptr),
  m_FontSize(font_size),
  m_Alloc(g_EngineSettings.m_FontCacheSize, g_EngineSettings.m_FontCacheSize)
{
  m_Texture.CreateEmptyTexture(g_EngineSettings.m_FontCacheSize, g_EngineSettings.m_FontCacheSize, TextureType::kGrayscale);
  m_LoadLink = m_Font.Resolve()->AddLoadCallback(FontAsset::LoadCallback(&TextRenderer::FinalizeAssetLoad, this));
}

TextRenderer::~TextRenderer()
{
  if (m_Face)
  {
    FT_Done_Face(m_Face);
  }
}

void TextRenderer::FinalizeAssetLoad(FontAsset * asset, bool success)
{
  if (m_Face)
  {
    FT_Done_Face(m_Face);
    m_Face = nullptr;
  }

  if (success)
  {
    if (FT_New_Memory_Face(g_FreeType, asset->m_FontBuffer.Get(), (long)asset->m_FontBuffer.GetSize(), 0, &m_Face))
    {
      throw std::runtime_error("Coult not load font");
    }

    FT_Set_Pixel_Sizes(m_Face, 0, m_FontSize);
    AddString(COMMON_CHARS, strlen(COMMON_CHARS));
  }

  m_Loaded = success;
}

std::size_t TextRenderer::CreateVertexBufferForString(czstr utf8_str, std::size_t len, VertexBuffer & vertex_buffer, const Color & color)
{
  char32_t * wide_buffer = (char32_t *)_alloca(sizeof(char32_t) * len);

  std::codecvt_utf8<char32_t> converter;

  std::mbstate_t mb = {};
  const char * from_next;
  char32_t * to_next;

  int x = 0, y = 0;

  converter.in(mb, utf8_str, utf8_str + len, from_next, wide_buffer, wide_buffer + len, to_next);
  std::size_t num_glyphs = to_next - wide_buffer;
  std::vector<VertexInfo> verts;
  std::vector<uint16_t> indices;

  verts.reserve(num_glyphs * 4);
  indices.reserve(num_glyphs * 4);

  for (uint16_t index = 0; wide_buffer != to_next; wide_buffer++)
  {
    if (*wide_buffer == '\n')
    {
      x = 0;
      y -= m_FontSize;
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

    if (*wide_buffer == ' ')
    {
      x += glyph.m_Advance;
      continue;
    }

    RenderVec2 start_pos = { x + glyph.m_BufferLeft, y + glyph.m_BufferTop + glyph.m_Height };
    RenderVec2 end_pos = { x + glyph.m_BufferLeft + glyph.m_Width, y + glyph.m_BufferTop };

    RenderVec2 start_tex = RenderVec2{glyph.m_X, glyph.m_Y };
    RenderVec2 end_tex = glyph.m_Rotated ? RenderVec2{glyph.m_X + glyph.m_Height, glyph.m_Y + glyph.m_Width } :
                                           RenderVec2{glyph.m_X + glyph.m_Width, glyph.m_Y + glyph.m_Height };

    start_tex /= RenderVec2{ g_EngineSettings.m_FontCacheSize, g_EngineSettings.m_FontCacheSize };
    end_tex /= RenderVec2{ g_EngineSettings.m_FontCacheSize, g_EngineSettings.m_FontCacheSize };

    // 00 = 10   0 = 2
    // 01 = 00   1 = 0
    // 10 = 11   2 = 3
    // 11 = 01   3 = 1

    VertexInfo vert;
    vert.m_Color = color;

    vert.m_Position = SelectVectorXY(start_pos, end_pos, 0);
    vert.m_TexCoord = SelectVectorXY(start_tex, end_tex, glyph.m_Rotated ? 2 : 0);
    verts.emplace_back(vert); indices.emplace_back(index); index++;

    vert.m_Position = SelectVectorXY(start_pos, end_pos, 1);
    vert.m_TexCoord = SelectVectorXY(start_tex, end_tex, glyph.m_Rotated ? 0 : 1);
    verts.emplace_back(vert); indices.emplace_back(index); index++;

    vert.m_Position = SelectVectorXY(start_pos, end_pos, 3);
    vert.m_TexCoord = SelectVectorXY(start_tex, end_tex, glyph.m_Rotated ? 1 : 3);
    verts.emplace_back(vert); indices.emplace_back(index); index++;

    vert.m_Position = SelectVectorXY(start_pos, end_pos, 2);
    vert.m_TexCoord = SelectVectorXY(start_tex, end_tex, glyph.m_Rotated ? 3 : 2);
    verts.emplace_back(vert); indices.emplace_back(index); index++;

    x += glyph.m_Advance;
  }

  vertex_buffer.SetBufferData(verts, indices, VertexBufferType::kQuads);
  return num_glyphs;
}

void TextRenderer::BindGlyphTexture(int texture_stage)
{
  m_Texture.BindTexture(texture_stage);
}

Box TextRenderer::GetTextSize(czstr utf8_str, std::size_t len)
{
  Box size;
  int line_height = (int)(((float)m_Face->height / (float)m_Face->units_per_EM) * m_FontSize);
  int ascender = (int)(((float)m_Face->bbox.yMax / (float)m_Face->units_per_EM) * m_FontSize);
  int descender = (int)(((float)m_Face->bbox.yMin / (float)m_Face->units_per_EM) * m_FontSize);

  size.m_Start.x = -1;
  size.m_Start.y = descender;
  size.m_End.x = 0;
  size.m_End.y = ascender;

  char32_t * wide_buffer = (char32_t *)_alloca(sizeof(char32_t) * len);

  std::codecvt_utf8<char32_t> converter;

  std::mbstate_t mb = {};
  const char * from_next;
  char32_t * to_next;

  converter.in(mb, utf8_str, utf8_str + len, from_next, wide_buffer, wide_buffer + len, to_next);

  for (int line_x = 0; wide_buffer != to_next; wide_buffer++)
  {
    if (*wide_buffer == '\n')
    {
      line_x = 0;
      size.m_Start.y -= m_FontSize;
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
      size.m_Start.x = std::min(glyph.m_BufferLeft, (int)size.m_Start.x);
    }

    line_x += glyph.m_Advance;
    size.m_End.x = std::max(line_x, (int)size.m_End.x);
  }

  return size;
}

void TextRenderer::AddString(czstr utf8_str, std::size_t len)
{
  char32_t * wide_buffer = (char32_t *)_alloca(sizeof(char32_t) * len);

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

  auto glyph_index = FT_Get_Char_Index(m_Face, character_code);
  if (glyph_index == 0)
  {
    m_GlyphMap.emplace(std::make_pair(character_code, GlyphInfo{}));
    return;
  }

  if (FT_Load_Glyph(m_Face, glyph_index, FT_LOAD_DEFAULT))
  {
    m_GlyphMap.emplace(std::make_pair(character_code, GlyphInfo{}));
    return;
  }

  if (FT_Render_Glyph(m_Face->glyph, FT_RENDER_MODE_NORMAL))
  {
    m_GlyphMap.emplace(std::make_pair(character_code, GlyphInfo{}));
    return;
  }

  auto pos = m_Alloc.Allocate(m_Face->glyph->bitmap.width + 2, m_Face->glyph->bitmap.rows + 2);
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
  glyph_info.m_Width = m_Face->glyph->bitmap.width;
  glyph_info.m_Height = m_Face->glyph->bitmap.rows;
  glyph_info.m_BufferLeft = m_Face->glyph->bitmap_left;
  glyph_info.m_BufferTop = m_Face->glyph->bitmap_top - m_Face->glyph->metrics.height / 64;
  glyph_info.m_Advance = m_Face->glyph->metrics.horiAdvance / 64;

  m_GlyphMap.emplace(std::make_pair(character_code, glyph_info));

  PixelBuffer pixel_buffer(m_Face->glyph->bitmap.buffer, glyph_info.m_Width, glyph_info.m_Height, 1);
  
  if (pos->m_Rotated)
  {
    m_Texture.SetTextureSubData(pixel_buffer.Rotate(), glyph_info.m_X, glyph_info.m_Y);
  }
  else
  {
    m_Texture.SetTextureSubData(pixel_buffer, glyph_info.m_X, glyph_info.m_Y);
  }
}
