#pragma once

#include "Foundation/Allocator/Allocator2D.h"

#include "Engine/Asset/FontAsset.h"
#include "Engine/Rendering/Texture.h"
#include "Engine/Rendering/VertexBuffer.h"

#include "Data/BasicTypes/BasicTypes.refl.h"

#include <unordered_map>

#include <freetype/ft2build.h>
#include FT_FREETYPE_H

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
  TextRenderer(const AssetReference<FontAsset> & asset_ref, int font_size);
  ~TextRenderer();

  std::size_t CreateVertexBufferForString(czstr utf8_str, std::size_t len, VertexBuffer & vertex_buffer, const Color & color);
  void BindGlyphTexture(int texture_stage);
  Box GetTextSize(czstr utf8_str, std::size_t len);

  bool Loaded() { return m_Loaded; }
  
private:

  void FinalizeAssetLoad(FontAsset * asset, bool success);

  void AddString(czstr utf8_str, std::size_t len);
  void AddGlyph(char32_t character_code);

private:

  AssetReference<FontAsset> m_Font;

  bool m_Loaded;
  FT_Face m_Face;

  int m_FontSize;

  Texture m_Texture;

  std::unordered_map<char32_t, GlyphInfo> m_GlyphMap;
  Allocator2D m_Alloc;

  FontAsset::LoadCallbackLink m_LoadLink;
};

