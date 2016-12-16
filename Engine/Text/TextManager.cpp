
#include "Engine/EngineCommon.h"

#include "Foundation/FileSystem/File.h"

#include "Engine/Text/TextManager.h"
#include "Engine/Text/TextRenderer.h"
#include "Engine/Text/TextShaders.h"
#include "Engine/Input/TextInputContext.h"
#include "Engine/Rendering/Shader.h"
#include "Engine/Rendering/RenderErrorMacros.h"
#include "Engine/Rendering/RenderState.h"
#include "Engine/Asset/AssetLoader.h"

#include <codecvt>

TextManager g_TextManager;

void TextManager::Init()
{
  m_TextShader = MakeQuickShaderProgram(kBasicTextVertexShader, kBasicTextFragmentShader);

#ifdef _MSC_VER
  LoadBackupFont("C:\\Windows\\Fonts\\arial.ttf");
  LoadBackupFont("C:\\Windows\\Fonts\\gulim.ttc");
#endif

  SetTextMode();
  SetPrimaryColor();
  SetShadowColor();
  SetSelectionColor();
  SetSelectionBkgColor();
}

void TextManager::ShutDown()
{
  m_Fonts.clear();
}

void TextManager::LoadFont(czstr font_path, int font_id, int font_size)
{
  m_Fonts.emplace(std::make_pair(font_id, std::make_unique<TextRenderer>(FontAsset::Load(font_path), font_size, m_BackupFonts)));
}

bool TextManager::IsFontLoaded(int font_id)
{
  auto itr = m_Fonts.find(font_id);
  if (itr == m_Fonts.end())
  {
    return false ;
  }

  auto & font = itr->second;
  return font->Loaded();
}

void TextManager::AddTextToBuffer(czstr text, int font_id, TextBufferBuilder & vertex_builder, int sel_start, int sel_end, int cursor_pos)
{
  auto itr = m_Fonts.find(font_id);
  if (itr == m_Fonts.end())
  {
    return;
  }

  auto & font = itr->second;
  if (font->Loaded() == false)
  {
    return;
  }

  if (vertex_builder.m_FontId == -1)
  {
    vertex_builder.m_FontId = font_id;
  }
  else if (vertex_builder.m_FontId != font_id)
  {
    throw std::runtime_error("Cannot use a single text buffer with multiple fonts");
  }

  m_GlyphPositions.clear();
  font->CreateVertexBufferForString(text, strlen(text), sel_start, sel_end, cursor_pos, m_Settings, vertex_builder, m_GlyphPositions);
}

void TextManager::RenderBuffer(TextBufferBuilder & vertex_builder, RenderState & render_state)
{
  if (vertex_builder.m_FontId == -1)
  {
    return;
  }

  auto itr = m_Fonts.find(vertex_builder.m_FontId);
  if (itr == m_Fonts.end())
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
    screen_bounds.x = (float)m_Settings.m_TextBounds->m_Start.x / (float)render_state.GetScreenWidth();
    screen_bounds.y = (float)m_Settings.m_TextBounds->m_Start.y / (float)render_state.GetScreenHeight();
    screen_bounds.w = (float)m_Settings.m_TextBounds->m_End.x / (float)render_state.GetScreenWidth();
    screen_bounds.z = (float)m_Settings.m_TextBounds->m_End.y / (float)render_state.GetScreenHeight();

    screen_bounds -= RenderVec4{ 0.5f, 0.5f, 0.5f, 0.5f };
    screen_bounds *= 2.0f;
  }

  render_state.EnableBlendMode();

  m_TextShader.Bind();
  m_TextVertexBuffer.Bind();
  m_TextVertexBuffer.CreateDefaultBinding(m_TextShader);

  font->BindGlyphTexture(0);

  m_TextShader.SetUniform(COMPILE_TIME_CRC32_STR("u_GlyphTexture"), 0);
  m_TextShader.SetUniform(COMPILE_TIME_CRC32_STR("u_ScreenSize"), (float)render_state.GetScreenWidth(), (float)render_state.GetScreenHeight());
  m_TextShader.SetUniform(COMPILE_TIME_CRC32_STR("u_Bounds"), screen_bounds);

  m_TextVertexBuffer.Draw();

  render_state.DisableBlendMode();

  m_TextVertexBuffer.Unbind();
  m_TextShader.Unbind();
}

void TextManager::RenderText(czstr text, int font_id, RenderState & render_state, int sel_start, int sel_end, int cursor_pos)
{
  AddTextToBuffer(text, font_id, m_BufferBuilder, sel_start, sel_end, cursor_pos);
  RenderBuffer(m_BufferBuilder, render_state);
}

void TextManager::RenderInputText(std::shared_ptr<TextInputContext> & context, int font_id, RenderState & render_state)
{
  std::string text = context->GetCurrentInput();

  auto & compo = context->GetCurrentComposition();
  std::size_t compo_size = context->GetMultibyteLength(compo.data());

  double s;
  int cursor_pos = std::modf(context->GetTimeSinceLastUpdate(), &s) <= 0.5 ? (int)context->GetCursorPos() : -1;

  if (compo_size)
  {
    text.insert(text.begin() + context->GetCharacterByteOffset(context->GetCursorPos()), compo.begin(), compo.end());
    RenderText(text.data(), font_id, render_state, (int)context->GetCursorPos(), (int)(context->GetCursorPos() + compo_size - 1), cursor_pos);
  }
  else
  {
    RenderText(text.data(), font_id, render_state, -1, -1, cursor_pos);
  }
}

Box TextManager::GetTextSize(czstr text, int font_id)
{
  auto itr = m_Fonts.find(font_id);
  if (itr == m_Fonts.end())
  {
    return{};
  }

  auto & font = itr->second;
  if (font->Loaded() == false)
  {
    return{};
  }

  return font->GetTextSize(text, strlen(text));
}

bool TextManager::BindGlyphTexture(int font_id, int texture_stage)
{
  auto itr = m_Fonts.find(font_id);
  if (itr == m_Fonts.end())
  {
    return false;
  }

  auto & font = itr->second;
  if (font->Loaded() == false)
  {
    return false;
  }

  font->BindGlyphTexture(texture_stage);
  return true;
}

void TextManager::SetTextMode(TextRenderMode mode)
{
  m_Settings.m_Mode = mode;
}

void TextManager::SetTextPos(const Vector2 & pos)
{
  m_Settings.m_TextPos = pos;
  m_Settings.m_TextBounds = {};
}

void TextManager::SetTextBounds(const Box & bounds)
{
  m_Settings.m_TextBounds = bounds;
}

void TextManager::ClearTextBounds()
{
  m_Settings.m_TextBounds = {};
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
    m_BackupFonts.emplace_back(std::make_unique<TextBackupFont>(std::move(*buffer)));
  }
}
