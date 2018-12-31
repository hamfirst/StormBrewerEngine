
#include "Engine/EngineCommon.h"

#include "Foundation/FileSystem/File.h"

#include "Engine/Text/TextManager.h"
#include "Engine/Text/TextRenderer.h"
#include "Engine/Input/TextInputContext.h"
#include "Engine/Rendering/Shader.h"
#include "Engine/Rendering/RenderErrorMacros.h"
#include "Engine/Rendering/RenderState.h"
#include "Engine/Shader/ShaderManager.h"
#include "Engine/Asset/AssetLoader.h"

#include <codecvt>
#include "Engine/Text/TextWrap.h"

TextManager g_TextManager;

static std::map<int, std::unique_ptr<TextRenderer>> s_Fonts;
std::vector<std::unique_ptr<TextBackupFont>> s_BackupFonts;

TextManager::TextManager() :
  m_TextVertexBuffer(true)
{
}

void TextManager::Init()
{
#ifdef _MSC_VER
  //LoadBackupFont("C:\\Windows\\Fonts\\arial.ttf");
  //LoadBackupFont("C:\\Windows\\Fonts\\gulim.ttc");
#endif

  SetTextMode();
  SetPrimaryColor();
  SetShadowColor();
  SetSelectionColor();
  SetSelectionBkgColor();
}

void TextManager::ShutDown()
{
  s_Fonts.clear();
}

Optional<int> TextManager::FindFontId(czstr font_path, int font_size)
{
  auto path_hash = crc32lowercase(font_path);
  for(auto && elem : s_Fonts)
  {
    if(elem.second->GetFontAssetHash() == path_hash && elem.second->GetFontSize() == font_size)
    {
      return elem.first;
    }
  }

  return {};
}

void TextManager::LoadFont(czstr font_path, int font_id, int font_size)
{
  s_Fonts.emplace(std::make_pair(font_id, std::make_unique<TextRenderer>(FontAsset::Load(font_path), font_size, s_BackupFonts)));
}

bool TextManager::IsFontLoaded(int font_id)
{
  auto itr = s_Fonts.find(font_id);
  if (itr == s_Fonts.end())
  {
    return false;
  }

  auto & font = itr->second;
  return font->Loaded();
}

bool TextManager::AllFontsLoaded()
{
  for(auto & elem : s_Fonts)
  {
    if(elem.second->Loaded() == false)
    {
      return false;
    }
  }

  return true;
}

void TextManager::AddTextToBuffer(const std::string_view & text, int font_id, float scale,
        TextBufferBuilder & vertex_builder, int sel_start, int sel_end, int cursor_pos)
{
  auto itr = s_Fonts.find(font_id);
  if (itr == s_Fonts.end())
  {
    return;
  }

  auto & font = itr->second;
  if (font->Loaded() == false)
  {
    return;
  }

  if (vertex_builder.m_FontId == kInvalidFontId)
  {
    vertex_builder.m_FontId = font_id;
  }
  else if (vertex_builder.m_FontId != font_id)
  {
    throw std::runtime_error("Cannot use a single text buffer with multiple fonts");
  }

  m_GlyphPositions.clear();
  font->CreateVertexBufferForString(text, scale, sel_start, sel_end, cursor_pos, m_Settings, vertex_builder, m_GlyphPositions);
}

void TextManager::AddTextToBuffer(std::shared_ptr<TextInputContext> & context, int font_id, float scale, TextBufferBuilder & vertex_builder, const char * prompt)
{
  std::string text = prompt;
  std::size_t prompt_length = TextInputContext::GetMultibyteLength(prompt);
  text += context->GetCurrentInput();

  int cursor_pos = (int)(context->GetCursorPos() + prompt_length);

  auto & compo = context->GetCurrentComposition();
  std::size_t compo_size = context->GetMultibyteLength(compo.data());

  double s;
  bool show_cursor = std::modf(context->GetTimeSinceLastUpdate(), &s) <= 0.5;

  if (compo_size)
  {
    text.insert(text.begin() + prompt_length + context->GetCharacterByteOffset(context->GetCursorPos()), compo.begin(), compo.end());
    AddTextToBuffer(text.data(), font_id, scale, vertex_builder, cursor_pos, (int)(cursor_pos + compo_size), show_cursor ? (int)(cursor_pos + compo_size) : -1);
  }
  else
  {
    AddTextToBuffer(text.data(), font_id, scale, vertex_builder, -1, -1, context->IsTextInputActive() && show_cursor ? cursor_pos : -1);
  }
}

void TextManager::RenderBuffer(TextBufferBuilder & vertex_builder, RenderState & render_state)
{
  if (vertex_builder.m_FontId == kInvalidFontId)
  {
    return;
  }

  auto itr = s_Fonts.find(vertex_builder.m_FontId);
  if (itr == s_Fonts.end())
  {
    return;
  }

  auto & font = itr->second;
  if (font->Loaded() == false)
  {
    return;
  }

  RenderVec4 screen_bounds = { -1, -1, 1, 1 };
  if (m_Settings.m_TextBounds)
  {
    screen_bounds.x = 2.0f * ((float)m_Settings.m_TextBounds->m_Start.x - 0.5f) / (float)render_state.GetRenderWidth();
    screen_bounds.y = 2.0f * ((float)m_Settings.m_TextBounds->m_Start.y - 0.5f) / (float)render_state.GetRenderHeight();
    screen_bounds.z = 2.0f * ((float)m_Settings.m_TextBounds->m_End.x - 0.5f) / (float)render_state.GetRenderWidth();
    screen_bounds.w = 2.0f * ((float)m_Settings.m_TextBounds->m_End.y - 0.5f) / (float)render_state.GetRenderHeight();
  }

  render_state.EnableBlendMode();

  m_TextVertexBuffer.SetBufferData(vertex_builder.m_Verts, VertexBufferType::kTriangles);

  auto & shader = g_ShaderManager.GetDefaultScreenSpaceShader();
  render_state.BindShader(shader);
  render_state.BindVertexBuffer(m_TextVertexBuffer);

  font->BindGlyphTexture(render_state, 0);

  auto color_matrix = Mat4f(1.0f, 0.0f, 0.0f, 0.0f,
                            1.0f, 0.0f, 0.0f, 0.0f,
                            1.0f, 0.0f, 0.0f, 0.0f,
                            1.0f, 0.0f, 0.0f, 0.0f);

  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_ScreenSize"), RenderVec2{ render_state.GetRenderSize() });
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Offset"), RenderVec2{ 0, 0 });
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Matrix"), RenderVec4{ 1.0f, 0, 0, 1.0f });
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Texture"), 0);
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), RenderVec4{ 1.0f, 1.0f, 1.0f, 1.0f });
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Bounds"), screen_bounds);
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_ColorMatrix"), color_matrix);

  render_state.Draw();
}

void TextManager::RenderText(const std::string_view & text, int font_id, float scale, RenderState & render_state, int sel_start, int sel_end, int cursor_pos)
{
  TextBufferBuilder buffer_builder;
  AddTextToBuffer(text, font_id, scale, buffer_builder, sel_start, sel_end, cursor_pos);
  RenderBuffer(buffer_builder, render_state);
}

void TextManager::RenderInputText(std::shared_ptr<TextInputContext> & context, int font_id, float scale, RenderState & render_state, const char * prompt)
{
  TextBufferBuilder buffer_builder;
  AddTextToBuffer(context, font_id, scale, buffer_builder, prompt);
  RenderBuffer(buffer_builder, render_state);
}

Box TextManager::GetTextSize(const std::string_view & text, int font_id, float scale)
{
  auto itr = s_Fonts.find(font_id);
  if (itr == s_Fonts.end())
  {
    return{};
  }

  auto & font = itr->second;
  if (font->Loaded() == false)
  {
    return{};
  }

  return font->GetTextSize(text, scale);
}

Box TextManager::GetTextSize(std::shared_ptr<TextInputContext> & context, int font_id, float scale, const char * prompt)
{
  std::string text = prompt;
  std::size_t prompt_length = TextInputContext::GetMultibyteLength(prompt);
  text += context->GetCurrentInput();

  int cursor_pos = (int)(context->GetCursorPos() + prompt_length);

  auto & compo = context->GetCurrentComposition();
  std::size_t compo_size = context->GetMultibyteLength(compo.data());

  double s;
  bool show_cursor = std::modf(context->GetTimeSinceLastUpdate(), &s) <= 0.5;

  if (compo_size)
  {
    text.insert(text.begin() + prompt_length + context->GetCharacterByteOffset(context->GetCursorPos()), compo.begin(), compo.end());
    return GetTextSize(text.data(), font_id, scale);
  }
  else
  {
    return GetTextSize(text.data(), font_id, scale);
  }
}

float TextManager::GetLineHeight(int font_id, float scale) const
{
  auto itr = s_Fonts.find(font_id);
  if (itr == s_Fonts.end())
  {
    return{};
  }

  auto & font = itr->second;
  if (font->Loaded() == false)
  {
    return{};
  }

  return font->GetLineHeight() * scale;
}

bool TextManager::BindGlyphTexture(RenderState & render_state, int font_id, int texture_stage)
{
  auto itr = s_Fonts.find(font_id);
  if (itr == s_Fonts.end())
  {
    return false;
  }

  auto & font = itr->second;
  if (font->Loaded() == false)
  {
    return false;
  }

  font->BindGlyphTexture(render_state, texture_stage);
  return true;
}

void TextManager::SetTextMode(TextRenderMode mode)
{
  m_Settings.m_Mode = mode;
}

void TextManager::SetTextPos(const Vector2f & pos)
{
  m_Settings.m_TextPos = pos;
  m_Settings.m_TextBounds.Clear();
}

void TextManager::SetTextBounds(const Box & bounds)
{
  m_Settings.m_TextBounds = bounds;
}

void TextManager::ClearTextBounds()
{
  m_Settings.m_TextBounds.Clear()	;
}

void TextManager::SetPrimaryColor(const Color & color)
{
  m_Settings.m_PrimaryColor = color;
}

void TextManager::SetShadowColor(const Color & color)
{
  m_Settings.m_ShadowColor = color;
}

void TextManager::SetSelectionColor(const Color & color)
{
  m_Settings.m_SelectionColor = color;
}

void TextManager::SetSelectionBkgColor(const Color & color)
{
  m_Settings.m_SelectionBkgColor = color;
}

void TextManager::LoadBackupFont(czstr font_path)
{
  int file_open_error;
  auto buffer = g_AssetLoader.LoadFullFile(font_path, file_open_error);

  if (buffer)
  {
    s_BackupFonts.emplace_back(std::make_unique<TextBackupFont>(std::move(*buffer)));
  }
}

bool TextManager::VisitTextSizeInternal(Delegate<bool, const Box &, char32_t, czstr> & callback, const std::string_view & text, int font_id, float scale)
{
  auto itr = s_Fonts.find(font_id);
  if (itr == s_Fonts.end())
  {
    return true;
  }

  auto & font = itr->second;
  if (font->Loaded() == false)
  {
    return true;
  }

  return font->VisitTextSize(callback, text, scale);
}
