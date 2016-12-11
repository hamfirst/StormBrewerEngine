
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
  m_SelectionShader = MakeQuickShaderProgram(kBasicTextVertexShader, kSelectionBkgFragmentShader);

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

void TextManager::RenderText(czstr text, int font_id, RenderState & render_state, int sel_start, int sel_end, int cursor_pos)
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

  auto num_glyphs = font->CreateVertexBufferForString(text, strlen(text), m_GlyphPositions, 
    m_PrimaryColor, m_SelectionColor, m_SelectionBkgColor, m_TextVertexBuffer, m_SelectionVertexBuffer, sel_start, sel_end, cursor_pos);

  RenderVec4 screen_bounds = { -1, -1, 1, 1 };
  if (m_TextBounds)
  {
    screen_bounds.x = (float)m_TextBounds->m_Start.x / (float)render_state.GetScreenWidth();
    screen_bounds.y = (float)m_TextBounds->m_Start.y / (float)render_state.GetScreenHeight();
    screen_bounds.w = (float)m_TextBounds->m_End.x / (float)render_state.GetScreenWidth();
    screen_bounds.z = (float)m_TextBounds->m_End.y / (float)render_state.GetScreenHeight();

    screen_bounds -= RenderVec4{ 0.5f, 0.5f, 0.5f, 0.5f };
    screen_bounds *= 2.0f;
  }

  render_state.EnableBlendMode();

  if (num_glyphs.second > 0)
  {
    m_SelectionShader.Bind();
    m_SelectionVertexBuffer.Bind();
    m_SelectionVertexBuffer.CreateDefaultBinding(m_SelectionShader);

    m_SelectionShader.SetUniform(COMPILE_TIME_CRC32_STR("u_TextPos"), (RenderVec2)m_TextPos);
    m_SelectionShader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), m_SelectionBkgColor);
    m_SelectionShader.SetUniform(COMPILE_TIME_CRC32_STR("u_ScreenSize"), (float)render_state.GetScreenWidth(), (float)render_state.GetScreenHeight());
    m_SelectionShader.SetUniform(COMPILE_TIME_CRC32_STR("u_Bounds"), screen_bounds);
    m_SelectionVertexBuffer.Draw();

    m_SelectionShader.Unbind();
    m_SelectionVertexBuffer.Unbind();
  }

  m_TextShader.Bind();
  m_TextVertexBuffer.Bind();
  m_TextVertexBuffer.CreateDefaultBinding(m_TextShader);

  font->BindGlyphTexture(0);

  m_TextShader.SetUniform(COMPILE_TIME_CRC32_STR("u_GlyphTexture"), 0);
  m_TextShader.SetUniform(COMPILE_TIME_CRC32_STR("u_ScreenSize"), (float)render_state.GetScreenWidth(), (float)render_state.GetScreenHeight());
  m_TextShader.SetUniform(COMPILE_TIME_CRC32_STR("u_Bounds"), screen_bounds);

  if (m_Mode == TextRenderMode::kNormal)
  {
    m_TextShader.SetUniform(COMPILE_TIME_CRC32_STR("u_Str"), 1.0f);
  }
  if (m_Mode == TextRenderMode::kShadowed)
  {
    int x = m_TextPos.x;
    int y = m_TextPos.y;
    m_TextShader.SetUniform(COMPILE_TIME_CRC32_STR("u_Str"), 1.0f);
    m_TextShader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), RenderVec4{ m_ShadowColor.r, m_ShadowColor.g, m_ShadowColor.b, 1.0f });
    m_TextShader.SetUniform(COMPILE_TIME_CRC32_STR("u_TextPos"), (float)x + 1, (float)y - 1);

    m_TextVertexBuffer.Draw();
  }
  else if (m_Mode == TextRenderMode::kOutlined)
  {
    int x = m_TextPos.x;
    int y = m_TextPos.y;

    m_TextShader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), RenderVec4{ m_SelectionColor.r, m_SelectionColor.g, m_SelectionColor.b, 1.0f });

    m_TextShader.SetUniform(COMPILE_TIME_CRC32_STR("u_GlyphTexture"), 0);
    m_TextShader.SetUniform(COMPILE_TIME_CRC32_STR("u_Str"), 0.5f);

    m_TextShader.SetUniform(COMPILE_TIME_CRC32_STR("u_TextPos"), (float)x + 1, (float)y + 1);
    m_TextVertexBuffer.Draw();
    m_TextShader.SetUniform(COMPILE_TIME_CRC32_STR("u_TextPos"), (float)x - 1, (float)y + 1);
    m_TextVertexBuffer.Draw();
    m_TextShader.SetUniform(COMPILE_TIME_CRC32_STR("u_TextPos"), (float)x - 1, (float)y - 1);
    m_TextVertexBuffer.Draw();
    m_TextShader.SetUniform(COMPILE_TIME_CRC32_STR("u_TextPos"), (float)x + 1, (float)y - 1);
    m_TextVertexBuffer.Draw();
    m_TextShader.SetUniform(COMPILE_TIME_CRC32_STR("u_TextPos"), (float)x + 1, (float)y);
    m_TextVertexBuffer.Draw();
    m_TextShader.SetUniform(COMPILE_TIME_CRC32_STR("u_TextPos"), (float)x - 1, (float)y);
    m_TextVertexBuffer.Draw();
    m_TextShader.SetUniform(COMPILE_TIME_CRC32_STR("u_TextPos"), (float)x, (float)y + 1);
    m_TextVertexBuffer.Draw();
    m_TextShader.SetUniform(COMPILE_TIME_CRC32_STR("u_TextPos"), (float)x, (float)y - 1);
    m_TextVertexBuffer.Draw();

    m_TextShader.SetUniform(COMPILE_TIME_CRC32_STR("u_Str"), 1.0f);
  }


  m_TextShader.SetUniform(COMPILE_TIME_CRC32_STR("u_TextPos"), (RenderVec2)m_TextPos);
  m_TextShader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), Color(0, 0, 0, 0));

  m_TextVertexBuffer.Draw();

  render_state.DisableBlendMode();

  m_TextVertexBuffer.Unbind();
  m_TextShader.Unbind();
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
  m_Mode = mode;
}

void TextManager::SetTextPos(const Vector2 & pos)
{
  m_TextPos = pos;
  m_TextBounds = {};
}

void TextManager::SetTextBounds(const Box & bounds)
{
  m_TextBounds = bounds;
}

void TextManager::ClearTextBounds()
{
  m_TextBounds = {};
}

void TextManager::SetPrimaryColor(const Color & color)
{
  m_PrimaryColor = color;
}

void TextManager::SetShadowColor(const Color & color)
{
  m_ShadowColor = color;
}

void TextManager::SetSelectionColor(const Color & color)
{
  m_SelectionColor = color;
}

void TextManager::SetSelectionBkgColor(const Color & color)
{
  m_SelectionBkgColor = color;
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
