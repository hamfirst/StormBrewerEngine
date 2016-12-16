#pragma once

#include "Foundation/Allocator/Allocator2D.h"

#include "Engine/Asset/FontAsset.h"
#include "Engine/Rendering/Texture.h"
#include "Engine/Rendering/VertexBuffer.h"
#include "Engine/Text/TextBackupFont.h"
#include "Engine/Text/TextManager.h"
#include "Engine/Text/TextBufferBuilder.h"

struct GlyphInfo
{
  bool m_Valid;
  bool m_Rotated;
  int m_X, m_Y;
  int m_Width, m_Height;
  int m_BufferLeft;
  int m_BufferTop;
  int m_Advance;
};

class TextRenderer
{
public:
  TextRenderer(const AssetReference<FontAsset> & asset_ref, int font_size, std::vector<std::unique_ptr<TextBackupFont>> & backup_fonts);
  ~TextRenderer();

  void CreateVertexBufferForString(czstr utf8_str, std::size_t len, int sel_start, int sel_end, int cursor_pos,
    const TextSettings & settings, TextBufferBuilder & buffer, std::vector<Box> & glyph_positions);

  void BindGlyphTexture(int texture_stage);
  Box GetTextSize(czstr utf8_str, std::size_t len);

  bool Loaded() { return m_Loaded; }
  
private:

  void FinalizeAssetLoad(FontAsset * asset, bool success);

  void AddGlyphToBuffer(int x, int y, const GlyphInfo & glyph, const TextSettings & settings, TextBufferBuilder & buffer, const Color & color);

  void AddString(czstr utf8_str, std::size_t len);
  void AddGlyph(char32_t character_code);

  FT_GlyphSlot LoadGlyph(char32_t character_code);
  FT_GlyphSlot LoadBackupGlyph(char32_t character_code);

private:

  AssetReference<FontAsset> m_Font;
  std::vector<std::unique_ptr<TextBackupFont>> & m_BackupFonts;

  bool m_Loaded;
  FT_Face m_Face;

  int m_FontSize;

  Texture m_Texture;

  std::unordered_map<char32_t, GlyphInfo> m_GlyphMap;
  Allocator2D m_Alloc;

  FontAsset::LoadCallbackLink m_LoadLink;
};

