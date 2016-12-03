
#include "Engine/EngineCommon.h"

#include "Foundation/FileSystem/File.h"

#include "Engine/Text/TextManager.h"
#include "Engine/Text/TextRenderer.h"
#include "Engine/Text/TextShaders.h"
#include "Engine/Rendering/Shader.h"
#include "Engine/Rendering/RenderErrorMacros.h"
#include "Engine/Rendering/RenderState.h"

#include <gl3w/gl3w.h>

TextManager g_TextManager;

void TextManager::Init()
{
  m_FontShader = MakeQuickShaderProgram(kBasicTextVertexShader, kBasicTextFragmentShader);
}

void TextManager::ShutDown()
{
  m_Fonts.clear();
}

void TextManager::LoadFont(czstr font_path, int font_id, int font_size)
{
  m_Fonts.emplace(std::make_pair(font_id, std::make_unique<TextRenderer>(FontAsset::Load(font_path), font_size)));
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

void TextManager::RenderText(czstr text, int font_id, Color color, const Vector2 & pos, RenderState & render_state)
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

  auto num_glyphs = font->CreateVertexBufferForString(text, strlen(text), m_VertexBuffer, color);

  m_FontShader.Bind();
  m_VertexBuffer.Bind();
  m_VertexBuffer.CreateDefaultBinding(m_FontShader);

  font->BindGlyphTexture(0);

  render_state.EnableBlendMode();

  m_FontShader.SetUniform(COMPILE_TIME_CRC32_STR("u_GlyphTexture"), 0); CHECK_GL_RENDER_ERROR;
  m_FontShader.SetUniform(COMPILE_TIME_CRC32_STR("u_Str"), 1.0f); CHECK_GL_RENDER_ERROR;

  m_FontShader.SetUniform(COMPILE_TIME_CRC32_STR("u_ScreenSize"), (float)render_state.GetScreenWidth(), (float)render_state.GetScreenHeight()); CHECK_GL_RENDER_ERROR;
  m_FontShader.SetUniform(COMPILE_TIME_CRC32_STR("u_TextPos"), (RenderVec2)pos); CHECK_GL_RENDER_ERROR;
  m_FontShader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), RenderVec4{ 0, 0, 0, 0 }); CHECK_GL_RENDER_ERROR;

  m_VertexBuffer.Draw();

  render_state.DisableBlendMode();

  m_VertexBuffer.Unbind();
  m_FontShader.Unbind();
}

void TextManager::RenderTextShadowed(czstr text, int font_id, Color color, Color shadow_color, const Vector2 & pos, RenderState & render_state)
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

  auto num_glyphs = font->CreateVertexBufferForString(text, strlen(text), m_VertexBuffer, color);

  m_FontShader.Bind();
  m_VertexBuffer.Bind();
  m_VertexBuffer.CreateDefaultBinding(m_FontShader);

  font->BindGlyphTexture(0);

  render_state.EnableBlendMode();

  int x = pos.x;
  int y = pos.y;

  m_FontShader.SetUniform(COMPILE_TIME_CRC32_STR("u_GlyphTexture"), 0); CHECK_GL_RENDER_ERROR;
  m_FontShader.SetUniform(COMPILE_TIME_CRC32_STR("u_Str"), 1.0f); CHECK_GL_RENDER_ERROR;

  m_FontShader.SetUniform(COMPILE_TIME_CRC32_STR("u_ScreenSize"), (float)render_state.GetScreenWidth(), (float)render_state.GetScreenHeight()); CHECK_GL_RENDER_ERROR;
  m_FontShader.SetUniform(COMPILE_TIME_CRC32_STR("u_TextPos"), (float)x + 1, (float)y - 1); CHECK_GL_RENDER_ERROR;
  m_FontShader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), RenderVec4{ shadow_color.r, shadow_color.g, shadow_color.b, 1 }); CHECK_GL_RENDER_ERROR;

  m_VertexBuffer.Draw();

  m_FontShader.SetUniform(COMPILE_TIME_CRC32_STR("u_TextPos"), (float)x, (float)y); CHECK_GL_RENDER_ERROR;
  m_FontShader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), RenderVec4{ 0, 0, 0, 0 }); CHECK_GL_RENDER_ERROR;

  m_VertexBuffer.Draw();

  render_state.DisableBlendMode();

  m_VertexBuffer.Unbind();
  m_FontShader.Unbind();
}

void TextManager::RenderTextOutlined(czstr text, int font_id, Color color, Color outline_color, const Vector2 & pos, RenderState & render_state)
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

  auto num_glyphs = font->CreateVertexBufferForString(text, strlen(text), m_VertexBuffer, color);

  m_FontShader.Bind();
  m_VertexBuffer.Bind();
  m_VertexBuffer.CreateDefaultBinding(m_FontShader);

  font->BindGlyphTexture(0);

  render_state.EnableBlendMode();

  int x = pos.x;
  int y = pos.y;

  m_FontShader.SetUniform(COMPILE_TIME_CRC32_STR("u_GlyphTexture"), 0); CHECK_GL_RENDER_ERROR;
  m_FontShader.SetUniform(COMPILE_TIME_CRC32_STR("u_Str"), 0.5f); CHECK_GL_RENDER_ERROR;

  m_FontShader.SetUniform(COMPILE_TIME_CRC32_STR("u_ScreenSize"), (float)render_state.GetScreenWidth(), (float)render_state.GetScreenHeight()); CHECK_GL_RENDER_ERROR;
  m_FontShader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), RenderVec4{ outline_color.r, outline_color.g, outline_color.b, 1.0f }); CHECK_GL_RENDER_ERROR;

  m_FontShader.SetUniform(COMPILE_TIME_CRC32_STR("u_TextPos"), (float)x + 1, (float)y + 1); CHECK_GL_RENDER_ERROR;
  m_VertexBuffer.Draw();
  m_FontShader.SetUniform(COMPILE_TIME_CRC32_STR("u_TextPos"), (float)x - 1, (float)y + 1); CHECK_GL_RENDER_ERROR;
  m_VertexBuffer.Draw();
  m_FontShader.SetUniform(COMPILE_TIME_CRC32_STR("u_TextPos"), (float)x - 1, (float)y - 1); CHECK_GL_RENDER_ERROR;
  m_VertexBuffer.Draw();
  m_FontShader.SetUniform(COMPILE_TIME_CRC32_STR("u_TextPos"), (float)x + 1, (float)y - 1); CHECK_GL_RENDER_ERROR;
  m_VertexBuffer.Draw();
  m_FontShader.SetUniform(COMPILE_TIME_CRC32_STR("u_TextPos"), (float)x + 1, (float)y); CHECK_GL_RENDER_ERROR;
  m_VertexBuffer.Draw();
  m_FontShader.SetUniform(COMPILE_TIME_CRC32_STR("u_TextPos"), (float)x - 1, (float)y); CHECK_GL_RENDER_ERROR;
  m_VertexBuffer.Draw();
  m_FontShader.SetUniform(COMPILE_TIME_CRC32_STR("u_TextPos"), (float)x, (float)y + 1); CHECK_GL_RENDER_ERROR;
  m_VertexBuffer.Draw();
  m_FontShader.SetUniform(COMPILE_TIME_CRC32_STR("u_TextPos"), (float)x, (float)y - 1); CHECK_GL_RENDER_ERROR;
  m_VertexBuffer.Draw();

  m_FontShader.SetUniform(COMPILE_TIME_CRC32_STR("u_TextPos"), (float)x, (float)y); CHECK_GL_RENDER_ERROR;
  m_FontShader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), RenderVec4{ 0, 0, 0, 0 }); CHECK_GL_RENDER_ERROR;
  m_FontShader.SetUniform(COMPILE_TIME_CRC32_STR("u_Str"), 1.0f); CHECK_GL_RENDER_ERROR;

  m_VertexBuffer.Draw();

  render_state.DisableBlendMode();

  m_VertexBuffer.Unbind();
  m_FontShader.Unbind();
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
